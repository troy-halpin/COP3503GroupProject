#include <iostream>
#include <string.h>

using namespace std;

class Account{

	string accountName;
	double balance;

public:

	Account(string name, double bal) {

		accountName = name;
		balance = bal;
	}

	string getAccountName() {
		return accountName;
	}
	void setAccountName(string name) {
		accountName = name;
	}

	void setAccountBalance(double amt) {
		balance = amt;
	}
	double getAccountBalance() {
		return balance;
	}

	void withdraw(double amt) {

		if(amt > balance){
			cout<<"Error: You do not have enough in your account to withdraw that amount."<<endl;
		}
		else{
			balance -= amt;
			cout << "Successfully withdrawn: " << amt << " USD\n" << accountName << " Balance: " << balance << endl;
		}

	}

	void deposit(double amt) { 

		balance += amt;
		cout << "Successfully deposited: " << amt << " USD\n" << accountName << " Balance: " << balance << endl;

	}
};
