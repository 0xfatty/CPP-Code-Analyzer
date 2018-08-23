#ifndef STACK
#define STACK

#include "linkedlist.h"
#include "DSString.h"

template<class T>
class Stack{

    public:

        void peekpop();
        T pop();
        T peek();
        void push(T);
        bool isEmpty();
		int size();

		const LinkedList<T> getData();

    private:

        LinkedList<T> data;

};

template<class T> const LinkedList<T> Stack<T>::getData() {
	return data;
}

// Removes the first element of the first stack, if it is one
template<class T> void Stack<T>::peekpop() {
    data[0].pop();
}

template<class T> int Stack<T>::size() {
	return data.size();
}

template<class T> T Stack<T>::pop() {
	T ret = data.remove(0);
	return ret;
}

template<class T> T Stack<T>::peek() {
	return data.get(0);
}

template<class T> void Stack<T>::push(T item) {
	data.addToFront(item);
}

template<class T> bool Stack<T>::isEmpty() {
	return data.isEmpty();
}

#endif
