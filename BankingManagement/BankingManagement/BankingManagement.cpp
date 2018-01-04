// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017
// BankingManagement.cpp : Main file for the account management system


#include "stdafx.h" 
#include "StockAccount.h" //using header StockAccount
#include "BankAccount.h"//using header BankAccount
#include <iostream>//using header iostream
#include <string>
#include <vector>
#include <string>

using namespace std;//using namespace std in the program
int main() //main program begins
{		
	int amount, choice1 = 0, choice2 = 0, choice3 = 0;  //initialized variables to 0 to store the user choices

	StockAccount objs; //object of StockAccount class
	BankAccount objb; //object of BankAccount class
	
	cout << "Welcome to Account Management System! \n"; //prompt for the welcome message
	while (choice1 != 3) //loop to let the user select the options, unless 3 is chosen (to exit) 
	{
		cout << "\n1. Stock Portfolio Account" //displays options
			<< "\n2. Bank Account"
			<< "\n3. Exit"
			<< "\nSelect Account to be Accessed : ";
		cin >> choice1; //stores the user entered number in choice1

		switch (choice1) //switch case for choice1
		{
		case 1: //case 1 when user wants to access the stock portfolio account
			objs.getBalanceFile();
			while (choice2 != 7)// loop to let user select the stock account menu options, unless user wants to go back to previous menu (selects 7)
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
				cin >> choice2; //stores user's choice of menu option from the stock portfolio menu
				cin.clear();
				fflush(stdin);
				string stock;
				int number;
				double price;
				double value;
				switch (choice2)
				{
				case 1://case 1 to get the stock value
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter the stock :";
					getline(cin, stock);
					cout << "Stock value is " << objs.getstock(stock) << endl;
					break;
				case 2://case 2 to display the portfolio
					objs.displayportfolio();
					break;
				case 3://case 3 to buy shares
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter the stock you want to buy :";
					getline(cin, stock);
					cout << "Please enter the number of stocks you want to buy: ";
					cin >> number;
					cout << "Please enter the price at which you wish to buy:";
					cin >> price;
					objs.buyshare(stock,number,price);
					break;
				case 4://case 4 to sell share
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter the stock you want to sell : ";
					getline(cin, stock);
					fflush(stdin);
					cout << "Please enter the number of stocks you want to sell: ";
					cin >> number;
					cout << "Please enter the price per stock at which you wish to sell :";
					cin >> price;
					objs.sellshare(stock,number,price);
					break;
				case 5://case 5 to plot graph
					cout << "Display graph here\n";
					objs.plotgraph();
					break; 
				case 6://case 6 to print transaction history
					objs.transaction_history();
					break;

				case 7://case 7  to break the file
					break;
				default://default option if wrong option is entered
					cout << "\nPlease Enter a Valid Option ";
				}
			}
			choice2 = 0;//choice2 is 0
			break;
		case 2: //case 2 when user selects to access the bank account
			objb.getBalanceFile();
			while (choice3 != 5)
			{
				cout << "\nBank Account"
					<< "\n1. View Account Balance"
					<< "\n2. Deposit Money"
					<< "\n3. Withdraw Money"
					<< "\n4. Print History"
					<< "\n5. Return to Previous Menu";
				cout << "\nPlease Enter Your Choice : ";
				cin >> choice3;
				switch (choice3)
				{
				case 1://case 1 to view balance
					objb.viewbalance();
					break;
				case 2://case 2 to deposit money
					cout << "Please enter the amount you want to deposit";
					cin >> amount;
					objb.deposit(amount);
					break;
				case 3://case 3 to withdraw money
					cout << "Please enter the amount you want to withdraw";
					cin >> amount;
					objb.withdraw(amount);
					break;
				case 4://case 4 to print transaction history
					objb.transaction_history();
					break;
				case 5:
					break;
				default://default case in case of wrong option
					cout << "\nPlease Enter a Valid Option";
				}
			}
			choice3 = 0;//choice 3 is 0
			break;

		case 3: //to exit the menu
			break; //break exits the menu
		default: //default case to prompt user to enter a valid option
			cout << "\nPlease Enter a Valid Option";
		}
	}
	return 0; //program terminates
}

