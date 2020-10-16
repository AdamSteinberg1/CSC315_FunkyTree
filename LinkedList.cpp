#include "LinkedList.h"

template<class T>
LinkedList<T>::LinkedList()
{
	length = 0;
}

template<class T>
void LinkedList<T>::insert(T newData)
{
	Node<T>* n = new Node<T>;
	n->data = newData;
	if(length == 0)
	{
		n->back = n;
		n->next = n;
		head = n;
		currNode = n;
	}
	else
	{
		n->back = currNode;
		n->next = currNode->next;
		currNode->next->back = n;
		currNode->next = n;
		currNode = currNode->next;
	}
	length++;
}

template<class T>
void LinkedList<T>::deleteNode()
{
	if(currNode == head)
	{
		head = currNode->next;
	}
	currNode->back->next = currNode->next;
	currNode->next->back = currNode->back;
	delete currNode;
	currNode = currNode->next;
	length--;
}

template<class T>
T LinkedList<T>::getCurr() const
{
	return currNode->data;
}

template<class T>
void LinkedList<T>::next()
{
	currNode=currNode->next;

}

template<class T>
void LinkedList<T>::previous()
{
	currNode = currNode->back;
}

template<class T>
int LinkedList<T>::getLength() const
{
	return length;
}

template<class T>
bool LinkedList<T>::isHead() const
{
	return currNode == head;
}
