#include "stdafx.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;
LinkedList::LinkedList():start(0),end(0)
{
	size = 0;
	iter = 0;
}

bool LinkedList::createIterator()
{
	if (start == 0)
	{
		return false;
	}
	else
	{
		iter = start;
		return true;
	}

}

bool LinkedList::next()
{
	if (iter == 0)
	{
		return false;
	}
	if (iter != 0)
	{
		iter = iter->ptr2;
		return true;
	}
	else 
	{
		return false;
	}
}

int LinkedList::getNumber() 
{
	if (iter != 0)
	{
		return iter->number;
	}
	return -1;
}

string LinkedList::getStock()
{
	if (iter != 0)
	{
		return iter->stock;
	}
	return "";
}

void LinkedList::setIteratorZero() 
{
	iter = 0;
}

void LinkedList::addNode(string stock, int number)
{
	Node *Object1 =new Node();
	Object1->number = number;
	Object1->stock = stock;
	Object1->ptr1 = 0;
	Object1->ptr2 = 0;
	if (size == 0)
	{
		start = Object1;
		end = Object1;
		size+=1;
		return;
	}
	Node *temp=0;
	temp = start;
	while (temp->ptr2 != 0)
	{
		if (temp->stock == stock)
		{
			temp->number = temp->number + number;
			return;
		}
		temp = temp->ptr2;
	}
	if (temp->stock == stock)
	{
		temp->number += number;
		return;
	}
	Object1->ptr1 = temp;
	temp->ptr2 = Object1;
	end = Object1;
	size++;
}
bool LinkedList::delNode(string stock, int number)
{
	Node *temp=0;
	temp = start;
	if (start == end)
	{
		temp = start;
		if (temp->stock == stock)
		{
			if (number <= temp->number)
			{
				temp->number = temp->number - number;
				if (temp->number == 0)
				{
					start = 0;
					end = 0;
					delete temp;
					size--;
				}
				return true;
			}
			else
			{
				cout << "You dont have sufficient stocks to sell" << endl;
				return false;
			}
		}
		else
		{
			cout << "You dont have stocks of " << stock << "to sell" << endl;
			return false;
		}
	}
	
	while (temp->ptr2 != 0)
	{
		if (temp->stock == stock)
		{
			break;
		}
		temp = temp->ptr2;
	}

	if (temp->ptr1 == 0)
	{	
		if (temp->stock == stock)
		{
			if (number <= temp->number)
			{
				temp->number = temp->number - number;
				if (temp->number == 0)
				{
					start = temp->ptr2;
					delete temp;
					size--;
				}
				return true;
			}
			else
			{
				cout << "You dont have sufficient stocks to sell" << endl;
				return false;
			}
		}
	}
	if (temp->stock == stock)
	{
		if (number <= temp->number)
		{
			temp->number = temp->number - number;
			if (temp->number == 0)
			{
				if (temp->ptr2 == 0)
				{
					end = temp->ptr1;
					temp->ptr1->ptr2 = 0;
					delete temp;
					size--;
				}
				else
				{
					temp->ptr1->ptr2 = temp->ptr2;
					temp->ptr2->ptr1 = temp->ptr1;
					delete temp;
					size--;
				}
			}
			return true;
		}
		else
		{
			cout << "You dont have sufficient stocks to sell" << endl;
			return false;
		}
	}
	else
	{
		cout << "You dont have stocks of " << stock << "to sell" << endl;
	}
	return false;
}

double LinkedList::get_value(int file_number,string stock)
{
	fstream file;
	if (file_number==1)
		file.open("Results_1.txt",ios::in);
	else
		file.open("Results_2.txt", ios::in);
	vector<string> vec;
	string buff;
	while (getline(file, buff))
	{
		vec.clear();
		istringstream token(buff);
		for (string s; token >> buff;)
		{

			vec.push_back(buff);
		}
		if (vec[0] == stock)
			return stod(vec[1]);
	}
	return 0.0;
}

void LinkedList::storeList()
{
	fstream file;
	file.open("storelinkedlist.txt", ios::out);
	Node *temp = 0;
	temp = start;
	ostringstream convert;
	string num = "";
	while (temp->ptr2 != 0)
	{
		convert << temp->number;
		file << temp->stock + " " + convert.str() + '\n';
		temp = temp->ptr2;
	}
	file.close();
}

void LinkedList::sortList(int f)
{
	double x, y;
	srand(time(NULL));
	if (start != NULL)
	{
		int flag = 0;
		Node *current = start;
		Node *prev = 0;
		Node *temp = NULL;
		int choice = f;


		for (int i = 0; i < size; i++)
		{
			while (current->ptr2 != 0)
			{
				temp = current->ptr2;

				x = get_value(choice, current->stock)*current->number;
				y = get_value(choice, temp->stock)*current->number;
				//comparing stock value
				if ((current->number)*x < (temp->number)*y)
				{
					temp->ptr1 = current->ptr1;
					current->ptr1 = temp;
					current->ptr2 = temp->ptr2;

					flag = 1;

					if (current->ptr2 != NULL)
					{
						current->ptr2->ptr1 = current;
					}
					temp->ptr2 = current;

					if (prev != 0)
					{
						prev->ptr2 = temp;
					}
					prev = temp;

					if (start == current)
					{
						start = temp;
					}
					if (current->ptr2 == 0)
					{
						end = current;
					}
				}
				else
				{
					prev = current;
					current = current->ptr2;
				}
			}

			if (flag == 0)
			{
				break;
			}
			else
			{
				prev = NULL;
				current = start;
				flag = 0;
			}
		}
	}

}

void LinkedList::loadlist()
{
	fstream file;
	file.open("storelinkedlist", ios::in);
	vector<string> load;
	string buff;
	while (getline(file, buff))
	{
		istringstream token(buff);
		for (string s; token >> buff;)
		{
			load.push_back(buff);
		}
		addNode(load[0], stod(load[1]));
	}
}
LinkedList::~LinkedList()
{
}
