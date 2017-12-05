#pragma once
class LinkedList
{
public:
	void addNode(int);
	void delNode(int);
	void printNode();
	
	LinkedList();
	~LinkedList();
private:
	Node *start;
	Node *end;
	int size;
};

class Node {
	
	friend class LinkedList;

private:
	Node *ptr1;
	Node *ptr2;
	int data;

};