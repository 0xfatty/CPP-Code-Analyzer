/* indexinterface.cpp
 * Generic interface for indexers */
#include "indexinterface.h"
#include <string.h>

using std::string;
using std::getline;

// Helper function to sort a vector of IndexItems by count
bool sortII(IndexItem a, IndexItem b) {
    return a.count > b.count;
}

std::vector<IndexItem> IndexInterface::topFifty() {
    std::vector<IndexItem> t = dumpTable();
    std::vector<IndexItem> retVal;

    std::sort(t.begin(), t.end(), sortII);
    std::sort(t.begin(), t.end(), sortII);

    for(int i=0;i<50&&i<t.size();i++) {
        retVal.push_back(t[i]);
    }

    return retVal;
}

void IndexInterface::saveIndex(string fn) {
    std::vector<IndexItem> dt = dumpTable();

    std::ofstream out;

    out.open(fn);
    if(out.fail())
        return;

    out << dt.size() << std::endl;
    out << pagesCount << std::endl;
    for(IndexItem i: dt) {
        out << i.data << std::endl;
        out << i.count << std::endl;
        out << i.docs.size() << std::endl;
        for(IndexDocItem s: i.docs) {
            out << s.name << std::endl;
            out << s.count << std::endl;
        }
    }
    out.close();
}

void IndexInterface::loadIndex(string fn) {
    std::ifstream in;
    int cnt, cnt2, wcnt;

    in.open(fn);
    if(in.fail())
        return;

    in >> cnt;
    in >> pagesCount;
    // This line is required to absorb the newline
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i=0;i<cnt;i++) {
        string data;
        getline(in, data);
        in >> wcnt;
        in >> cnt2;
        // This line is required to absorb the newline
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(int i2=0;i2<cnt2;i2++) {
            string doc;
            int dcount;
            std::getline(in, doc);
            in >> dcount;
            // This line is required to absorb the newline
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            addWord(data, doc, wcnt, dcount);
        }
    }
    in.close();
}

int IndexInterface::getFrequency(std::string name) {
    IndexItem* ii;
    ii = findItem(name);

    if(ii != nullptr) {
        return ii->count;
    }

    return -1;
}

void IndexInterface::setPageCount(int cnt) {
    this->pagesCount = cnt;
}

int IndexInterface::totalPagesCount() {
    return pagesCount;
}

int IndexInterface::totalWordsCount() {
    return wordsCount;
}


bool operator==(const IndexDocItem& a, const IndexDocItem& b) {
    return (a.name==b.name && a.count==b.count);
}

