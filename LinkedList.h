#pragma once
//class for a circular linkedList

template<typename T> struct Node;


template<typename T>
class LinkedList
{
public:
	LinkedList<T>();
	void insert(T newData);
	void deleteNode();
	void next();
	void previous();
	int getLength();
	T getCurr();
	bool isHead();

private:
	Node<T>* head;
	Node<T>*	currNode;
	int length;
};

template<typename T>
struct Node
{
  T data;
	Node* next;
	Node* back;
};
