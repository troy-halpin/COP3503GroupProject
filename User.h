/********************************************************************
	User
	User.h contains the User class, an object that holds all the
	information and functionality of a user within our program, 
	inlcuding their name, username, password, salt, bank accounts,
	and associated methodology.
*********************************************************************
*/
#ifndef _USER_H
#define _USER_H

#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include <stdexcept>
#include "hash.h"
#include "FileManage.h"
#include "Account.h"

using namespace std;

class User
{
private:

	string userName;
	string hashedPassword;
	string userSalt;
	string realName;
	FileManage manager;
	string saltedAP;				// attepmted password + salt
	Account* userAccounts[3];
	int numberOfAccounts;

public:

	User(string realNameInput, string userNameInput, string pw) // new user
	{
		realName = realNameInput;
		userName = userNameInput;
		userSalt = generateSalt();
		string saltedPassword = pw += userSalt;
		hashedPassword = hashPassword(saltedPassword);
		saltedAP = "";
		numberOfAccounts = 0;
	}

	User(string realNameInput, string userNameInput, string realPass, string salt, string attemptedPass)	// existing user
	{
		realName = realNameInput;
		userName = userNameInput;
		hashedPassword = realPass;
		userSalt = salt;
		saltedAP = attemptedPass += userSalt;
		numberOfAccounts = 3 - manager.freeAccounts(userName);
	}

	string getUsername()
	{
		return userName;
	}

	string getRealName()
	{
		return realName;
	}

	/************************************************************
	
	generateSalt()
	Generates a psuedo-random number between 1 and 1000 and adds
	370 to it (arbitrary number). This value is returned as a
	string and padded to the password prior to hashing so that
	two users that happen to have the same password will almost 
	certainly not have the same hash stored in the database.
	*************************************************************
	*/

	string generateSalt()
	{
		/* initialize random seed: */
  		srand (time(NULL));
  		int saltInt = rand() % 1000 + 1;
  		saltInt += 370;
  		string salt = to_string(saltInt);

  		return salt;
	}

	string hashPassword(string originalPassword) 
	{
		string hashed;

		hashed = hash(originalPassword);

		return hashed;
	}

	string getHashedPassword()
	{
		return hashedPassword;
	}

	/************************************************************
	correctPassword()
	Test that occurs at login to verify that a user has entered
	a correct password to match his/her username. Takes the
	attempted password, appends the previsouly stored salt, 
	hashes it, and compares it to the previously stored hash.
	*************************************************************
	*/

	bool correctPassword()
	{
		string hashedAP = hashPassword(saltedAP);

		if (hashedAP == hashedPassword)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	/************************************************************
	
	infoExport()
	Takes all held information for the user and exports it to 
	the file manager class for writing to the database.
	*************************************************************
	*/

	void infoExport()
	{
		string accName2, bal2, accName3, bal3;

		string accName1 = userAccounts[0]->getAccountName();
		string bal1 = to_string(userAccounts[0]->getAccountBalance());	// change to string

		if (numberOfAccounts >= 2)
		{
			accName2 = userAccounts[1]->getAccountName();
			bal2 = to_string(userAccounts[1]->getAccountBalance());	// change to string
		}
		else	// An "*" represents the values for accounts that do not not yet exist (potential accounts)
		{
			accName2 = "*";
			bal2 = "*";
			accName3 = "*"; 
			bal3 = "*";
		}

		if (numberOfAccounts == 3)
		{
			accName3 = userAccounts[2]->getAccountName();
			bal3 = to_string(userAccounts[2]->getAccountBalance());	// change to string
		}

		manager.writeFile(userName, hashedPassword, realName, userSalt, accName1, bal1, accName2, bal2, accName3, bal3);
	}

	/************************************************************
	takeAccountsOnline()
	Initializes users bank accounts upon login. Takes read names
	and balances and uses them in the instatiation. Accounts
	are only created if they existed prior to login.
	*************************************************************
	*/

	void takeAccountsOnline(string accName1, string accName2, string accName3, string bal1, string bal2, string bal3)
	{
		double amount = string_to_double(bal1);

		userAccounts[0] = new Account(accName1, amount);

		if (numberOfAccounts >= 2)
		{
			amount = string_to_double(bal2);
			userAccounts[1] = new Account(accName2, amount);
		}
		if (numberOfAccounts == 3)
		{
			amount = string_to_double(bal3);
			userAccounts[2] = new Account(accName3, amount);
		}
	}

	void createNewAccount(string accountName)
	{
		if (numberOfAccounts < 3)
		{
			Account* currentAccount = new Account(accountName, 0.0);
			userAccounts[numberOfAccounts] = currentAccount;
			numberOfAccounts++;
		}
		else
		{
			throw invalid_argument("You cannot have more than 3 accounts."); // too many accounts
		}
	}

	// Returns only the default account (the first account created) at login
	Account* grabAccount()
	{
		return userAccounts[0];
	}

	/************************************************************
	grabAccount()
	This gives an account to the main that is used for all
	functionality (deposit, withdraw, transfer) until the user
	switches or logs out. This function also takes care of account
	switching, switching to the other available account if there
	are two total accounts and providing a menu and options if
	there are two more accounts a user can switch two. This is 
	done by checking for eqality against the current account's
	name.
	*************************************************************
	*/

	Account* grabAccount(string currentAccount)
	{
		int newAccountIndex = 0;
		int otherAccountIndex = 4;		// 4 is simply an arbitrary int that cannot be an index,
		int otherAccountIndex2 = 4;		// used to make sure that the otherAccount variables are not overwhited
		string otherAccounts[3];

		if (numberOfAccounts == 2)
		{
			if (userAccounts[0]->getAccountName() == currentAccount)
			{
				newAccountIndex = 1;
			}
			else
			{
				newAccountIndex = 0;
			}
		}
		else	// number of accounts = 3
		{

			for (int i = 0; i < 3; i++)
			{
				otherAccounts[i] = userAccounts[i]->getAccountName();
			}

			for (int i = 0; i < 3; i++)
			{
				if (otherAccounts[i] != currentAccount)
				{
					if (otherAccountIndex == 4)
					{
						otherAccountIndex = i;
					}
					else if (otherAccountIndex2 == 4)
					{
						otherAccountIndex2 = i;
					}
				}
			}

			string choice;
			cout << "1 - " << otherAccounts[otherAccountIndex] << endl << "2 - " << otherAccounts[otherAccountIndex2] << endl;
			cin >> choice;

			while (cin.fail() || ((choice != "1") && (choice != "2")))
			{																	
				cin.clear();
				cin.ignore(1000, '\n');											// catch bad user input
				cout << "\nEnter '1' or '2': ";
				cin >> choice;
			}

			if (choice == "1")
			{
				newAccountIndex = otherAccountIndex;
			}
			if (choice == "2")
			{
				newAccountIndex = otherAccountIndex2;
			}
		}

		return userAccounts[newAccountIndex];
	}

	int getNumberOfAccounts()
	{
		return numberOfAccounts;
	}

	/************************************************************
	to_string()
	overloaded functions that simply convert a number value,
	int or double, to a string so that it can be stored as such
	in the database or used to pad another string.
	*************************************************************
	*/

	string to_string(int num)
	{
		ostringstream numToString;
		numToString << num;
		return numToString.str() ;
	}

	string to_string(double num)
	{
		ostringstream numToString;
		numToString << num;
		return numToString.str() ;
	}

	double string_to_double(string str)
	{
		double num = 0.0;

    	stringstream stringToDouble;

    	stringToDouble << str;
    	stringToDouble >> num;

    	return num;
	}
};
#endif
