// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017

#pragma comment( lib, "libmx.lib" ) //library files for plotgraph function
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )


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
#include "engine.h"
#include "engine.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#include "mex.h" //using header for plotgraph function
#include <engine.h>



using namespace std;

StockAccount::StockAccount() // stock account constructor
{
	getBalanceFile();//getting the current cash balance of the customer
	
}

void StockAccount::getBalanceFile()//function to get and set the cash balance from the file
{
	input.open("CashBalance.txt");//opening CashBalance file in input mode
	string buff;//creating a string buffer
	if (input.is_open())//opening the file
	{
		while (getline(input, buff))//getting the cashbalance value from file
		{
			double value = stod(buff);//converting cash balancce value to double
			setCashBalance(value);//setting the cash balance value
		}

	}
	else//if file not open
	{	
		output.open("CashBalance.txt");
		output << 10000;
		setCashBalance(10000);
		output.close();
	}
	input.close();
}

void StockAccount::transaction_history() //function to view the transaction history of the fiel
{
	ifstream input;
	input.open("stock_transaction_history.txt",ios::app);//open the transaction history file
	if (input.is_open())
		cout << "Open";
	string buff;//create string buffer
	cout << left<<setw(25)<< "Event"<< left<< setw(25) << "Company-Symbol"<< left<< setw(25)<< "Number" << left << setw(25)<< "Price-per-share" << left << setw(25)<< "Total value"<< left << setw(25)<< "Time"<< "\n";
	while (getline(input, buff))//get contents of file line by line
	{
		cout<< buff<<endl;//output contents of buffer
	}
	input.close();
	
}

void StockAccount::updateCashBalance()//function to write cash balance to the file
{
	output.open("CashBalance.txt");//opening the cash balance file
	output << getCashBalance();//input the current cash balance to the file
	output.close();//close the file
}

StockAccount::~StockAccount()//stock account destructor
{
	updateCashBalance();//update the cash balance file before being destroyed
	input.close();
	output.close();
	input.clear();
	output.clear();
}

void StockAccount::savePortfolioValue(double portvalue)//function to save the portfolio value
{
	time_t rawtime;//time_t variable
	struct tm timeinfo;//structure to store time info
	char buffer[80];//creating a character buffer of length 80
	time(&rawtime);//passing address of rawtime to time function
	localtime_s(&timeinfo, &rawtime);//calling localtime_s function 
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);//converting the time into day-month-year Hour-minute-second format
	string s(buffer);//passing buffer to string object s as parameter
	output.open("portfoliovalue.txt", ios::app);//opening portfoliovalue file
	output << left << setw(25) << portvalue;//outputting portvalue to file
	output << buffer << endl;//outputting time value to file
	output.close();
}

double StockAccount::getTotalPortfolioValue()// function to get the total value of current portfolio
{
	srand(time(NULL));//providig time seed to rand function
	double cashbalance = getCashBalance();//calling th egetcashbalance function
	int f;//integer variable to choose the file
	double val=0.0, total=0.0;//created 2 variable
	stockaccount.setIteratorZero();//setting the iterator of th elinked list to zero
	stockaccount.createIterator();//creating the iterator
	f = rand() % 2 + 1;//choosing a file randomly
	do
	{
		if (stockaccount.getStock() == "")//if no stock
			continue;//continue to the loop
		val = stockaccount.get_value(f, stockaccount.getStock())*stockaccount.getNumber();//getting the value of current node through iterator
		total += val;//total variable that adds the total value of each node

	} while (stockaccount.next());//loop to iterate the list
	return cashbalance + total;//returning cash balance + total portfolio value
}

double StockAccount::getstock(string stock)//function to retrieve the stock from one file at random
{
	srand(time(NULL));//supplying time seed
	double value=0.0;//creating a variable
	string buff, date, temp;//string variables buff date and temp
	int choosefile, i = 0;//choosefile to choose file
	choosefile = (rand() % 2) + 1;//choosing a file at random
	if (choosefile == 1)//if choosing fisrst file to retreive stock value
	{
		input.open("Results_1.txt", ios::in);//open the first stock file
	}
	else//otherwise
	{
		input.open("Results_2.txt", ios::in);//open the second stock file
	}
	vector<std::string> vec;//created a vec variable
	while (getline(input, buff))//getting contents line by line
	{
		vec.clear();//clear the contents of the vector 
		istringstream token(buff);//istringstrema object token with parameter buff
		for (string s; token >> buff;)
		{
			vec.push_back(buff);//supplying stock symbol and stock value to the vector
		}
		if (vec[0] == stock)//if stock symbpol is the one we want
		{
			input.close();//close the file
			return stod(vec[1]);//return the value of the stock by conversion to double
		}
	}
	cout << "There is no stock with this symbol";//if no symbol found then output no symbol
	input.close();
	return NULL;//return NULL
}

void StockAccount::buyshare(string stock, int number, double price)//function to buy shares
{
	double value = 0.0,temp=0.0;
	value = getstock(stock);//get the value of the stock
	if (value == NULL)//if no stocck with that symbol 
		return;//return the control to the calling function
	temp = value*number; //temp is total i.e value of stock*number
	if (temp <= price)//if temp is less than equal to price
	{ 
		if (getCashBalance() > temp)//if wee have sufficient amount to buy the stock
		{
			double buy = getCashBalance() - temp;//buy the stock and deduct the amount from our cashbalance
			setCashBalance(buy);//set the new cash balance
			updateCashBalance();//update cash balance to the file
			cout << "You have purchased " << number << " shares of " << stock << " at $ " << value << " each for a total of $ " << temp << "." << endl;//output the purchase
			stockaccount.addNode(stock, number);//add the node of the current transaction
			updateTransactionFile("BUY", stock, number, value);//update theis event in transaction file
			savePortfolioValue(getTotalPortfolioValue());//update the event in portfoliovalue file
		}
		else//if we don't have the sufficient cash balance to buy the stock
			cout << "You cannot buy " << number << " shares, with " << price << " amount. Insufficient Amount in Account " << endl;//output the error message
	}
	else//if tempis greater than price
		cout << "You cannot buy " << number << "shares, with " << price << "amount. Insufficient Amount Proposed" << endl;//output error message
}

void StockAccount::updateTransactionFile(string event, string company, int number, double value)//funtion to update the transaction file
{
	output.open("stock_transaction_history.txt", ios::app);//open the transaction history file

	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	string s(buffer);
	output << left;
	output << setw(25);
	output << event;//output event to file
	output << left;
	output << setw(25);
	output << company;//output company symbol
	output << left;
	output << setw(25);
	output << number;//output number of stocks
	output << left;
	output << setw(25);
	output << value;//output value
	output << left;
	output << setw(25);
	output << value * number;//output totla value
	output << left;
	output << setw(25);
	output << s;//output date and time
	output << "\n";
	output.close();

}


void StockAccount::sellshare(string stock, int number, double price)//function to sell the shares of the stock
{ 
	double value = 0.0,temp=0.0;
	value = getstock(stock);//get the value of the stock
	if (value == NULL)//if value of stock is null
		return;//return to caller
	if (value >= price)//if value of stock is less than the price supplied
	{
		if (stockaccount.delNode(stock, number))//delete or modify the corresponding node
		{
			temp = value*number;//total value of the stock
			double sell = getCashBalance() + temp;//add the amount after selling to our cash balance
			cout << "You have sold " << number << "shares of" << stock << "at $ " << value << "each for a total of $ " << temp << "." << endl;//output the sell message
			setCashBalance(sell);//set the cash balance with the new value
			updateTransactionFile("SELL", stock, number, value);//update the new sell event in the transaction history file
			updateCashBalance();//update cash balance in the file
			savePortfolioValue(getTotalPortfolioValue());//save the total portfolio in portfoliovalue file
		}
	}
	else if (value > price)//if value is greater than price
	{
		cout << "Price per stock is less than the amount to sell for" << endl;//output the error message
	}
	else//otherwise
	{
		cout << "Not sufficient stocks to be sold" << endl;//output error message
	}

}

void StockAccount::displayportfolio()//function to display the portfolio 
{
	srand(time(NULL));//providing time seed to rand function
	int f = rand() % 2 + 1;//choosing a file at random
	double total = 0.0,tot =0.0;
	double val = 0.0;
	string stock;
	int number;
	stockaccount.sortList(f);//sort the list
	cout << "Cash Balance = $" << getCashBalance() << endl;//output the current cash balance
	stockaccount.setIteratorZero();//set the iterator to zero
	stockaccount.createIterator();//create an iterator of the list
	cout << left << setw(25) << "Company-Symbol" << left << setw(25) << "Number" << left << setw(25) << "Price-per-share" << left << setw(25) << "Total value" << endl;//output the transaction with proper formatting
	do
	{
		if (stockaccount.getStock()=="")//if stockvalue is null
			continue;//continue
		//cout <<"Total value: "<< stockaccount.get_value(f, stockaccount.getStock()) << endl;
		//cout << "Number: "<<stockaccount.getNumber() << endl;
		stock = stockaccount.getStock();
		number = stockaccount.getNumber();
		val = stockaccount.get_value(f, stock);
		tot = val*number;//get the total stock value of the stock
		cout << left << setw(25) <<stock;//get the stock
		cout << left << setw(25) <<number;//get the number of corresponding stocks
		cout << left << setw(25) << "$" + std::to_string(val);//output the current value of stock
		cout << left << setw(25) << "$" +std::to_string(tot);//output the total value of stock
		cout << endl;
		total += val;

	} while (stockaccount.next());//loop to traverse the linked list using iterator
	cout << "Total portfolio value $" << getCashBalance()+total << endl;//output the total portfolio value
}



void StockAccount::plotgraph() {
	
	input.open("portfoliovalue.txt");
	vector<std::string> tempvec;
	double portfoliovalue[100] = {0.0};
	string time[100];
	int num1 = 100,count=0;
	string buff;
	while (getline(input, buff))
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
	cout <<left<<setw(25)<< "Potfolio Value" << left << setw(25) << "Date & Time" << endl;
	for (int i = 0; i < num1; i++)
	{
		cout <<left << setw(25) << "$" + std::to_string(portfoliovalue[i]) << left << setw(25) << time[i] << endl;
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
	input.close();
} 