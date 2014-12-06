/********************************************************************

	User

	User.h contains the User class, an object that holds all the
	information and functionality of a user within our program, 
	inlcuding their name, username, password, salt, bank accounts,
	and associated methodology.

*********************************************************************
*/

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

	const string userName;
	const string hashedPassword;
	const string userSalt;
	const string realName;
	const FileManage manager;
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
		userSalt = salt;
		string realSaltedPass = realPass += userSalt;
		hashedPassword = hashPassword(realSaltedPass);
		saltedAP = attemptedPass += userSalt;
		numberOfAccounts = 3 - manager.freeAccounts();
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

		manager.writeFile(userName, hashedPassword, string realName, userSalt, accName1, bal1, accName2, bal2, accName3, bal3);
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
		double amount = stod(bal1);

		userAccounts[0] = new Account(accName1, bal1Double);

		if (numberOfAccounts >= 2)
		{
			amount = stod(bal2);
			userAccounts[1] = new Account(accName2, bal2);
		}
		if (numberOfAccounts == 3)
		{
			amount = stod(bal3);
			userAccounts[2] = new Account(accName3, bal3);
		}
	}

	void createNewAccount(string accountName)
	{
		if (numberOfAccounts < 3)
		{
			Account* currentAccount = new Account(accountName, 0.0);
			userAccounts[numberOfAccounts] = currentAccount;
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
	name and also against the null (nonexistant) account, "*".

	*************************************************************
	*/

	Account* grabAccount(string currentAccount)
	{
		int newAccountIndex = 0;
		int otherAccountIndex = 4;		// 4 is simply an arbitrary int that cannot be an index,
		int otherAccountIndex2 = 4;		// used to make sure that the otherAccount variables are not overwhited
		string otherAccount = "";
		string otherAccount2 = "";

		if (numberOfAccounts == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				if (userAccounts[i]->getAccountName() != currentAccount && userAccounts[i]->getAccountName() != "*")
				{
					newAccountIndex = i;
				}
			}
		}
		else	// number of accounts = 3
		{
			for (int i = 0; i < 3; i++)
			{
				if (userAccounts[i]->getAccountName() != currentAccount && userAccounts[i]->getAccountName() != "*")
				{
					if (otherAccount == "" && otherAccountIndex == 4)
					{
						otherAccount = userAccounts[i]->getAccountName();
						otherAccountIndex = i;
					}
					else
					{
						otherAccount2 = userAccounts[i]->getAccountName();
						otherAccountIndex2 = i;
					}
				}
			}

			string choice;
			cout << "1 - " << otherAccount << endl << "2 - " << otherAccount2 << endl;
			cin >> choice;

			if (choice == "1")
			{
				newAccountIndex = otherAccountIndex;
			}
			else if (choice == "2")
			{
				newAccountIndex = otherAccountIndex2;
			}
			else
			{
				throw invalid_argument("Please enter a digit, either '1' or '2'.");
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
};
