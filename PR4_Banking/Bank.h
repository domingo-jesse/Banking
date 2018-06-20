#ifndef BANK_H_
#define BANK_H_
#include <vector>
#include <stdexcept>
#include "Account.h"
#include "Customer.h"

/**
The CS273 Bank has Accounts and Customers

@author: Ed Walker
*/
class Bank
{
private:
	std::vector<Account *> accounts; // Bank HAS accounts
	std::vector<Customer *> customers;  // Bank HAS customers
	
	// Counters for generating unique account and customer IDs
	int account_id;
	int customer_id;


	/**
	Return a vector of accounts owned by the specified name of the customer.
	Remember a customer can have many accounts.  
	@param name The customer name 
	@return vector of account ids
	*/
	std::vector<int> find_accounts_by_name(std::string name)
	{
		std::vector<int> user_accounts;
		for (int j = 0; j < accounts.size(); j++)
		{
			//Object is pointing to the accounts of the customer
			Customer *C1 = accounts[j]->get_customer();
			Account *A1 = accounts[j];

			//Finds the customers ID
			int acct_id = A1->get_account();

			//Finds the customers name
			string name_ = C1->get_name();
			if (name_ == name)
			{
				user_accounts.push_back(acct_id);
			}
		}
		
		return user_accounts;
	}

	/**
	Find a customer based on his/her name
	@param name The customer name
	@return customer object if found, NULL otherwise
	*/
	Customer *find_customer(std::string name)
	{
		for (int i = 0; i < customers.size(); i++)
		{
			//Finds the customer (by name) in the database
			if (customers[i]->get_name() == name)
			{
				//Returns that customer
				return customers[i];
			}
		}
		return NULL;
	}

	/** 
	Add a new account to a customer object (irrespective of its specific type: adult, senior, or student)
	@param cust The customer object 
	@param account_type The account type, i.e. "savings" or "checking"
	@return the newly created account object
	*/
	Account * add_account (Customer *cust, std::string account_type)
	{
		Account *acct = NULL;
		string accountType = account_type;

		for (int i = 0; i < customers.size(); i++)
		{
			string name = cust->get_name();

			//Create a new account for an existing customer
			if (customers[i]->get_name() == name)
			{
				//Customer wants to create a savings account
				if (accountType == "savings")
				{
					//generate an account number
					++account_id;

					//Create a new Savings Account, passing in the cust (customer name, type) and new account number
					acct = new Savings_Account(cust, account_id);
					accounts.push_back(acct);
				}

				else if (accountType == "checking")
				{
					//generate an account number
					++account_id;

					//Create a new Checking Account, passing the the cuse (customer name, type) and new account number
					acct = new Checking_Account(cust, account_id);
					accounts.push_back(acct);
				}
			}
		}

		
		return acct;
	}

public:
	/** Constructor
	*/
	Bank() : account_id(1000), customer_id(1000) {}

	/**
	Add account for an existing user
	@param name The customer name
	@param account_type The account type, i.e. "checking" or "savings"
	@return the newly created account object if the customer exist, or NULL otherwise
	*/
	Account* add_account(std::string name, std::string account_type) 
	{
		Customer *cust = find_customer(name);
		if (cust == NULL)
			return NULL;
		return add_account(cust, account_type);
	}

	/** 
	Add account for new user.  This creates a new customer and adds an account to him/her.
	@param name Customer name
	@param address Customer address
	@param telephone Customer telephone number
	@param age Customer age
	@param cust_type Customer type, i.e. "adult", "senior" or "student"
	@param account_type Account type, i.e. "checking" or "savings"
	@return the newly created account object
	*/
	Account* add_account(std::string name, std::string address, std::string telephone, int age, 
		std::string cust_type, std::string account_type)
	{
		Customer *cust = NULL;

		if (cust_type == "senior")
		{
			//Create a new Senior Customer
			++customer_id;

			//Create a new Senior object with name, id and senior
			cust = new Senior(name, customer_id, cust_type);
		}
		else if (cust_type == "adult")
		{
			//Create a new Senior Customer
			++customer_id;

			//Create a new Adult object with name, id and senior
			cust = new Adult(name, customer_id, cust_type);
		}
		else
		{
			//Create a new Senior Customer
			++customer_id;

			//Create a new Student object with name, id and senior
			cust = new Student(name, customer_id, cust_type);
		}

		//Set the customers id that is being incremented.
		cust->set_customerID(customer_id);

		cust->set_name(name);
		cust->set_address(address);
		cust->set_PhoneNumber(telephone);
		cust->set_age(age);
		cust->set_customerAccount(account_type);
		

		customers.push_back(cust);
		return add_account(cust, account_type);
	}

	/**
	Make a deposit in an account identified by the account id
	@param acct_number	The account id
	@param amt			The amount to deposit
	*/
	void make_deposit(int acct_number, double amt) 
	{
		Account *acct = get_account(acct_number);
		if (acct) 
		{
			acct->deposit(amt);
		}
		else
		{
			std::cout << "Account " << acct_number << " could not be found. " << std::endl;
		}
	}

	/** 
	Make a withdrawal in an account identified by the account id
	@param acct_number	The account id
	@param amt			The amount to withdraw
	*/
	void make_withdrawal(int acct_number, double amt) 
	{
		Account *acct = get_account(acct_number);
		if (acct)
		{
			acct->withdraw(amt);
		}
		else
		{
			std::cout << "Account " << acct_number << " could not be found. " << std::endl;
		}

	}

	/**
	Get the list of account numbers associated with a user, identified by his/her name
	@param name The customer name
	@return vector of account ids
	*/
	std::vector<int> get_account(std::string name) 
	{
		return find_accounts_by_name(name);
	}

	/**
	Get the account object for an account identified by an account id
	@param acct_name The account id
	@return the account object if it exists, NULL otherwise
	*/
	Account *get_account(int acct_number)
	{
		for (size_t i = 0; i < accounts.size(); i++) {
			if (accounts[i]->get_account() == acct_number)
				return accounts[i];
		}
		return NULL;
	}
};

#endif
