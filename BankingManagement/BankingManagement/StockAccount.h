#pragma once
#include "LinkedList.h"
#include "Account.h"
#include <fstream> 
#include <iostream>

using namespace std;

class StockAccount :public Account
{
public:
	StockAccount();
	~StockAccount();
	void getBalanceFile();
	double getstock(string);
	void savePortfolioValue(double);
	void sellshare(string, int, double);
	double getTotalPortfolioValue();
	void displayportfolio();
	void updateCashBalance();
	void updateTransactionFile(string, string, int, double);
	void plotgraph();
	void buyshare(string, int, double);
	virtual void transaction_history();


private:
	LinkedList stockaccount;
	fstream file;

};

