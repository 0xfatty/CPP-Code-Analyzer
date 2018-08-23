// AVLTree.cpp
// Implementation of the AVLTree class

#include "AVLTree.h"
#include <iostream>
#include <algorithm>	// std::max

AVLTree::AVLTree(){
	// constructor for tree, root NULL
	root = nullptr;
    pagesCount = 0;
    wordsCount = 0;
}

AVLTree::~AVLTree(){
	// destructor for tree,
	// clear the root node to delete tree
	clear(root);
}

// public function for adding a word to the tree
// and its document to the docs vector, if not there
void AVLTree::addWord(std::string s, std::string d, int wcnt, int dcnt){
	// use insertNode function, starting with root
	AVLNode *insNode = insertNode(root, s, d, wcnt, dcnt);

    root = insNode;
	return;
}

std::vector<IndexDocItem>* AVLTree::getDocsForWord(std::string s){
	AVLNode *match = search(s, root);
	if (match == nullptr){
		return nullptr;
	}
	else {
		return &(match->docs);
	}
}

AVLNode* AVLTree::findItem(std::string s){
    AVLNode *match = search(s, root);
    return match;
}

std::vector<IndexItem> AVLTree::dumpTable() {
    std::vector<IndexItem> dt;

    dumpTableRecur(dt, root);

    return dt;
}

void AVLTree::dumpTableRecur(std::vector<IndexItem> &dt, AVLNode* n) {
    if(n==nullptr)
        return;
    IndexItem ii;
    dumpTableRecur(dt, n->left);
    ii.data = n->data;
    ii.docs = n->docs;
    ii.count = n->count;
    dt.push_back(ii);
    dumpTableRecur(dt, n->right);
}

void AVLTree::setDocs(AVLNode *insNode, std::string d, int cnt) {
	// determine if the document is in the docs vector
	bool dInDocs = false;
	for(int i=0; i < insNode->docs.size(); i++){
		if (insNode->docs[i].name == d){
            insNode->docs[i].count++;
			dInDocs = true;
			break;
		}
	}
	// if the document is not in, add it
	if(!dInDocs){
        IndexDocItem idi;
        idi.name = d;
        idi.count = cnt;
		insNode->docs.push_back(idi);
	}
}

AVLNode* AVLTree::insertNode(AVLNode* node, std::string s, std::string d, int wcnt, int dcnt){
	// node is nullptr when we have reached the end of
	// the tree, so return a new node
	if (node == nullptr) {
        AVLNode* retVal = new AVLNode(s, nullptr, nullptr, 1);
        retVal->count = wcnt;
        setDocs(retVal,d,dcnt);
        wordsCount++;
	    return retVal;
	}
	// determine if the word goes to left or right in
	// the tree
	if (s < node->data){
		node->left = insertNode(node->left,s,d,wcnt, dcnt);
	} 
	else if (s > node->data) {
		node->right = insertNode(node->right,s,d,wcnt,dcnt);
	} else {
		// the word is already in the tree and 
		// there is no need to rebalance
        setDocs(node, d, 1);
        node->count++;
		return node;
	}
	// rebalance tree after adding node
	return rebalance(node);
}

// rebalancing the tree
AVLNode* AVLTree::rebalance(AVLNode* node){
	// the node's height must be set
	setHeight(node);
	// getBalance will give the balance factor,
	// and there will be rotations if it is
	// 2 or -2
	if (getBalance(node) > 1) {
		if (node->data < node->left->data)
			return leftRightRotate(node);
		else if(node->data > node->left->data)
			return rightRotate(node);
	} else if (getBalance(node) < -1){
		if (node->data > node->right->data)
			return rightLeftRotate(node);
		else if(node->data < node->right->data)
			return leftRotate(node);
    }
	return node;
}

// Returns the height of a node or 0 if null
int AVLTree::getHeight(AVLNode* node) {
    if(node==nullptr)
        return 0;
    return node->nheight;
}

// helper function to set the height of node
// get the height of left and right child
// (or 0 if they are null) and set the
// node height to the greater value + 1
void AVLTree::setHeight(AVLNode* node){
	node->nheight = std::max(getHeight(node->left),getHeight(node->right)) + 1;
}

// helper function to get the balance factor
// the height of right child - height of
// left child
int AVLTree::getBalance(AVLNode* node){
	return getHeight(node->left) - getHeight(node->right);
}


AVLNode* AVLTree::leftRotate(AVLNode* node){
	AVLNode *temp = node->right;
	AVLNode *temp2 = temp->left;
	node->right = temp2;
	temp->left = node;
	setHeight(node);
	setHeight(temp);
	return temp;
}

AVLNode* AVLTree::rightRotate(AVLNode* node){
	AVLNode *temp = node->left;
	AVLNode *temp2 = temp->right;
    node->left = temp2;
    temp->right = node;
	setHeight(node);
	setHeight(temp);
	return temp;
}

AVLNode* AVLTree::rightLeftRotate(AVLNode* node){
	node->right = rightRotate(node->right);
	return leftRotate(node);
}

AVLNode* AVLTree::leftRightRotate(AVLNode* node){
	node->left = leftRotate(node->left);
	return rightRotate(node);
}

// clears the tree
void AVLTree::clear(AVLNode* node){
	if(node != nullptr){
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

// returns the node with data == s
// returns nullptr if s was not in the tree.
AVLNode* AVLTree::search(std::string s, AVLNode* node){
	if(node == nullptr){
		return nullptr;
	}
	if(s < node->data){
		return search(s, node->left);
	}
	if(s > node->data){
		return search(s, node->right);
	}
	return node;
}


