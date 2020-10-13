#pragma once
//class for a circular linkedList

struct LineNode;
template<typename T>
class LinkedList
{
public:
	LineList();
	void goToHead();
	void insert (T newData);
	void deleteNode();
	void next();
	void previous();
	int getLength();
	T getCurr();

private:
	Node*	currNode;
	int length;
};

template<typename T>
struct Node
{
  T data;
	Node* next;
	Node* back;
};
