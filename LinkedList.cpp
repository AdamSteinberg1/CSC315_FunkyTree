#include "LinkedList.h"
#include <iostream>
#include "linelist.h"

LinkedList::LinkedList()
{
	Node *head = new Node;
  head -> data =
  currNode = head;

}



void LineList::goToTop()
{
	// Post : Advances currLine to line 1
	if (currLine->back == NULL) //if we are at the top buffer
	{
		currLine = currLine->next;
	}
	else
	{
		while (currLine->back->info != topMessage)
		{
			currLine = currLine->back;
		}
	}
	currLineNum = 1;
}

void LineList::goToBottom()
{
	// Post : Advances currLine to last line
	if (currLine->next == NULL) //if we are at the bottom buffer
	{
		currLine = currLine->back;
	}
	else
	{
		while (currLine->next->info != bottomMessage)
		{
			currLine = currLine->next;
			currLineNum++;
		}
	}
}

void LineList::insertLine(string newLine)
{
	// post : newLine has been inserted after the current line
	if (currLine->info == bottomMessage)
		movePrevLine();
	LineNode* line = new LineNode;
	line->info = newLine;
	line->back = currLine;
	line->next = currLine->next;
	currLine->next->back = line;
	currLine->next = line;
	currLine = currLine->next;
	length++;
	currLineNum++;
}

void LineList::deleteLine()
{
	// post : deletes the current line leaving currentLine pointing to line following
	if (currLine->next != NULL && currLine->back != NULL) //if we are at the top or bottom buffer then do nothing
	{
		currLine->back->next = currLine->next;
		currLine->next->back = currLine->back;
		delete currLine;
		currLine = currLine->next;
		length--;
	}
}

void LineList::printList()
{
	LineNode* temp = currLine; //remember which line we had selected
	int tempNum = currLineNum; //remember what the current line number is

	goToTop();
	if (currLine->info == bottomMessage)
	{
		cout << "Your text file is empty." << endl;
	}
	else
	{
		while (currLine->next->info != bottomMessage)
		{
			cout << currLineNum << "> " << currLine->info << endl;
			currLine = currLine->next;
			currLineNum++;
		}
		cout << currLineNum << "> " << currLine->info << endl;
	}

	currLine = temp;
	currLineNum = tempNum;
}

string LineList::getCurrLine() const
{
	return currLine->info;
}

void LineList::moveNextLine()
{
	// Post : Advances currLine (unless already at last line)
	if (currLine->next != NULL)
	{
		currLine = currLine->next;
		currLineNum++;
	}

}

void LineList::movePrevLine()
{
	// Post : Advances currLine (unless already at last line)
	if (currLine->back != NULL)
	{
		currLine = currLine->back;
		currLineNum--;
	}
}

int LineList::getCurrLineNum() const
{
	return currLineNum;
}

int LineList::getLength() const
{
	return length;
}
