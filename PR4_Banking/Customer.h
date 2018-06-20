#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>
using namespace std; 

/**
The Bank has Customers.  Each Customer has a name, address, age, and telephone number.
Additionally, there are specialized types of Customers: Adult, Senior, and Student.
Each type of Customer has its own checking and savings interest rates, 
as well as its own checking and overdraft fees.

@author: Ed Walker
*/
class Customer 
{
protected: 
	string name; 
	string address; 
	int age; 
	string phoneNumber;
	int customerID;
	string customerAccount; 

public: 
	Customer(string name_, int customerID_, string customerAccount_)
	{
		name = name_;
		customerAccount = customerAccount_;
		customerID = customerID_; 

	}
	void set_name(string Name) 
	{
		name = Name; 
	}
	string get_name()
	{
		return name; 
	}
	void set_address(string Address)
	{
		address = Address;
	}
	string get_address()
	{
		return address; 
	}
	void set_age(int Age )
	{
		age = Age; 
	}
	int get_age()
	{
		return age; 
	}
	void set_PhoneNumber(string phonenum)
	{
		phoneNumber = phonenum;
	}
	string get_Phonenum()
	{
		return phoneNumber; 
	}
	void set_customerID(int ID)
	{
		customerID = ID; 
	}
	int get_customerID()
	{
		return customerID; 
	}
	void set_customerAccount(string type)
	{
		customerAccount = type; 
	}
	string get_customerAccount()
	{
		return customerAccount;
	}

	virtual const double get_overdraftFees() = 0;
	virtual const double get_checkCharge() = 0;
	virtual const double get_savingsInterest() = 0;
	virtual const double get_checkingInterest() = 0;
};

class Adult : public Customer
{
public:
	Adult(string name_, int customerID_, string customerAccount_) : Customer(name_, customerID_, customerAccount_) {};
	double SAVINGS_INTEREST = 0.1;
	double CHECK_INTEREST = 0.1;
	double CHECK_CHARGE = 1.4;
	double OVERDRAFT_PENALTY = 35.0;

	const double get_overdraftFees() { return OVERDRAFT_PENALTY; }
	const double get_checkCharge() { return CHECK_CHARGE; }
	const double get_savingsInterest() { return SAVINGS_INTEREST; }
	const double get_checkingInterest() { return CHECK_INTEREST; }


};

class Senior : public Customer
{
public:
	Senior(string name_, int customerID_, string customerAccount_) : Customer(name_, customerID_, customerAccount_) {};
	double SAVINGS_INTEREST = 0.075;
	double CHECK_INTEREST = 0.075;
	double CHECK_CHARGE = 1.3;
	double OVERDRAFT_PENALTY = 25.0;

	const double get_overdraftFees() { return OVERDRAFT_PENALTY; }
	const double get_checkCharge() { return CHECK_CHARGE; }
	const double get_savingsInterest() { return SAVINGS_INTEREST; }
	const double get_checkingInterest() { return CHECK_INTEREST; }

};
class Student : public Customer
{
public:
	Student(string name_, int customerID_, string customerAccount_) : Customer(name_, customerID_, customerAccount_) {};
	double SAVINGS_INTEREST = 0.05;
	double CHECK_INTEREST = 0.05;
	double CHECK_CHARGE = 1.0;
	double OVERDRAFT_PENALTY = 20.0;

	const double get_overdraftFees() { return OVERDRAFT_PENALTY; }
	const double get_checkCharge() { return CHECK_CHARGE; }
	const double get_savingsInterest() { return SAVINGS_INTEREST; }
	const double get_checkingInterest() { return CHECK_INTEREST; }

};

#endif