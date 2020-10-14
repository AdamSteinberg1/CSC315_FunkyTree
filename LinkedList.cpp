#include "LinkedList.h"
#include <iostream>
#include "linelist.h"

LinkedList::LinkedList()
{
	length = 0;
}


void LinkedList::insert(T newData)
{
	if(length == 0)
	{
		Node<T>* n = new Node;
		n->data = newData;
		n->back = n;
		n->next = n;
		head = n;
		currNode = n;
	}
	else
	{
		Node<T>* n = new Node;
		n->data = newData;
		n->back = currNode;
		n->next = currNode->next;
		currNode->next->back = n;
		currNode->next = n;
		currNode = currNode->next;
	}
	length++;
}

void LinkedList::delete()
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


string LinkedList::getCurr() const
{
	return currLine->data;
}

void LinkedList::next()
{
	currNode=currNode->next;

}

void LinkedList::previous()
{
	currNode = currNode->back;
}

int LinkedList::getLength() const
{
	return length;
}

bool isHead()
{
	return currNode == head;
}
