#pragma once
class Account
{
public:
	
	double getCashBalance()
	{
		return cashbalance;
	}
	void setCashBalance(double cashbalance)
	{
		this->cashbalance = cashbalance;
	}
	
	virtual void transaction_history() = 0;

private:
	double cashbalance;

};

