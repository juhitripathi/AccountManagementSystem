// Name: Juhi Tripathi
// Course: 16:332:503, Programming Finance
// Date: 12/11/2017

#pragma once

class Account //Abstract base class Account
{
public:
	
	double getCashBalance() //public member function to retrieve cashbalance
	{
		return cashbalance; //returns cashbalance value
	}
	void setCashBalance(double cashbalance) //function to set the cashbalance to the passed value of cashbalance
	{
		this->cashbalance = cashbalance; //sets the passed value of cashbalance in the private cashbalance variable 
	}
	
	virtual void transaction_history() = 0; //pure virtual function transaction history

private:
	double cashbalance; //private variable cashbalance 

};

