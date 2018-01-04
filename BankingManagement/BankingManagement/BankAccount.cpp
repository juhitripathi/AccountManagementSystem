// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017

#include "stdafx.h"
#include <iostream>
#include "BankAccount.h"
#include "Account.h"
#include <string>
#include <iomanip>

using namespace std;

BankAccount::BankAccount()//BankAccount constructor
{
	input.open("CashBalance.txt");//open CashBalance file
	string buff;//created a string buffer
	if (input.is_open())//if the file is open
	{
		while (getline(input, buff))//get contents of the file to buff
		{
			double value = stod(buff);//convert value of buff to double
			setCashBalance(value);//set the cash balance with this value
		}
		
	}
	else//if not able to open the file
	{
		output.open("CashBalance.txt");
		output << 10000;
		output.close();
		setCashBalance(10000);
		cout << "Cannot retrieve data. Unable to open the CashBalance file" << endl;//output error message
	}
	input.close();//close the file
	
}

void BankAccount::getBalanceFile()//get balance file function to get the cash balance from file
{
	input.open("CashBalance.txt");//open the CashBalance file
	string buff;//create a string buffer
	if (input.is_open())//if file is open
	{
		while (getline(input, buff))//get contents of the file
		{
			double value = stod(buff);//convert the contents to double
			setCashBalance(value);//set the cash balance
		}
		
	}
	else//if not able to open the file
	{
		output.open("CashBalance.txt");
		output << 10000;
		output.close();
		setCashBalance(10000);
	}
	input.close();//close the file
}

void BankAccount::updateCashBalance()//functionto update the cash balance
{
	output.open("CashBalance.txt");//open cash balance file
	output << getCashBalance();//output the cash balance to file
	output.close();//close the file
}

BankAccount::~BankAccount()//BankAccount destructor
{
	updateCashBalance();//update cash balance before destroying
}

void BankAccount::deposit(double amount)//function to deposit the amount
{
	if (amount < 0)//if amount is less then zero
	{
		cout << "Enter proper amount" << endl;//output error message
		return;//return
	}
	double value=getCashBalance();//get the cash balance
	double newValue = value + amount;//get the newvalue after depositing money
	updateTransactionFile("DEPOSIT", value, amount, newValue);//update the transaction file
	setCashBalance(newValue);//set new cash balance
	updateCashBalance();//update cash balance in file
}
void BankAccount::withdraw(double amount)//withdraw amount from bank
{
	double value = getCashBalance();//get the cash balance value
	if (value < amount)//if  value is less than amount
	{
		cout << "Insufficient Funds" << endl;//output the message
		return;//return to caller
	}
	if (amount < 0)//if amount is less than 0
	{
		cout << "Enter proper amount" << endl;//output proper message
		return;//return to caller
	}
	double newValue = value - amount;//deduct the amount withdrawn
	setCashBalance(newValue);//set new value of cash balance
	updateTransactionFile("WITHDRAWL", value, amount, newValue);//update the transaction file
	
	updateCashBalance();//update the cash balance to file
}

void BankAccount::updateTransactionFile(string event, double initialValue, double amount, double newValue)//function to update transaction file
{
	output.open("bank_transaction_history.txt", ios::app);//open transaction history file
	time_t rawtime;//calculate time
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	string s(buffer); 
	output.flush();
	output<<"\n"<<left<<setw(25) << event << left << setw(25) << initialValue << left << setw(25) << amount << left << setw(25) << newValue << left << setw(25) << s;//output all the values to the file
	output.close();//close the file
}



void BankAccount::transaction_history()//function to print transaction history 
{
	input.open("bank_transaction_history.txt", ios::in);//open the transaction history file
	string buff;//create string buff
	cout << left << setw(25)<< "Event"<< left<< setw(25) << "InitialAmount"<< left << setw(25)<< "Amount" << left << setw(25)<< "FinalAmount" << left << setw(25)<< "Date"<< "\n";
	while (getline(input, buff))//get contents of file line by line
	{
		cout << buff<<endl;//output contents of buff
	}
	input.close();//close the file
}

void BankAccount::viewbalance()//function to view balance
{
	cout << "Your Account Balance is: " << getCashBalance() << endl;//output the balance
}