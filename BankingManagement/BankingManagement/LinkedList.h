#pragma once
#include <string>
#include <iostream>

class Node {


public:
	friend class LinkedList;
	friend class LinkedListIterator;

	std::string getStock() {
		return stock;
	}

private:
	Node *ptr1;
	Node *ptr2;
	int number;
	std::string stock;

};

class LinkedList
{
public:
	friend class LinkedListIterator;
	void addNode(std::string, int);
	bool delNode(std::string,int);
	double get_value(int,std::string);
	bool createIterator();
	bool next();
	int getNumber();
	void setIteratorZero();
	std::string getStock();
	void storeList();
	void sortList(int);
	void loadlist();
	LinkedList();
	~LinkedList();
private:
	Node *iter;
	Node *start;
	Node *end;
	int size;
};

