#include "stdafx.h"
#include <iostream>
#include "BankAccount.h"
#include "Account.h"
#include <string>
#include <iomanip>

using namespace std;

BankAccount::BankAccount()
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
		cout << "Cannot retrieve data. Unable to open the CashBalance file" << endl;
	file.close();
	if (getCashBalance() == 0)
	{
		setCashBalance(10000);
	}
	updateCashBalance();
	file.open("bank_transaction_history.txt", ios::app);
	if (file.is_open())
	{
		file.seekg(0, ios::end); // put the "cursor" at the end of the file
		int length = file.tellg(); // find the position of the cursor
		if (length == 0) {
			file << left;
			file << setw(25);
			file << "Event";
			file << left;
			file << setw(25);
			file << "InitialAmount";
			file << left;
			file << setw(25);
			file << "Amount";
			file << left;
			file << setw(25);
			file << "FinalAmount";
			file << left;
			file << setw(25);
			file << "Date";
			file << "\n";
		}
	}
	file.close();

}

void BankAccount::getBalanceFile()
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
	file.close();
}

void BankAccount::updateCashBalance()
{
	fstream file;
	file.open("CashBalance.txt");
	file << getCashBalance();
	file.close();
}

BankAccount::~BankAccount()
{
	updateCashBalance();
}

void BankAccount::deposit(double amount)
{
	if (amount < 0)
	{
		cout << "Enter proper amount" << endl;
		return;
	}
	double value=getCashBalance();
	double newValue = value + amount;
	updateTransactionFile("DEPOSIT", value, amount, newValue);
	setCashBalance(newValue);
	updateCashBalance();
}
void BankAccount::withdraw(double amount)
{
	double value = getCashBalance();
	if (value < amount)
	{
		cout << "Insufficient Funds" << endl;
		return;
	}
	if (amount < 0)
	{
		cout << "Enter proper amount" << endl;
		return;
	}
	double newValue = value - amount;
	setCashBalance(newValue);
	updateTransactionFile("WITHDRAWL", value, amount, newValue);
	
	updateCashBalance();
}

void BankAccount::updateTransactionFile(string event, double initialValue, double amount, double newValue)
{
	fstream file;
	file.open("bank_transaction_history.txt", ios::app);
	
	if (file.is_open())
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
		string s(buffer); 
		file.flush();
		file<<"\n"<<left<<setw(25) << event << left << setw(25) << initialValue << left << setw(25) << amount << left << setw(25) << newValue << left << setw(25) << s;
		
	}
	file.close();
}



void BankAccount::transaction_history() 
{
	file.open("bank_transaction_history.txt", ios::in);
	string buff;
	while (getline(file, buff))
	{
		cout << buff<<endl;
	}
	file.close();
}

void BankAccount::viewbalance()
{
	cout << "Your Account Balance is: " << getCashBalance() << endl;
}