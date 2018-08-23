// AVLTree.h
// Definition of AVLTree class.
//
#ifndef AVLTree_H
#define AVLTree_H
#include <string>
#include <vector>
#include "indexinterface.h"

class AVLNode : public IndexItem {
    public:
    std::string data;
    int nheight = 0;
    // use vector for fast iteration and insertion to end
    std::vector<IndexDocItem> docs;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    AVLNode(){};
    AVLNode(std::string d, AVLNode* l, AVLNode* r, int h)
        : data(std::move(d)), left(l), right(r), nheight(h)
    {};
    ~AVLNode(){};
};

class AVLTree : public IndexInterface {
	private:
		AVLNode* root;
		AVLNode* insertNode(AVLNode*, std::string, std::string, int, int);
		AVLNode* rebalance(AVLNode*);
		void setHeight(AVLNode*);
        int getHeight(AVLNode*);
		int getBalance(AVLNode*);
		AVLNode* leftRotate(AVLNode*);
		AVLNode* rightRotate(AVLNode*);
		AVLNode* leftRightRotate(AVLNode*);
		AVLNode* rightLeftRotate(AVLNode*);
		void clear(AVLNode*);
		void outputTree(AVLNode*);
		AVLNode* search(std::string, AVLNode*);
        void setDocs(AVLNode*, std::string, int);

        std::vector<IndexItem> dumpTable();

        void dumpTableRecur(std::vector<IndexItem> &dt, AVLNode* n);
	public:
		AVLTree();
		~AVLTree();
		void addWord(std::string, std::string, int cnt1=1, int cnt=1);
		std::vector<IndexDocItem>* getDocsForWord(std::string);
        AVLNode* findItem(std::string);
};
#endif
