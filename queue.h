#ifndef QUEUE
#define QUEUE

#include "linkedlist.h"

template<class T>
class Queue{

    public:

        T dequeue();
        T peek();
        void enqueue(T);
        bool isEmpty();
        int size();

    private:

        LinkedList<T> data;

};

template<class T> T Queue<T>::dequeue() {
	return data.remove(0);
}

template<class T> int Queue<T>::size() {
    return data.size();
}

template<class T> T Queue<T>::peek() {
	return data.get(0);
}

template<class T> void Queue<T>::enqueue(T item) {
	data.add(item);
}

template<class T> bool Queue<T>::isEmpty() {
	return data.isEmpty();
}

#endif
