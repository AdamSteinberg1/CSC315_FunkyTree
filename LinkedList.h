#pragma once
//class for a circular linkedList

template<class T>
struct Node
{
  T data;
	Node* next;
	Node* back;
};

template<class T>
class LinkedList
{
	public:
		LinkedList();
		void insert(T newData);
		void deleteCurr();
		void next();
		void previous();
		int getLength() const;
		T getCurr() const;

	private:
		Node<T>* currNode;
		int length;
};


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
void LinkedList<T>::deleteCurr()
{
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
