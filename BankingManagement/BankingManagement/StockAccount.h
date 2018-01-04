// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017

#pragma once
#include "LinkedList.h"
#include "Account.h"
#include <fstream> 
#include <iostream>

using namespace std;

class StockAccount :public Account//StockAccount class inheriting Account base class
{
public:
	StockAccount();//constructor
	~StockAccount();//destructor
	void getBalanceFile();//function to update the cash balance
	double getstock(string);//function to get the value of the stock
	void savePortfolioValue(double);//function to save the portfolio to file
	void sellshare(string, int, double);//function to sell the shares
	double getTotalPortfolioValue();//function to get the total portfolio value
	void displayportfolio();//function to display portfolio
	void updateCashBalance();//function to update cash balance everywhere
	void updateTransactionFile(string, string, int, double);//function to update transaction in file
	void plotgraph();//function to plot the graph
	void buyshare(string, int, double);//function to buy the sahres
	virtual void transaction_history();//function to print transaction history


private:
	LinkedList stockaccount;//linked list variable to store stock portfolio
	fstream file;//fstream variable to perform file operations
	ofstream output;
	ifstream input;

};

