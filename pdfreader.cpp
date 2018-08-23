/* pdfreader functions
 * For reading PDF files
 * */

#include "pdfreader.h"

AVLTreeString PDFReader::stop_words;

void PDFReader::addToIndex(string word, string fn, IndexInterface* main_table) {
	// Do not add any words in the stopword list
    if(PDFReader::stop_words.findItem(word)!=nullptr||word==""){
        return;
    }

    // Ignore all number-only answers
    if(word.find_first_not_of("0123456789.") == std::string::npos)
        return;

    // Run words thru the stemmer
    Porter2Stemmer::stem(word);

    main_table->addWord(word,fn);
}

void PDFReader::readStopWords() {
	std::ifstream in(STOPWORDSFN);
    string line;

    while(std::getline(in, line)) {
        // Lines that start with # are a comment
        if(line[0]!='#') {
            PDFReader::stop_words.addWord(line);
        }
    }
}

void PDFReader::dumpPDF(std::string fn) {
    int pageCnt;

    poppler::document *doc = poppler::document::load_from_file(fn);
    pageCnt = doc->pages();
    for (int i=0;i<pageCnt;++i) {
        std::string pageText;
        poppler::page *p = doc->create_page(i);
        pageText = p->text().to_latin1();
        std::cout << pageText;
    }
}

void PDFReader::readPDF(std::string fn, IndexInterface* main_table) {
    int pageCnt;
    TextStream ts;

    poppler::document *doc = poppler::document::load_from_file(fn);
    if(doc==nullptr)
        return;
    //std::cerr << "File: " << fn <<std::endl;
    pageCnt = doc->pages();
    //std::cerr << "Read Pages: " << pageCnt << " : ";

    // Process each page one at a time
    main_table->setPageCount(main_table->totalPagesCount() + pageCnt);
    for (int i=0;i<pageCnt;++i) {
        //std::cerr << ".";
        std::string pageText;
        poppler::page *p = doc->create_page(i);
        pageText = p->text().to_latin1();
        ts.addString(pageText);
        delete p;
        // If there is text output ready in the buffer, add it to the index
        if(ts.outputReady()) {
            std::stack<std::string> tsoutput;
            tsoutput = ts.getOutput();

            while(tsoutput.size()>0) {
                addToIndex(tsoutput.top(), fn, main_table);
                tsoutput.pop();
            }
            //std::cerr << "o";
        }
        // Add the remainding buffer.
        addToIndex(ts.getBufferAndWipe(), fn, main_table);
    }
    //std::cerr << std::endl;

    delete doc;

    return;
}

