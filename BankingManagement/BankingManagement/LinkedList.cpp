// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017
// LinkedList.cpp 

#include "stdafx.h"
#include "LinkedList.h" //includes header file linkedlist
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std; //using namespace std

LinkedList::LinkedList():start(0),end(0) //constructor of linkedlist initializing the variables
{
	size = 0; //size of linkedlist 0 initially
	loadList();
	iter = 0;
}

bool LinkedList::createIterator() //creates iterator to iterate the linked list
{
	if (start == 0) //when there is no node, returns false
	{
		return false;
	}
	else //to start the iterator from the first node
	{
		iter = start;
		return true;
	}

}

bool LinkedList::next() //to move the iterator to the next node
{
	if (iter == 0) //if iterator doesnt point to any node, return false
	{
		return false;
	}
	if (iter != 0) //if the iterator points to some node, condition becomes true
	{
		iter = iter->ptr2; //moving the iterator to next node
		return true;
	}
	else // for any other condition, returns false
	{
		return false;
	}
}

int LinkedList::getNumber() //function to get the value of 'number' stored at the node pointed by iter
{
	if (iter != 0) //if condition is true, return the number, otherwise returns -1
	{
		return iter->number;
	}
	return -1;
}

string LinkedList::getStock()//function to get the value of 'stock' stored at the node pointed by iter
{
	if (iter != 0) //if condition is true, return the stock, otherwise returns empty string
	{
		return iter->stock;
	}
	return "";
}

void LinkedList::setIteratorZero() //function to set iterator to 0
{
	iter = 0; //sets iterator to 0
}

void LinkedList::addNode(string stock, int number) //defining addNode function 
{
	Node *Object1 =new Node(); //creating object of node
	Object1->number = number; //store the user entered number in object 1
	Object1->stock = stock; //store the user entered stock in object 1
	Object1->ptr1 = 0; //initializing the pointer1 of object 1, to 0
	Object1->ptr2 = 0;//initializing the pointer2 of object 1, to 0
	if (size == 0) //if the size of linked list is 0
	{
		start = Object1; //start points towards object1
		end = Object1;//end would point towards object1 too
		size+=1; //increase size by 1
		return; //returns
	}
	Node *temp=0; //initializing a variable temp pointer
	temp = start; //storing the start address of linked list in temp
	while (temp->ptr2 != 0) //loop to traverse temp from start to end of the linkedlist one by one 
	{
		if (temp->stock == stock) // if the stock in a node matched the stock entered by user condition becomes true
		{
			temp->number = temp->number + number; //adds the number of stock by the number given by user
			return;
		}
		temp = temp->ptr2; //moving temp to the next node
	}
	if (temp->stock == stock) //if the stock stored in temp happens to be the same as stock entered by user condition becomes true
	{
		temp->number += number; //adds the number of stocks entered by user to the number stored in the node (number of stocks) 
		return;
	}
	Object1->ptr1 = temp; // to store object1 at the end of linkedlist
	temp->ptr2 = Object1;
	end = Object1;
	size++; //increasing size of linkedlist by 1
}
bool LinkedList::delNode(string stock, int number) //function to delete node of linkedlist
{
	Node *temp=0; //initializing pointer temp with 0
	temp = start; //storing the start address of linkedlist in temp
	if (start == end) //if there is only 1 node in the linked list
	{
		temp = start; //storing the start address in temp
		if (temp->stock == stock)//if the stock stored in the temp is same as the stock passed by the user, condition becomes true
		{
			if (number <= temp->number) //if there are enough number of stocks in the node to be deleted 
			{
				temp->number = temp->number - number; //reduces the number of stock by the number passed by user
				if (temp->number == 0) //if there are 0 number of stock remaining, node is to be deleted
				{
					start = 0; //start would point to 0
					end = 0;//end would point to 0
					delete temp;//delete the node
					size--;//reduces size of linkedlist by 1
				}
				return true; //returns true
			}
			else //if there are not enough stocks in the node to be sold
			{
				cout << "You dont have sufficient stocks to sell" << endl; //prompts that stocks are not enough to be sold
				return false; //returns false
			}
		}
		else //if the node doesnt contain stocks of the user entered stock
		{
			cout << "You dont have stocks of " << stock << "to sell" << endl;
			return false; //returns false
		}
	}
	
	while (temp->ptr2 != 0) //while loop to traverse the temp through the linkedlist
	{
		if (temp->stock == stock) //if the stock in node matches the stock passed by user 
		{
			break; //breaks the traverse of temp
		}
		temp = temp->ptr2; //to pass temp to the next node
	}

	if (temp->ptr1 == 0) //if the node is the first node of linkedlist
	{	
		if (temp->stock == stock) //if the stock stpred in the node is same as the stock passed by user
		{
			if (number <= temp->number) //if there are enough stocks to be deleted
			{
				temp->number = temp->number - number; //reduces the existing number of stocks by the user entered value of number 
				if (temp->number == 0) //if no stock remains of the type, stock node has to be deleted
				{
					start = temp->ptr2; // start node would be the next node
					delete temp; //deletes temp
					size--;//reduces size
				}
				return true;//returns true
			}
			else //if there are not enough stocks to be sold
			{
				cout << "You dont have sufficient stocks to sell" << endl;
				return false; 
			}
		}
	}
	if (temp->stock == stock) //if the stock in temp matches the stock passed by the user
	{
		if (number <= temp->number) //if there are enough stocks to be sold
		{
			temp->number = temp->number - number; //reduces the number of stocks by user entered number of stocks to be deleted
			if (temp->number == 0) // if there remains no stock of the stock type, node has to be deleted
			{
				if (temp->ptr2 == 0) // when node to be deleted is last node
				{
					end = temp->ptr1; // end of linkedlist is going to be the just previous node 
					temp->ptr1->ptr2 = 0; //ptr 2 of the just previous node would be 0
					delete temp; //delete temp
					size--; //reduces size by 1
				}
				else // if the node to be deleted is not the last node
				{
					temp->ptr1->ptr2 = temp->ptr2;  // arranging neighbouring nodes pointers
					temp->ptr2->ptr1 = temp->ptr1;
					delete temp; //delete temp
					size--;
				}
			}
			return true; //return true
		}
		else //if there are not enough stocks to sell
		{
			cout << "You dont have sufficient stocks to sell" << endl;
			return false; //returns false
		}
	}
	else //if the stock entered by user doesnt exist in linkedlist
	{
		cout << "You dont have stocks of " << stock << "to sell" << endl;
	}
	return false; //returns false
}

double LinkedList::get_value(int file_number,string stock) //defining get value function
{
	if (file_number==1) //to open file 1
		input.open("Results_1.txt"); //opens file
	else //to open file 2
		input.open("Results_2.txt");
	vector<string> vec; //vector declared
	string buff; //buff string declared
	while (getline(input, buff)) //goes through the file line by line and stores in buff
	{
		vec.clear(); //clears vector
		istringstream token(buff); //using istringstream on buff
		for (string s; token >> buff;)
		{
			vec.push_back(buff); //input elements of buff in vector
		}
		if (vec[0] == stock) //if vec[0] matched the stock entered
		{
			input.close();
			return stod(vec[1]); //returns stock value, converted to double

		}
	}
	input.close();
	return 0.0; //returns 0.0
}

void LinkedList::sortList(int f) //sorting function
{
	double x, y; //declared variable
	srand(time(NULL)); //giving time seed
	if (start != NULL) // when linked list is not empty
	{
		int flag = 0; //created a flag variable
		Node *current = start; //created a current pointer to point to start node initially
		Node *prev = 0; //created another previous pointer to point to previous node
		Node *temp = NULL; // Node pointer temp which is null initially
		int choice = f;// choice of file


		for (int i = 0; i < size; i++) // this is the outer loop that will run till the end of linked list
		{
			while (current->ptr2 != 0)// inner loop for each pass through the linked list,executed until current pointer is the last node
			{
				temp = current->ptr2;// temp pointer pointing to current pointer's next node

				x = get_value(choice, current->stock)*current->number; // getting the value of current node's stock and multiplying with total number of stock for the current node
				y = get_value(choice, temp->stock)*current->number;// getting the value of current node's stock and multiplying with total number of stock for the next node
				//comparing stock value
				if ((current->number)*x < (temp->number)*y) // checking if the total value of current node is less than total value of next node
				{
					temp->ptr1 = current->ptr1;//if current node's value is less then we swap the node
					current->ptr1 = temp; // swapping the node
					current->ptr2 = temp->ptr2;

					flag = 1;//flag set to 1 to indicate change in node order

					if (current->ptr2 != NULL)//if current pointer is not the last node
					{
						current->ptr2->ptr1 = current;//point next node's ptr1 to current node
					}
					temp->ptr2 = current;//temp node's next pointer ptr2 set to current node

					if (prev != 0)// if previous node pointer is not zero
					{
						prev->ptr2 = temp;//previous node's next pointer will point to temp after swapping
					}
					prev = temp;//previous node is equal to temp node

					if (start == current)//if start node was the current node
					{
						start = temp;// start will point to temp node after swapping
					}
					if (current->ptr2 == 0)//if current node becomes the last node
					{
						end = current; //update end pointer to current node
					}
				}
				else // if current node's value is already greater than temp node's value
				{
					prev = current;//previous node pointer points to current
					current = current->ptr2;//current node pointer points to next node of current pointer
				}
			}

			if (flag == 0)// if there was no swapping which means list is already sorted then we will break out of the loop
			{
				break;//break out of the loop
			}
			else//if flag was not zero
			{
				prev = NULL;//previous node pointer will equal to null
				current = start;// current node will point to starting node
				flag = 0;// flag will again be set to zero
			}
		}
	}

}

void LinkedList::storeList()
{
	srand(time(NULL));
	output.open("storelinkedlist.txt");
	int f = rand() % 2 + 1;
	sortList(f);
	Node *temp = 0;
	temp = start;
	ostringstream convert;
	string num = "";
	while (temp != 0)
	{
		convert << temp->number;
		output << temp->stock + " " + convert.str() + '\n';
		temp = temp->ptr2;
	}
	output.close();
}

bool LinkedList::loadList()
{
	srand(time(NULL));
	input.open("storelinkedlist.txt");
	input.seekg(0, ios::end);
	int fileSize = input.tellg();
	if (!input.is_open() || fileSize == 0)
	{
		input.close();
		return false;
	}
	input.seekg(0, ios::beg);
	vector<string> load;
	string buff;
	while (getline(input, buff))
	{
		load.clear();
		istringstream token(buff);
		for (string s; token >> buff;)
		{
			load.push_back(buff);
		}
		addNode(load[0], stod(load[1]));
	}
	input.close();
	return true;
}



LinkedList::~LinkedList() //destructor
{
	storeList();
}
