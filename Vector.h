// Vector.h
//
// The vector class is the ULTIMATE CLASS!

#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <iostream>

//#include "DSString.h"

template <class VType> class Vector {
    public:
        
    // Default Constructor
	Vector();
    // Copy Constructor
    Vector(Vector const& v);
    // Default Destructor
    ~Vector();
    // Return count of items in vector
	int getSize() const;
    // Add an item to the end of the vector
	void addItem(VType item);
    // Remove an item at index
	void removeItem(int index);
    // [] operator using index
    // Returns a pointer so that the return value
    // can be NULL if the index is not valid
	VType* operator [](int index) const;

    // = operator
    Vector<VType>& operator=(const Vector<VType> &v);

    private:
        // Head of the vector
		VType* head;
		int size;
};

// Implementations
template <class VType> Vector<VType>& Vector<VType>::operator=(const Vector<VType> &v) {
    // Check for self-assignment
    if(this==&v)
        return *this;

    if(this->head!=NULL)
        delete [] head;
    if(v.size==0) {
        this->head = NULL;
        this->size = 0;
        return *this;
    }
        
    this->head = new VType[v.size];
    for(int i=0;i<v.size;i++)
        this->head[i] = *(v[i]);
    this->size = v.size;
    return *this;
}

template <class VType> Vector<VType>::Vector() {
	head = NULL;
	size = 0;
}

template <class VType> Vector<VType>::Vector(Vector const& v) {
    // Copy the memory array into a new array
    this->head = new VType[v.size];
    for(int i=0;i<v.size;i++)
        this->head[i] = *(v[i]);
    this->size = v.size;
}

template <class VType> Vector<VType>::~Vector() {
    if(head!=NULL)
        delete [] head;
}

template <class VType> int Vector<VType>::getSize() const {
	return size;
}

template <class VType> void Vector<VType>::addItem(VType item) {
    // To make the vector contiguous, allocate new memory
    // and retain pointer to old memory, copy over and delete
	VType* oldArray = head;
	head = new VType[size+1];
	
	for(int i=0; i<size; i++)
		head[i] = oldArray[i];
	head[size++] = item;
	
	delete [] oldArray;
}

template <class VType> void Vector<VType>::removeItem(int index) {
    // Similar to add, allocate new memory for the vector
    // and retain pointer to old memory, copying over all items
    // except the one to remove
	if(index<0 || index>size-1)
		return;

	VType* oldArray = head;
	head = new VType[size];

	for(int i=0; i<index; i++)
		head[i] = oldArray[i];
	for(int i=index+1;i<size;i++)
		head[i-1] = oldArray[i];

	size--;
	delete [] oldArray;
}

template <class VType> VType* Vector<VType>::operator [](int index) const {
	return &(head[index]);
}
#endif
