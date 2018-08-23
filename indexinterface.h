/* indexinterface.h 
 * Generic interface for indexers */
#ifndef indexinterface_H
#define indexinterface_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
// required for numeric_limits
#include <limits>

// Item to contain a document name and a frequency
class IndexDocItem {
    public:
        IndexDocItem() { count = 0; }
        std::string name;
        int count;
        friend bool operator==(const IndexDocItem& a, const IndexDocItem& b);
};

class IndexItem {
    public:
        std::string data;
        std::vector<IndexDocItem> docs;
        int count;
        IndexItem() { count = 0; };
        IndexItem(const IndexItem &ii) {
            data = ii.data;
            docs = ii.docs;
            count = ii.count;
        }
};

class IndexInterface {
    public:
        // Pure virtual functions
        virtual void addWord(std::string, std::string, int cnt1=1, int cnt=1) = 0;
        virtual std::vector<IndexDocItem>* getDocsForWord(std::string) = 0;
        virtual IndexItem* findItem(std::string) = 0;

        // Storage and loading from files
        void saveIndex(std::string);
        void loadIndex(std::string);

        // Get document frequency of an item
        // returns -1 if not found
        int getFrequency(std::string);

        std::vector<IndexItem> topFifty();

        int totalPagesCount();
        int totalWordsCount();

        void setPageCount(int);
    protected:
        int pagesCount;
        int wordsCount;
    private:
        // Builds and returns a full table as vectors
        // Used to do saveIndex and loadIndex
        virtual std::vector<IndexItem> dumpTable() =0;
};
#endif
