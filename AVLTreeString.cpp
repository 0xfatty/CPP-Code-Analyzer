// AVLTreeString.cpp
// Implementation of the AVLTreeString class

#include "AVLTreeString.h"
#include <iostream>
#include <algorithm>	// std::max

AVLTreeString::AVLTreeString(){
	// constructor for tree, root NULL
	root = nullptr;
}

AVLTreeString::~AVLTreeString(){
	// destructor for tree,
	// clear the root node to delete tree
	clear(root);
}

// public function for adding a word to the tree
void AVLTreeString::addWord(std::string s){
	// use insertNode function, starting with root
	AVLNodeString *insNode = insertNode(root, s);

    root = insNode;
	return;
}

AVLNodeString* AVLTreeString::findItem(std::string s){
    AVLNodeString *match = search(s, root);
    return match;
}

AVLNodeString* AVLTreeString::insertNode(AVLNodeString* node, std::string s){
	// node is nullptr when we have reached the end of
	// the tree, so return a new node
	if (node == nullptr) {
        AVLNodeString* retVal = new AVLNodeString(s, nullptr, nullptr, 1);
	    return retVal;
	}
	// determine if the word goes to left or right in
	// the tree
	if (s < node->data){
		node->left = insertNode(node->left,s);
	} 
	else if (s > node->data) {
		node->right = insertNode(node->right,s);
	} else {
		// the word is already in the tree and 
		// there is no need to rebalance
		return node;
	}
	// rebalance tree after adding node
	return rebalance(node);
}

// rebalancing the tree
AVLNodeString* AVLTreeString::rebalance(AVLNodeString* node){
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
int AVLTreeString::getHeight(AVLNodeString* node) {
    if(node==nullptr)
        return 0;
    return node->nheight;
}

// helper function to set the height of node
// get the height of left and right child
// (or 0 if they are null) and set the
// node height to the greater value + 1
void AVLTreeString::setHeight(AVLNodeString* node){
	node->nheight = std::max(getHeight(node->left),getHeight(node->right)) + 1;
}

// helper function to get the balance factor
// the height of right child - height of
// left child
int AVLTreeString::getBalance(AVLNodeString* node){
	return getHeight(node->left) - getHeight(node->right);
}


AVLNodeString* AVLTreeString::leftRotate(AVLNodeString* node){
	AVLNodeString *temp = node->right;
	AVLNodeString *temp2 = temp->left;
	node->right = temp2;
	temp->left = node;
	setHeight(node);
	setHeight(temp);
	return temp;
}

AVLNodeString* AVLTreeString::rightRotate(AVLNodeString* node){
	AVLNodeString *temp = node->left;
	AVLNodeString *temp2 = temp->right;
    node->left = temp2;
    temp->right = node;
	setHeight(node);
	setHeight(temp);
	return temp;
}

AVLNodeString* AVLTreeString::rightLeftRotate(AVLNodeString* node){
	node->right = rightRotate(node->right);
	return leftRotate(node);
}

AVLNodeString* AVLTreeString::leftRightRotate(AVLNodeString* node){
	node->left = leftRotate(node->left);
	return rightRotate(node);
}

// clears the tree
void AVLTreeString::clear(AVLNodeString* node){
	if(node != nullptr){
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

// returns the node with data == s
// returns nullptr if s was not in the tree.
AVLNodeString* AVLTreeString::search(std::string s, AVLNodeString* node){
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

