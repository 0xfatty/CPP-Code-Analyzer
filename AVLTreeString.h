// AVLTreeString.h
// Definition of AVLTree class.
//
#ifndef AVLTreeString_H
#define AVLTreeString_H
#include <string>
#include <vector>

using std::string;

class AVLNodeString {
    public:
    std::string data;
    int nheight = 0;
    AVLNodeString* left = nullptr;
    AVLNodeString* right = nullptr;
    AVLNodeString(){};
    AVLNodeString(std::string d, AVLNodeString* l, AVLNodeString* r, int h)
        : data(std::move(d)), left(l), right(r), nheight(h)
    {}
    ~AVLNodeString(){};
};

class AVLTreeString {
	private:
		AVLNodeString* root;
		AVLNodeString* insertNode(AVLNodeString*, std::string);
		AVLNodeString* rebalance(AVLNodeString*);
		void setHeight(AVLNodeString*);
        int getHeight(AVLNodeString*);
		int getBalance(AVLNodeString*);
		AVLNodeString* leftRotate(AVLNodeString*);
		AVLNodeString* rightRotate(AVLNodeString*);
		AVLNodeString* leftRightRotate(AVLNodeString*);
		AVLNodeString* rightLeftRotate(AVLNodeString*);
		void clear(AVLNodeString*);
		void outputTree(AVLNodeString*);
		AVLNodeString* search(std::string, AVLNodeString*);

	public:
		AVLTreeString();
		~AVLTreeString();
		void addWord(std::string);
        AVLNodeString* findItem(std::string);
};
#endif
