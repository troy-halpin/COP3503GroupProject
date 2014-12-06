#include <iostream>
//#include <stdlib.h>
#include <stdexcept>
#include "User.h"
#include "FileManage.h"
#include "Account.h"
#include "CurrencyConverter.cpp"
#include "InterestSimulator.cpp"
using namespace std;

int main(void){


	int x;
	cout<<"Welcome to the Personal Banking Software!"<<endl;
	cout<<endl;
	cout<<"Enter a Command: \n 1: Sign In \n 2: Sign Up \n 3: Exit Program" << endl;
	x = inputCzech();

	while (true) {
		if (x == 1){
			
			while (true) {

				string username;
				string password;
				cout<<"Enter your username."<<endl;
				getline(cin, username);
				cout<<"Enter your password."<<endl;
				getline(cin, password)
				try {
					User* user = czechUser(username, password); //checkUser
					break;
				} catch (exception &e) {
					cerr << e.what() << endl;
				}
			}

			cout << "Welcome " << user->getRealName() << "!\n" << endl;
			
			mainMenu(user);
		}
		else if (x == 2) {

			stirng name;
			string username;
			string password;
			int accountType;
			string accountName;


			while (true) {	
				cout<<"Enter your name."<< endl;
				cin>>name;
				cout<<"Enter your desired username."<<endl;
				cin>>username;
				cout<<"Please enter a password that is between 6 and 56 characters, exclusive." << endl;
				cin>>password;
				cout<<"Enter account type \n 1: Checkings \n 2: Savings"<<endl;
				accountType = inputCzech();
				cout << "What would you like to call this account?" << endl;
				cin >> accountName >> endl;

				try{
					User* user = czechUser(name, username, password, accountType, accountName);
					cout << user->getRealName() << ", thank you for choosing PBS for all your personal banking needs"
					break;
				} catch (exception &e) {
					cerr << e.what() << endl;
				}
			}
			mainMenu(user);
		}
		
		else if (x == 3) {
			if (!userLogOut) {
				cout << "Thank you for using PBS, have a nice day!" << endl;
				break;
			} else {
				break;
			}
		}

		else {
			cout << "Our apologies, but we don't recognize that command. Please try again." << endl;
		}
	}

	return 0;
}

void mainMenu(User* user) {

	Account* currAccount = user->grabAccount();

	cout << "In order to ensure that your operations are saved, please remember to fully log out when you are finished!" << endl;
	cout << "How can we help you today?" << endl;
	int x = 0;
	while (x != 8) {
		cout <<
		"=====================================\n
		Enter 1 to Check Balance\n 
		Enter 2 to Deposit Funds \n 
		Enter 3 to Withdraw Funds\n 
		Enter 4 to Transfer Funds\n 
		Enter 5 to Add a new Account\n 
		Enter 6 to Switch Accounts \n
		Enter 7 to run the Interest Simulator\n
		Enter 8 to Log Out\n
		=====================================" << endl;

		x = inputCzech();

		switch (x) {
			//At the end of most operations (ones that actually alter an account) the "user->infoExport()" function is called. This overwrites and saves the program.

	  		case 1:
	    		//check balance
	  			cout << "The balance in " << currAccount.getAccountName() << " is: " << currAccount.getAccountBalance() << endl;
	    		break;

	  		case 2:
	   			//deposit
	  			depositFunds(currAccount);
	  			//user->infoExport();
	   		 	break;

	   		case 3:
	   			//withdraw
	   			withdrawFunds(currAccount);
	   			//user->infoExport();
	   			break;

	   		case 4:
	   			//transfer
	   			/*  Special note-- This was originally a function in the account class, but we realized that having to transfer to another account involves
   			        having another account, which the account class is not equipped for. So the transfer function was placed here instead                */


	   			cout << "Welcome to our money transfer service. Currently, funds can only be moved between your accounts, not other user's.\n"
	   			"How much would you like to transfer? Please note that all transfers must be of values greater than or equal to $1" << endl;

	   			int amount = inputCzech();	
	   			

	   			cout << "\nExcellent, we will begin the transferring process now."

	   			if (amount > currAccount->getAccountBalance()) {

					cout << "Our apologies, there are insufficient funds in this account to complete this transfer" << endl;
					break;
				}

				if (user->getNumberOfAccounts() == 1) {

					cout << "You don't have another account to switch to! Adding another is simple and free, just select Option 5 at the main menu." << endl;
					break;
				} 

				if (user->getNumberOfAccounts() == 3) {

	   				cout << "Which account would you like to transfer funds to?" << endl;
	   			}
	   			//subtracting the transfer amount from current account's balance
	   			currAccount->setAccountBalance(currAccount->getAccountBalance() - amount);

				Account* temp = user->grabAccount(currAccount->getAccountName());
				temp->setAccountBalance(temp->getAccountBalance() + amount);

				cout << "Successfully transferred: " << amount << " USD from " << currAccount->getAccountName() << " to " << temp->getAccountName() << endl;
				cout << currAccount->getAccountName() << ": " << currAccount->getBalance() << endl;
				cout << temp->getAccountName() << ": " << temp->getAccountBalance() << endl;
				

				//user->infoExport();
	   			break;

	   		case 5:
	   			//add new account
	   			cout << "Thank you for opening a new account with us. What would you like to name it?" << endl;
	   			try {
	   				user->createNewAccount(name);
	   				cout << "Account creation complete. You can access your new account by selecting Option 6 at the main menu, and selecting your new account." << endl;
	   			} catch (exception& e) {
	   				cerr << e.what() << endl;
	   			}
	   			//user->infoExport();
	   			break;

	   		case 6:
	   			//switch accounts
	   			cout << "What accound would you like to switch to?" << endl;
	   			//List of accounts function
	   			int numAccts = user->getNumberOfAccounts();

	   			if (numAccts == 1) {

	   				cout << "You don't have another account to switch to! Adding another is simple and free, just select Option 5 at the main menu." << endl;

	   			} else if (numAccts == 2) {

	   				//tells the user class what account we are currently
	   				currAccount = user->grabAccount(currAccount->getAccountName());
	   				cout << "Operation complete, you are now accessing " << currAccount->getAccountName() << endl;
	   			} else {
	   				currAccount = user->grabAccount(currAccount->getAccountName())
				}
				//user->infoExport();
	   			break;

	   		case 7:
	   			//run interest simulator
	   			interestSimulator* i = createSimulator(a);		
		 		runSimulator(i);
				delete i;

	   			break;
	   		case 8:
	   			//logout
	   			cout << user->getRealName() << ", thank you for using the PBS. Have a great day!" << endl;
	   			//user->infoExport();
	   			userLogOut = true;
	   			break;
	   			
	  		default:
	   			cout << "Command unknown";
	   			break;
	    }
	}
}

//There are a lot of times where we take digit inputs from the user, so to make life easier I just wrote this to call each time we take in an input
int inputCzech() {
	int input;
	cin >> input;
    while ((cin.fail()) || (input < 1)) {
	    cin.clear();               
	    cin.ignore(10000, '\n');   
	    cout << "Sorry, your input was not valid, please try again" << endl;
	    cin >> input;
	}

	return input;
}

/********************************************************************
	
	The czechUser Methods

	These methods take care of the interim between the User class
	and the main function, created primarily for code organization
	and ease of class communication. The methods are overloaded
	for different methodology between new and existing users, much
	like the constructors of the User class. They handle calling the
	functions for checking username availability and existance, 
	reading the user information from the database, initializing the 
	User for the main, creating the User's bank accounts, and 
	determining password correctness.

*********************************************************************
*/

User* czechUser(string realName, string userName, string password, string accountName) // new user
{
	bool userExists = false;
	FileManage manager;

	// read file to see if username exists
	userExists = manager.findUsername();

	if (!userExists)
	{
		// use the new user constructor
		User* currentUser = new User(realName, userName, password);

		// create default bank account
		currentUser->createAccount(accountName);

		return currentUser;
	}
	else // another user has already claimed the username
	{
		throw invalid_argument("This username is unavailable.");
	}
}

User* czechUser(string userNameInput, string passwordInput) // existing user
{
	bool userExists = false;
	string password, realName, realPassword, userSalt, accName1, accName2, accName3, bal1, bal2, bal3;
	FileManage manager;

	// read file to see if username exists
	userExists = manager.findUsername(userNameInput);

	if (userExists)
	{
		// read in real password, real name, and user salt
		manager.readFile(userNameInput, &realPassword, &realName, &userSalt, &accName1, &bal1, &accName2, &bal2, &accName3, &bal3);

		User* currentUser = new User(realName, userNameInput, realPassword, userSalt, passwordInput);

		if (currentUser->correctPassword())
		{
			currentUser->takeAccountsOnline(accName1, accName2, accName3, bal1, bal2, bal3);

			return currentUser;
		}
		else
		{
			throw invalid_argument("You have entered an incorrect password.");
		}
	}
	else
	{
		throw invalid_argument("This username does not exist.");
	}
}
