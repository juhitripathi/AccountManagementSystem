// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017

#pragma once
#include "LinkedList.h" //using header linkedlist
#include "Account.h" //using base class account header
#include <fstream>
#include <string>


class BankAccount:public Account //BankAccount class is a derived class of base class Account
{
public://public member functions
	BankAccount(); //consrtuctor
	~BankAccount();//destructor
	void getBalanceFile(); //function to get the cash balance from file
	void deposit(double);//function to deposit the money
	void withdraw(double);//function to withdraw the money
	virtual void transaction_history() ;//function to print the transaction history file
	void updateCashBalance();//function to update cash balance everywhere
	void viewbalance();//function to view balance
	void updateTransactionFile(std::string, double, double, double);//update the transaction file
private: //private member of class to access file
	std::ifstream input;
	std::ofstream output;//fstream variable to do file operations
};

