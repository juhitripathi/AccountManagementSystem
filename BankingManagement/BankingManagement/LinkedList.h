// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017

#pragma once
#include <string> 
#include <fstream>
#include <iostream>

class Node {// creating the node class


public:
	friend class LinkedList;// declaring LinkedList class as the friend class of Node class

	std::string getStock() {// function to get stock of the node
		return stock;//returns stock value
	}

private:
	Node *ptr1;//ptr1 to point to previous node
	Node *ptr2;//ptr2 to point to next node
	int number;// number to store number of stocks
	std::string stock;// stock to store stock symbol

};

class LinkedList//LinkedList class
{
public:
	void addNode(std::string, int);//function to add node to linked list or increment current node's value 
	bool delNode(std::string,int);// function to delete node of a linked list or delete the node's value
	double get_value(int,std::string);// function to get value of a stock
	bool createIterator();//function to create iterator for the linked list
	bool next();//function to move iterator to the next node
	int getNumber();//function to get number of stocks in the current node
	void setIteratorZero();//function to set iterator to starting node
	std::string getStock();//function to get the stock of the node
	void sortList(int);//function to sort the linked list
	void storeList();
	bool loadList();
	LinkedList();//linked list constructor
	~LinkedList();//linkedlist destructor
private:
		std::ifstream input;
		std::ofstream output;
		Node *iter;//iter pointer to iterate the linked list
		Node *start;//start pointer to point to the start of the linked list
		Node *end;//end pointer to point to the end of the linked list
		int size;//size variable to store current size of linked list
};

