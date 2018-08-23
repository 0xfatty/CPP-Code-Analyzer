// hashtable.cpp
// Definition of hashtable class.
//
#include "hashtable.h"
#include <iostream>

using std::copy;

HashTable::HashTable(int size) {
    head = new std::vector<HashItem>[size];
    this->size = size;
    this->pagesCount = 0;
    this->wordsCount = 0;
}

HashTable::~HashTable() {
    delete [] head;
}

// djb2 algorithm for a string hash attributed to Dan Bernstein
// http://www.cse.yorku.ca/~oz/hash.html
// Modified for C++11
// modulo to fit to size of array
unsigned int HashTable::getHash(std::string s) {
    unsigned int hash = 5381;
    int c;

    for (char& c: s) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % size;
}

void HashTable::setDocs(std::vector<IndexDocItem>& docs, std::string d, int cnt) {
    // determine if the document is in the docs vector
    bool dInDocs = false;
    for(int i=0; i < docs.size(); i++){
        if (docs[i].name == d){
            dInDocs = true;
            docs[i].count++;
            break;
        }
    }
    // if the document is not in, add it
    if(!dInDocs){
        IndexDocItem idi;
        idi.name = d;
        idi.count = cnt;
        docs.push_back(idi);
    }
}

std::vector<IndexItem> HashTable::dumpTable() {
    std::vector<IndexItem> dt;
    dt.reserve(size);

    for(int i=0;i<size;i++) {
        // Copy the vector from this bucket into the dumpTable
        for(HashItem hi: head[i]) {
            IndexItem ii;
            ii.data = hi.data;
            ii.docs.reserve(hi.docs.size());
            ii.count = hi.count;
            copy(hi.docs.begin(),hi.docs.end(),std::back_inserter(ii.docs));
            dt.push_back(ii);
        }
    }

    return dt;
}

// Cnt defaults to 1
void HashTable::addWord(std::string s, std::string d, int icnt, int dcnt) {
    int hash;
    bool isInVector = false;

    hash = getHash(s);
    
    // Check this bucket to see if this string is already there
    for(int i=0;i<head[hash].size();i++) {
        if(head[hash][i].data == s) {
            isInVector = true;
            setDocs(head[hash][i].docs, d, dcnt);
            head[hash][i].count++;
        }
    }

    if(!isInVector) {
        HashItem hi;
        hi.data = s;
        hi.count = icnt;
        setDocs(hi.docs, d, dcnt);
        head[hash].push_back(hi);
        wordsCount++;
    }
}

// Return null if hashtable does not contain doc
std::vector<IndexDocItem>* HashTable::getDocsForWord(std::string s) {
    int hash;
    hash = getHash(s);
    
    for(HashItem& hi : head[hash]) {
        if(hi.data == s) {
            return &hi.docs;
        }
    }
    return nullptr;
}

HashItem* HashTable::findItem(std::string s){
    int hash;
    hash = getHash(s);
    for(HashItem &hi: head[hash]) {
        if(hi.data == s) {
            return &hi;
        }
    }
    return nullptr;
}

