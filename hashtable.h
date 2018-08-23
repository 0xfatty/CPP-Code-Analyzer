// hashtable.h
// Definition of hashtable class.
//
#ifndef hashtable_H
#define hashtable_H
#include <string>
#include <vector>
#include "indexinterface.h"

class HashItem : public IndexItem {
    public:
        std::string data;
        std::vector<IndexDocItem> docs;
};

class HashTable : public IndexInterface {
	private:
        unsigned int getHash(std::string);
        void setDocs(std::vector<IndexDocItem>&, std::string, int);

        // This is an array of vectors.
        std::vector<HashItem>* head;
        int size;

        // Outputs the table as a vector of vectors so that it can be
        // written to a file
        std::vector<IndexItem> dumpTable();

   	public:
		HashTable(int);
		~HashTable();
		void addWord(std::string, std::string, int wcnt=1, int dcnt=1);
		std::vector<IndexDocItem>* getDocsForWord(std::string);
        HashItem* findItem(std::string);
};
#endif
