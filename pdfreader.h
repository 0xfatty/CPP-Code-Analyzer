/* pdfreader functions
 * For reading PDF files
 * */
#ifndef PDFREADER_H
#define PDFREADER_H

#include <iostream>
#include <string>
#include "AVLTree.h"
#include "porter2_stemmer.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "indexinterface.h"
#include "textstream.h"
#include "AVLTreeString.h"

#define STOPWORDSFN "stopwords.txt"

using std::string;

namespace PDFReader {
    extern AVLTreeString stop_words;
    void addToIndex(std::string, std::string, IndexInterface*);
    void readStopWords();
    void readPDF(std::string, IndexInterface*);
    void dumpPDF(std::string);
}

#endif
