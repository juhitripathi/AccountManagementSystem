#pragma once
#include "LinkedList.h"
#include "Account.h"
#include <fstream>
#include <string>


class BankAccount:public Account
{
public:
	BankAccount();
	~BankAccount();
	void getBalanceFile();
	void deposit(double);
	void withdraw(double);
	virtual void transaction_history() ;
	void updateCashBalance();
	void viewbalance();
	void updateTransactionFile(std::string, double, double, double);
private:
	std::fstream file;
};

