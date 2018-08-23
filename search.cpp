/* search.cpp
 *
 * Classes to support and implement searching
 * */

#include "search.h"

using PdfParser::QueryState;

void QueryParser::inputQuery(string q) {
    string buffer;
    std::stringstream queryStream(q);

    while(queryStream >> buffer) {
        queryQueue.push(buffer);
    }
}

Results QueryParser::processQuery(IndexInterface* main_table) {
    QueryState qs = QueryState::OR; // Default to OR

    Results results;

    queue<string> queryQueue2(queryQueue);

    bool firstToken=true;
    // First we loop and get results
    while(!queryQueue.empty()) {
        string token;

        token = queryQueue.front();
        queryQueue.pop();

        // Check if this is an operator
        if(token == "AND") {
            qs = QueryState::AND;
            continue;
        }
        if(token == "OR") {
            qs = QueryState::OR;
            continue;
        }
        if(token == "NOT") {
            qs = QueryState::NOT;
            continue;
        }

        // Reaching here, token is not an operator
        // Search the master table for this string
        
        // Stem first
        Porter2Stemmer::stem(token);

        // Now Search
        vector<IndexDocItem> *docs = main_table->getDocsForWord(token);
        Results tokenres;

        if(!(docs==nullptr)) {
            for(int x=0;x<docs->size();x++) {
                Result r;
                r.document = docs->at(x).name;

                tokenres.resultsVec.push_back(r);
            }
        }
        results.op(qs, tokenres, main_table, firstToken);
        firstToken = false;
    }

    // Next, we rank results
    // For each result we check each word in the search phrase
    //
    for(Result& r: results.resultsVec) {
        queue<string> q(queryQueue2);
        double score;

        score = 0;

        while(!q.empty()) {
             string token;

             token = q.front();
             q.pop();

             // We ignore modifiers now
             if(token!="NOT"&&token!="OR"&&token!="AND") {
                 // How important is each word to this document?
                 double tf, idf;

                 // Stem first
                 Porter2Stemmer::stem(token);
                 
                 // Search document for word
                 vector<IndexDocItem> *docs = main_table->getDocsForWord(token);
                 if(docs==nullptr)
                     tf = 0;
                 else {
                     for(int x=0;x<docs->size();x++) {
                         if(docs->at(x).name == r.document) {
                            tf = docs->at(x).count;
                         }
                     }

                     idf = log((double)main_table->totalWordsCount() / (double)docs->size());
                 }

                 score += (tf * idf);
             }
        }

        r.setScore(score);
    }
    
    // Finally, we sort results by score
    results.sort();

    return results;
}


double Result::getScore() {
    // We use the tf-idf score of all involved 
    return score;
}

void Result::setScore(double x) {
    score = x;
}

bool resultSort(Result a, Result b) {
    return(a.getScore() > b.getScore());
}

// Sort the results vector by score
void Results::sort() {
    std::sort(resultsVec.begin(), resultsVec.end(), resultSort);
}

bool Results::isIn(Result rTest) {
    for(Result r: resultsVec) {
        if(r.document == rTest.document)
            return true;
    }
    return false;
}

void Results::printResults() {
    for(Result r: resultsVec) {
        std::cerr << "R:" << r.document << std::endl;
        std::cerr << "Score: " << r.getScore() << std::endl;
    }
}

void Results::op(QueryState cmd, Results newResult, IndexInterface* main_table, bool firstToken) {
        if((cmd==QueryState::AND)&&(!firstToken)) {
            // Remove all Result from resultsVec where document is not in newResult
            if(newResult.resultsVec.size()==0) {
                resultsVec.erase(resultsVec.begin(), resultsVec.end());
            }
            for(int x=0;x<resultsVec.size();x++) {
                if(!newResult.isIn(resultsVec[x])) {
                    resultsVec.erase(resultsVec.begin()+x);
                    x--;
                }
            }
        }
        if((cmd==QueryState::OR)||firstToken) {
            // Add all newResult unless already in resultsVec
            for(Result r: newResult.resultsVec) {
                if(!this->isIn(r)) {
                    resultsVec.push_back(r);
                }
            }
        }
        if(cmd==QueryState::NOT) {
            for(int x=0;x<resultsVec.size();x++) {
                if(newResult.isIn(resultsVec[x])) {
                    resultsVec.erase(resultsVec.begin()+x);
                    x--;
                }
            }
        }
}
