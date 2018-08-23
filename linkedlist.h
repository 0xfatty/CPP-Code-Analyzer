#ifndef LINKED_LIST
#define LINKED_LIST

#include <cstdlib> // definition of NULL
#include <iostream> //cout and endl

template <class T>
class ListNode {
public:

	ListNode<T>(T d) {
		next = NULL;
		last = NULL;
		data = new T(d);
	}
    
    ListNode<T>(const ListNode<T>& t) {
        next = t.getNext();
        last = t.getLast();
        data = t.getData();
    }

    ~ListNode<T>() {
        delete data;
    }

	void setNext(ListNode<T>* n){
		next = n;
	}

	void setLast(ListNode<T>* n){
		last = n;
	}

	void setData(T d){
        delete data;
		data = new T(d);
	}

	ListNode<T> *getNext(){
		return next;
	}

	ListNode<T> *getLast(){
		return last;
	}

	T getData(){
		return *data;
	}

    ListNode<T>& operator=(const ListNode<T>& n) {
        next = n.getNext();
        last = n.getLast();
        data = n.getData();
    }

	// Use this to overload the []
	// operator in LinkedList
	T& getDataPtr(){
		return *data;
	}

private:
    ListNode<T>*next;
    ListNode<T>*last;
    T* data;
};


template<class T>
class LinkedList {

public:

    LinkedList();
    LinkedList(T);
    LinkedList(const LinkedList<T>&);

    void add(const T);
    void addToFront(const T);
    T get(int) const;
    int size() const;
    T remove(int);
    bool isEmpty();
    
    ~LinkedList();

    T& operator[] (int);
    LinkedList<T>& operator=(const LinkedList<T>&);

private:

    ListNode<T>*head;
    int num_elements;

};

template<class T> LinkedList<T>::LinkedList() {
	//Default Constructor
	head = NULL;
	num_elements = 0;
}

template<class T> LinkedList<T>::LinkedList(const T item) {
	// Constructor with data
	head = new ListNode<T>(item);
	num_elements = 1;
}

template<class T> LinkedList<T>::LinkedList(const LinkedList<T>& l) {
	// Copy constructor
	head = NULL;
	for (int i=0; i < l.size(); i++) {
		add(l.get(i));
	}
	num_elements = l.size();
}

template<class T> void LinkedList<T>::add(const T item) {
	// Add a new node to the end of the list
	if (isEmpty()) {
		head = new ListNode<T>(item);
	} else {
		ListNode<T> *temp = head;
		while(temp->getNext() != NULL) {
			temp = temp->getNext();
		}
		temp->setNext(new ListNode<T>(item));
		temp->getNext()->setLast(temp);
	}
	num_elements++;
}

template<class T> void LinkedList<T>::addToFront(const T item) {
	// Add a new node to the front of the list
	if (isEmpty()) {
		head = new ListNode<T>(item);
	} else {
		ListNode<T> *temp = head;
		head = new ListNode<T>(item);
		head->setNext(temp);
		temp->setLast(head);
	}
	num_elements++;
}

template<class T> T LinkedList<T>::get(int index) const {
	// Get data at certain index in the list
	ListNode<T> *temp = head;
	for (int i=0; i < index; i++) {
		if (temp->getNext() == NULL){
			return temp->getData();
		}
		temp = temp->getNext();
	}
	return temp->getData();
}

template<class T> int LinkedList<T>::size() const{
	// Get the size of the list
	return num_elements;
}

template<class T> T LinkedList<T>::remove(int index) {
	ListNode<T> *temp = head;
	for (int i=0; i < index; i++) {
		temp = temp->getNext();
	}
	T ret = temp->getData();
	if (temp->getLast() != NULL) {
		temp->getLast()->setNext(temp->getNext());
	}
	if ( temp->getNext() != NULL) {
		temp->getNext()->setLast(temp->getLast());
	}
	if (index == 0) {
		head = temp->getNext();
	}
	delete temp; // Delete what was removed

	num_elements--;


	return ret;
}

template<class T> bool LinkedList<T>::isEmpty() {
	// Check if the list is empty
	if (head == NULL){
		return true;
	} else {
		return false;
	}
}

template<class T> LinkedList<T>::~LinkedList() {
	// Destructor
	ListNode<T> *temp = head;
	ListNode<T> *nextTemp = head;
	for (int i=0; i < num_elements; i++){
		nextTemp = temp->getNext();
		delete temp;
		temp = nextTemp;
	}
}

template<class T> T& LinkedList<T>::operator[](int index) {
	// Overload [] operator - converts to pointer so it can
	// be set as well.
	ListNode<T> *temp = head;
	for (int i=0; i < index; i++) {
		if (temp->getNext() == NULL){
			return temp->getDataPtr();
		}
		temp = temp->getNext();
	}
	return temp->getDataPtr();
}

template<class T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& l) {
	// Overload = operator - similar to copy constructor
	for (int i=0; i < l.size(); i++) {
		add(l.get(i));
	}
	this->num_elements = l.size();
	return *this;
}

#endif
