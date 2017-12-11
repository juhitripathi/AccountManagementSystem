#pragma once

#include <string>
#include "LinkedList.h"
using namespace std;

class LinkedListIterator
{
public:
	LinkedListIterator(LinkedList);
	int getNumber();
	std::string getStock();
	bool next();
	~LinkedListIterator();
private:
	LinkedList obj;
	Node *current;
};

