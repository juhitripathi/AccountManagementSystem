#include "stdafx.h"
#include <sstream>
#include <time.h>
#include "StockAccount.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <string>
#include "LinkedListIterator.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )

#pragma comment( lib, "libeng.lib" )


#include "mex.h"
#include <engine.h>



using namespace std;

StockAccount::StockAccount()
{
	getBalanceFile();
	file.close();
	file.open("stock_transaction_history.txt", ios::app);
	if (file.is_open())
	{
		int file_length = file.tellg();
		if (!file_length) 
		{
			file << left;
			file << setw(25);
			file << "Event";
			file << left;
			file << setw(25);
			file << "Company-Symbol";
			file << left;
			file << setw(25);
			file << "Number";
			file << left;
			file << setw(25);
			file << "Price-per-share";
			file << left;
			file << setw(25);
			file << "Total value";
			file << left;
			file << setw(25);
			file << "Time";
			file << "\n";
		}
	
	}
	file.close();
}

void StockAccount::getBalanceFile()
{
	file.open("CashBalance.txt", ios::in);
	string buff;
	if (file.is_open())
	{
		while (getline(file, buff))
		{
			double value = stod(buff);
			setCashBalance(value);
		}

	}
	else
	{
		cout << "Cannot retrieve cash balance";
	}
	if (getCashBalance() == 0)
	{
		setCashBalance(10000);
	}
	updateCashBalance();
}
void StockAccount::transaction_history() 
{
	file.open("stock_transaction_history.txt", ios::in);
	string buff;
	while (getline(file, buff))
	{
		cout<< buff<<endl;
	}
}

void StockAccount::updateCashBalance()
{
	file.open("CashBalance.txt");
	file << getCashBalance();
	file.close();
}

StockAccount::~StockAccount()
{
	updateCashBalance();
}

void StockAccount::savePortfolioValue(double portvalue)
{
	fstream file;
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	string s(buffer);
	file.open("portfoliovalue.txt", ios::app);
	file << left << setw(25) << portvalue;
	file << buffer << endl;
}

double StockAccount::getTotalPortfolioValue()
{
	srand(time(NULL));
	double cashbalance = getCashBalance();
	int f;
	double val=0.0, total=0.0;
	stockaccount.setIteratorZero();
	stockaccount.createIterator();
	f = rand() % 2 + 1;
	do
	{
		if (stockaccount.getStock() == "")
			continue;
		val = stockaccount.get_value(f, stockaccount.getStock())*stockaccount.getNumber();
		total += val;

	} while (stockaccount.next());
	return cashbalance + total;
}

double StockAccount::getstock(string stock)
{
	fstream file;
	srand(time(NULL));
	double value=0.0;
	string buff, date, temp;
	int choosefile, i = 0;
	choosefile = (rand() % 2) + 1;
	if (choosefile == 1)
	{
		file.open("Results_1.txt", ios::in);
	}
	else
	{
		file.open("Results_2.txt", ios::in);
	}
	vector<std::string> vec;
	while (getline(file, buff))
	{
		vec.clear();
		istringstream token(buff);
		for (string s; token >> buff;)
		{
			vec.push_back(buff);
		}
		if (vec[0] == stock)
		{
			file.close();
			return stod(vec[1]);
		}
	}
	cout << "There is no stock with this symbol";
	return NULL;
}

void StockAccount::buyshare(string stock, int number, double price)
{
	double value = 0.0,temp=0.0;
	value = getstock(stock);
	if (value == NULL)
		return;
	temp = value*number; 
	if (temp <= price)
	{ //check if getcashbalance gives amount that is greater than temp
		if (getCashBalance() > temp)
		{
			double buy = getCashBalance() - temp;
			setCashBalance(buy);
			updateCashBalance();
			cout << "You have purchased " << number << " shares of " << stock << " at $ " << value << " each for a total of $ " << temp << "." << endl;
			stockaccount.addNode(stock, number);
			updateTransactionFile("BUY", stock, number, value);
			savePortfolioValue(getTotalPortfolioValue());
		}
		else
			cout << "You cannot buy " << number << " shares, with " << price << " amount. Insufficient Amount in Account " << endl;
	}
	else
		cout << "You cannot buy " << number << "shares, with " << price << "amount. Insufficient Amount Proposed" << endl;
}

void StockAccount::updateTransactionFile(string event, string company, int number, double value)
{
	file.open("stock_transaction_history.txt", ios::app);
	if (file.is_open())
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
		string s(buffer);
		file << left;
		file << setw(25);
		file << event;
		file << left;
		file << setw(25);
		file << company;
		file << left;
		file << setw(25);
		file << number;
		file << left;
		file << setw(25);
		file << value;
		file << left;
		file << setw(25);
		file << value * number;
		file << left;
		file << setw(25);
		file << s;
		file << "\n";
		file.close();
	}
}


void StockAccount::sellshare(string stock, int number, double price)
{ //check if stock is there in the linked list or not,if present then the number of stock is greater then the amount supplied or not
	double value = 0.0,temp=0.0;
	value = getstock(stock);
	if (value == NULL)
		return;
	if (value >= price)
	{
		if (stockaccount.delNode(stock, number))
		{
			temp = value*number;
			double sell = getCashBalance() + temp;
			cout << "You have sold " << number << "shares of" << stock << "at $ " << value << "each for a total of $ " << temp << "." << endl;
			setCashBalance(sell);
			updateTransactionFile("SELL", stock, number, value);
			updateCashBalance();
			savePortfolioValue(getTotalPortfolioValue());
		}
	}
	else if (value > price)
	{
		cout << "Price per stock is less than the amount to sell for" << endl;
	}
	else
	{
		cout << "Not sufficient stocks to be sold" << endl;
	}

}

void StockAccount::displayportfolio()
{
	srand(time(NULL));
	int f = rand() % 2 + 1;
	double total = 0.0;
	double val = 0.0;
	stockaccount.sortList(f);
	cout << "Cash Balance = $" << getCashBalance() << endl;
	stockaccount.setIteratorZero();
	stockaccount.createIterator();
	cout << left << setw(25) << "Company-Symbol" << left << setw(25) << "Number" << left << setw(25) << "Price-per-share" << left << setw(25) << "Total value" << endl;
	do
	{
		if (stockaccount.getStock()=="")
			continue;
		val = stockaccount.get_value(f, stockaccount.getStock())*stockaccount.getNumber();
		cout << left << setw(25) <<stockaccount.getStock();
		cout << left << setw(25) <<stockaccount.getNumber();
		cout << left << setw(25) << "$" + std::to_string(stockaccount.get_value(f,stockaccount.getStock()));
		cout << left << setw(25) << "$" +std::to_string(val);
		cout << endl;
		total += val;

	} while (stockaccount.next());
	cout << "Total portfolio value" << getCashBalance()+total << endl;
}

void StockAccount::plotgraph() {
	/*
	fstream file;
	file.open("portfoliovalue.txt", ios::app);
	vector<std::string> tempvec;
	double portfoliovalue[100];
	string time[100];
	int num1 = 100,count=0;
	string buff;
	while (getline(file, buff))
	{
		tempvec.clear();
		istringstream token(buff);
		for (string s; token >> buff;)
		{
			tempvec.push_back(buff);
		}
		if (count < 100) {
			portfoliovalue[count] = stod(tempvec[0]);
			time[count] = tempvec[1];
			count += 1;
		}
		else
			break;
	}
	cout << "Potfolio Value" << "\t\t" << "Date & Time" << endl;
	for (int i = 0; i < num1; i++)
	{
		cout << "$" << portfoliovalue[i] << "\t\t" << time[i] << endl;
	}

	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error: Not Found." << endl;
		exit(1);
	}

	// create mxArray and copy arrays into it
	mxArray *A;
	A = mxCreateDoubleMatrix(1, num1, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)portfoliovalue, num1 * sizeof(double));
	engPutVariable(ep, "yy", A);

	// plotting function.
	engEvalString(ep, "plot(yy);");
	

	//  title for graph
	engEvalString(ep, "title('Portfolio Value Variation graph');");

	mxDestroyArray(A); // destroy mxArray 
	*/

}