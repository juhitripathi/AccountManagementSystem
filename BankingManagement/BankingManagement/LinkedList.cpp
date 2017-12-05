#include "stdafx.h"
#include "LinkedList.h"


LinkedList::LinkedList()
{
	start = NULL;
	end = NULL;
	size = 0;
}

void LinkedList::addNode(int data)
{
	Node Object1;
	Object1.data = data;
	Object1.ptr1 = NULL;
	Object1.ptr2 = NULL;
	if (size == 0)
	{
		start = &Object1;
		end = &Object1;
		size++;
		return;
	}
	Node *temp;
	temp = start;
	while (temp->ptr2 != NULL)
	{
		temp = temp->ptr2;
	}
	
	Object1.ptr1 = temp;
	temp->ptr2 = &Object1;
	end = &Object1;
	size++;
}

LinkedList::~LinkedList()
{
}
