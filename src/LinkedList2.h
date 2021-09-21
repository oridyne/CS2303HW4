#ifndef LINKEDLIST2_H_
#define LINKEDLIST2_H_
#include <iostream>
#include <cstdlib>
#include "Room.h"

typedef struct SearchResults {
	int roomNumber;
	float treasure;
} SearchResults;

SearchResults* createResult(int roomNumber, float treasure);

template <class T>
class Node {
	public:
		Node<T>* next;
		Node<T>* prev;
		T* data;
};

template <class T>
class LinkedList {
	public:
		LinkedList();
		~LinkedList();
		void addEnd(T* newData);
		T* dequeueLIFO();
		void print();
		bool isEmpty();
		Node<T>* getHead();
		Node<T>* getTail();
		int getLength();
	private:
		int length;
		Node<T>* head;
		Node<T>* tail;
};

template <class T>
LinkedList<T>::LinkedList() {
	this->length = 0;
	this->head = NULL;
	this->tail = NULL;
}

template <class T>
LinkedList<T>::~LinkedList() {
	Node<T>* currNode = head;
	Node<T>* temp;
	while (currNode != NULL) {
		temp = currNode->next;
		if(currNode->data != NULL) {
			delete currNode->data;
		}
		delete currNode;
		currNode = temp;
	}
}

template<class T>
Node<T>* LinkedList<T>::getHead() {
	return head;
}

template<class T>
Node<T>* LinkedList<T>::getTail() {
	return tail;
}

template<class T>
int LinkedList<T>::getLength() {
	return length;
}

template <class T>
void LinkedList<T>::addEnd(T* newData) {
	Node<T>* newNode = new Node<T>;
	newNode->data = newData;
	if(this->isEmpty()) {
		this->head = newNode;
		this->tail = newNode;
		newNode->next = NULL;
	} else {
		this->tail->next = newNode;
		newNode->prev = this->tail;
		newNode->next = NULL;
		this->tail = newNode;
	}
	length++;
}

template <class T>
void LinkedList<T>::print() {
	Node<T>* temp = this->head;
	int count = 0;
	while(temp != NULL) {
		std::cout << "Node Data:" << temp->data << std::endl;
		temp = temp->next;
		count++;
	}
}

template <> void LinkedList<Room>::print();
template <> void LinkedList<SearchResults>::print();

template <class T>
bool LinkedList<T>::isEmpty() {
	return length == 0;
}

#endif
