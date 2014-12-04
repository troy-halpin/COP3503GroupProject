#include <iostream>
#include <string.h>

using namespace std;

class Account{

public:
	string accountName;
	int accountType;
	float balance;

	Account(string name, float bal, int type);

	float getAccountBalance();
	void setAccountBalance(float amt);
	string getAccountName();
	void setAccountName(string name);
	void withdraw(float amt);
	void deposit(float amt);
	void transfer(float amt, Account to);
	int getAccountType();



};
	Account::Account(string name, float bal, int type){
		accountName = name;
		balance = bal;
		accountType = type;
	}

	string Account::getAccountName(){
		return accountName;
	}
	void Account::setAccountName(string name){
		accountName = name;
	}

	int Account::getAccountType(){
		return accountType;
	}

	void Account::setAccountBalance(float amt){
		balance = amt;
	}
	float Account::getAccountBalance(){
		return balance;
	}

	void Account::withdraw(float amt){

		if(amt > balance){
			cout<<"Error: You do not have enough in your account to withdraw that amount."<<endl;
		}
		else{
			balance -= amt;
			cout<<"Successfully withdrawn: "<<amt<<"\n"<<accountName<<" Balance: "<<balance<<endl;
		}

	}

	void Account::deposit(float amt){ 

		balance += amt;
		cout<<"Successfully deposited: "<<amt<<"\n"<<accountName<<" Balance: "<<balance<<endl;

	}

	void Account::transfer(float amt, Account to){
	
		if(amt > balance){
			cout<<"Error: You do not have enough in your account to transfer that amount."<<endl;
		}
		else{
			balance -= amt;
			to.setAccountBalance(to.getAccountBalance()+amt);
			cout<<"Successfully transferred: "<<amt<<" from "<<accountName<<" to "<<to.getAccountName()<<endl;
			cout<<accountName<<": "<<balance<<endl;
			cout<<to.getAccountName()<<": "<<to.getAccountBalance()<<endl;
		}
	}

