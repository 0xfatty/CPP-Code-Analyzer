/* search.h
 *
 * Classes to support and implement searching
 * */

#ifndef SEARCH_H
#define SEARCH_H

#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>
#include "indexinterface.h"
#include "porter2_stemmer.h"

using std::string;
using std::queue;
using std::vector;

namespace PdfParser {
    enum QueryState {
        AND,
        OR,
        NOT
    };
}


class Result {
    public:
        string document;
        double getScore();
        void setScore(double);
    private:
        double score;
};

bool resultSort(Result a, Result b);

class Results {
    public:
        void op(PdfParser::QueryState, Results, IndexInterface*, bool);
        bool isIn(Result);
        vector<Result> resultsVec;
        void printResults();
        void sort();
};

class QueryParser {
    private:
        queue<string> queryQueue;
    public:

        // Raw input string from user
        void inputQuery(string);

        // Returns results in a vector
        // Requires pointer to primary table of information
        Results processQuery(IndexInterface*);
};


#endif
