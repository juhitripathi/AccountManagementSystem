// BankingManagement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StockAccount.h"
#include "BankAccount.h"
#include <iostream>
#include <string>
#include <vector>
#include <string>

using namespace std;
int main()
{		
	BankAccount BA;
	StockAccount SA;

	int ch1 = 0;
	int ch2 = 0;
	int ch3 = 0;

	int amount;
	cout << "Welcome to Account Management System! \n";

	while (ch1 != 3)
	{
		cout << "\n1. Stock Portfolio Account"
			<< "\n2. Bank Account"
			<< "\n3. Exit"
			<< "\nSelect Account to be Accessed : ";
		cin >> ch1;

		switch (ch1)
		{
		case 1:
			SA.getBalanceFile();
			while (ch2 != 7)// Stock Account Options displaying till it returns to previous menu
			{
				cout << "\nStock Portfolio account"
					<< "\n1. Display the price for a Stock Symbol"
					<< "\n2. Display Current Portfolio"
					<< "\n3. Buy Shares"
					<< "\n4. Sell Shares"
					<< "\n5. View a Graph for the Portfolio Value"
					<< "\n6. View Transaction History"
					<< "\n7. Return to the Previous Menu";
				cout << "\nEnter Your Choice : ";
				cin >> ch2;
				cin.clear();
				fflush(stdin);
				string stock;
				int number;
				double price;
				double value;
				switch (ch2)
				{
				case 1:
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter the stock you want :";
					getline(cin, stock);
					cout << "Stock value is " << SA.getstock(stock) << endl;
					
					break;
				case 2:
					SA.displayportfolio();
					break;
				case 3:
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter the stock you want :";
					getline(cin, stock);
					cout << "Please enter the number: of stocks you want to buy: ";
					cin >> number;
					cout << "Please enter the price:";
					cin >> price;
					SA.buyshare(stock,number,price);
					break;
				case 4:
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter the stock you want :";
					getline(cin, stock);
					fflush(stdin);
					cout << "Please enter the number: of stocks you want to sell: ";
					cin >> number;
					cout << "Please enter the price:";
					cin >> price;
					SA.sellshare(stock,number,price);
					break;
				case 5:
					//cout << "Display graph here\n";
					//SA.plotgraph();
					break;
				case 6:
					SA.transaction_history();
					break;

				case 7:
					break;
				default:
					cout << "\nPlease Enter a Valid Option!";
				}
			}
			ch2 = 0;
			break;
		case 2:
			BA.getBalanceFile();
			while (ch3 != 5)
			{
				cout << "\nBank Account"
					<< "\n1. View Account Balance"
					<< "\n2. Deposit Money"
					<< "\n3. Withdraw Money"
					<< "\n4. Print History"
					<< "\n5. Return to Previous Menu";
				cout << "\nPlease Enter Your Choice : ";
				cin >> ch3;
				switch (ch3)
				{
				case 1:
					BA.viewbalance();
					break;
				case 2:
					cout << "Please enter the amount you want to deposit";
					cin >> amount;
					BA.deposit(amount);
					break;
				case 3:
					cout << "Please enter the amount you want to withdraw";
					cin >> amount;
					BA.withdraw(amount);
					break;
				case 4:
					BA.transaction_history();
					break;
				case 5:
					break;
				default:
					cout << "\nPlease Enter a Valid Option!";
				}
			}
			ch3 = 0;
			break;

		case 3:
			break;
		default:
			cout << "\nPlease Enter a Valid Option!";
		}
	}
	return 0;
}

