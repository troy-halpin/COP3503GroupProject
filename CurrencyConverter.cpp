#include "currencyConverter.h"
#include "Account.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

unsigned int getCurrency()								// function that determines the currency from user input
{
	string input = "";
	unsigned int currencyChoice = 0;
	
	while (true)
	{
		cout << "\nChoose currency (Enter a number 1-10):\n" << 	
		"	(1) Euros\n" <<
		"	(2) British Pounds\n" <<
		"	(3) Indian Rupees\n" <<
		"	(4) Australian Dollars\n" <<
		"	(5) Canadian Dollars\n" <<							// lists currency options
		"	(6) Singapore Dollars\n" <<
		"	(7) Brazilian Reals\n" <<
		"	(8) Mexican Pesos\n" <<
		"	(9) South African Rands\n" <<
		"	(10) Japanese Yen\n" << endl;

		cout << "Choice: ";										// get currency choice
		getline(cin, input);
		stringstream ss1(input);

		if (ss1 >> currencyChoice)									// checks that input is a positive number or 0
		{
			if ((currencyChoice > 0) && (currencyChoice < 11))		// checks that input is between 1 and 10
			{
				break;
			}
		}

		cout << "You must enter a number between 1 and 10 to choose a currency." << endl;		// prints if input is bad
	}

	return currencyChoice;	
}

double roundValue(double newAmount)							// rounds amount to 2 or less decimal places
{
	if (fmod((newAmount * 1000.0), 10.0) > 5.0)
	{
		newAmount = ceil(newAmount * 100);					// rounds up
		newAmount = newAmount / 100;
	}

	else if (fmod((newAmount * 1000.0), 10.0) <= 5.0)
	{
		newAmount = floor(newAmount * 100);					//rounds down
		newAmount = newAmount / 100;
	}

	return newAmount;
}

double convert_To(unsigned int currencyChoice, currencyConverter* cc)	// function that converts amount from USD
{																		// to the chosen currency (for withdrawing)
	double newAmount = 		0.0;
	double withdrawn_Amt =  0.0;
	
	if (currencyChoice == 1)													// converts from USD to euros
	{
		newAmount = cc->to_EUR();
		withdrawn_Amt = roundValue(newAmount);									// round value
		cout << "Amount: "<< withdrawn_Amt << " euros." << endl;				// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 2)												// converts from USD to pounds
	{
		newAmount = cc->to_GBP();			
		withdrawn_Amt = roundValue(newAmount);									// round value
		cout << "Amount: " << withdrawn_Amt << " pounds." << endl;				// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 3)												// converts from USD to rupees
	{	
		newAmount = cc->to_INR();			
		withdrawn_Amt = roundValue(newAmount);									// round value
		cout << "Amount: " << withdrawn_Amt << " rupees." << endl;				// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 4)										// converts from USD to Australian dollars
	{
		newAmount = cc->to_AUD();
		withdrawn_Amt = roundValue(newAmount);											// round value
		cout << "Amount: " << withdrawn_Amt << " Australian dollars." << endl;			// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 5)										// converts from USD to Canadian dollars
	{
		newAmount = cc->to_CAD();
		withdrawn_Amt = roundValue(newAmount);										// round value
		cout << "Amount: " << withdrawn_Amt << " Canadian dollars." << endl;		// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 6)										// converts from USD to Singapore dollars
	{
		newAmount = cc->to_SGD();											
		withdrawn_Amt = roundValue(newAmount);											// round value
		cout << "Amount: " << withdrawn_Amt << " Singapore dollars." << endl;			// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 7)											// converts from USD to reals
	{
		newAmount = cc->to_BRL();						
		withdrawn_Amt = roundValue(newAmount);										// round value
		cout << "Amount: " << withdrawn_Amt << " Brazilian reals." << endl;			// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 8)											// converts from USD to pesos
	{
		newAmount = cc->to_MXN();
		withdrawn_Amt = roundValue(newAmount);										// round value
		cout << "Amount: " << withdrawn_Amt << " Mexican pesos." << endl;			// print value
		return withdrawn_Amt;
	}

	else if (currencyChoice == 9)											// converts from USD to rands
	{
		newAmount = cc->to_ZAR();
		withdrawn_Amt = roundValue(newAmount);											// round value
		cout << "Amount: " << withdrawn_Amt << " South African Rands." << endl;			// print value
		return withdrawn_Amt;
	}

	else
	{
		newAmount = cc->to_JPY();											// converts from USD to yen
		withdrawn_Amt = roundValue(newAmount);										// round value
		cout << "Amount: " << withdrawn_Amt << " Japanese yen." << endl;			// print value
		return withdrawn_Amt;
	}
}

double convert_From(unsigned int currencyChoice, currencyConverter* cc)	// function that converts amount from 
{																		// chosen currency to USD (for depositing)
	double current_Amt = 	cc->getAmount();								
	double newAmount = 		0.0;
	double deposited_Amt =  0.0;
	
	if (currencyChoice == 1)
	{
		cout << "Amount: " << current_Amt << " euros" << endl;		// print amount to be transferred
		newAmount = cc->from_EUR();									// converts from euros to USD
	}

	else if (currencyChoice == 2)
	{
		cout << "Amount: " << current_Amt << " pounds" << endl;		// print amount to be transferred
		newAmount = cc->from_GBP();									// converts from pounds to USD
	}

	else if (currencyChoice == 3)
	{
		cout << "Amount: " << current_Amt << " rupees" << endl;		// print amount to be transferred
		newAmount = cc->from_INR();									// converts from rupees to USD
	}

	else if (currencyChoice == 4)
	{
		cout << "Amount: " << current_Amt << " Australian dollars" << endl;		// print amount to be transferred
		newAmount = cc->from_AUD();												// converts from Australian dollars to USD
	}

	else if (currencyChoice == 5)
	{
		cout << "Amount: " << current_Amt << " Canadian dollars" << endl;		// print amount to be transferred
		newAmount = cc->from_CAD();												// converts from Canadian dollars to USD
	}

	else if (currencyChoice == 6)
	{
		cout << "Amount: " << current_Amt << " Singapore dollars" << endl;		// print amount to be transferred
		newAmount = cc->from_SGD();												// converts from Singapore dollars to USD
	}

	else if (currencyChoice == 7)
	{
		cout << "Amount: " << current_Amt << " reals" << endl;		// print amount to be transferred
		newAmount = cc->from_BRL();									// converts from reals to USD
	}

	else if (currencyChoice == 8)
	{cout << "Amount: " << current_Amt << " pesos" << endl;			// print amount to be transferred
		newAmount = cc->from_MXN();									// converts from pesos to USD
	}

	else if (currencyChoice == 9)
	{
		cout << "Amount: " << current_Amt << " rands" << endl;		// print amount to be transferred
		newAmount = cc->from_ZAR();									// converts from rands to USD
	}

	else 
	{
		cout << "Amount: " << current_Amt << " yen" << endl;		// print amount to be transferred
		newAmount = cc->from_JPY();									// converts from yen to USD
	}

	deposited_Amt = roundValue(newAmount);							// round value
	return deposited_Amt;
}

void withdraw(Account* a)			// function that combines all other functions to physically withdraw
{								//  the amount given by the user and (possibly) show amount in another currency
	string input =  "";
	string choice = "";
	double amt = 	0.0;												
	
	while (true)
	{
		cout << "\nEnter amount to withdraw (in USD): ";			// get withdraw amount
		getline(cin, input);
		stringstream ss2(input);

		if (ss2 >> amt)													// checks that input is a double
		{
			if ((amt >= 0) && (fmod((amt * 1000.0), 10.0) == 0))		// checks that input is positive (or 0) and up to 2 decimal places
			{
				break;
			}
		}

		cout << "You must enter a positive amount with up to 2 decimal places." << endl;	// prints if input is bad
	}							

	while (true)
	{
		cout << "\nChange currency from US Dollars? Y/N" << endl;		// ask user whether to change currency or not 
		getline(cin, choice);													// get choice

		if ((choice == "Y") || (choice == "y") || (choice == "N") || (choice == "n"))		// checks if input is "y", "Y", "n" or "N"
		{
			break;
		}

		cout << "You must enter 'Y' or 'N'." << endl;			// prints otherwise
	}

	if ((choice == "Y") || (choice == "y"))							// y = yes, change currency
	{
		unsigned int currencyChoice = getCurrency();					// get currency choice from user													
		currencyConverter* cc = new currencyConverter(amt);			// create the currency converter as an object
		convert_To(currencyChoice, cc);							// convert amount to desired currency and print it
		a->withdraw(amt);											// withdraw amount from account (in USD)
		delete cc;													// delete the converter and free memory space
	}																	

	else															// n = no, don't change currency
	{
		a->withdraw(amt);											// withdraw amount from account (in USD)
	}
}

void deposit(Account* a)		// function that combines all other functions to physically deposit
{									// amount from user into account and convert to USD if necessary
	string input = 	"";
	string choice = "";
	double amt = 	0.0;

	while (true)
	{
		cout << "\nAre you depositing in another currency (not USD)? Y/N" << endl;	// ask user if using different currency
		getline(cin, choice);																// get choice

		if ((choice == "Y") || (choice == "y") || (choice == "N") || (choice == "n"))	// checks for correct input
		{
			break;
		}

		cout << "You must enter 'Y' or 'N'." << endl;					// prints if input is bad
	}

	if ((choice == "Y") || (choice == "y"))								// y = yes, different currency
	{
		unsigned int currencyChoice = getCurrency();					// get currency from user
		
		while (true)
		{
			cout << "\nEnter amount to deposit: ";					// get deposit amount from user in that currency
			getline(cin, input);
			stringstream ss3(input);

			if (ss3 >> amt)												// checks that input is a double
			{
				if ((amt >= 0) && (fmod((amt * 1000.0), 10.0) == 0))		// checks that input is positive or 0 and up to 2 decimal places
				{
					break;
				}
			}

			cout << "You must enter a positive amount with up to 2 decimal places." << endl;		// prints if input is bad
		}																													

		currencyConverter* cc = new currencyConverter(amt);			// create the currency converter as an object
		double deposited_Amt = convert_From(currencyChoice, cc);	// convert amount to USD
		a->deposit(deposited_Amt);									// deposit amount (in USD) into account
		delete cc;													// delete the converter and free memory space
	}																	

	else														// n = no, deposit in USD
	{
		while (true)
		{
			cout << "\nEnter amount to deposit: ";					// get deposit amount from user in that currency
			getline(cin, input);
			stringstream ss4(input);

			if (ss4 >> amt)													// checks that input is a double
			{
				if ((amt >= 0) && (fmod((amt * 1000.0), 10.0) == 0))		// checks that input is positive or 0 and up to 2 decimal places
				{
					break;
				}
			}

			cout << "You must enter a positive amount with up to 2 decimal places." << endl;	// prints if input is bad
		}

		a->deposit(amt);								// deposit amount (in USD) into account
	}
}

int main()				// just for testing purposes
{
	// ***** choose account (made an account for testing purposes) *****
	string  name = 	"Checking";
	double  bal = 	331.95;
	int 	type = 	1;

	Account* a = new Account(name, bal, type);

	//withdrawing
	withdraw(a);

	//depositing
	deposit(a);
	
	// ***** return to main menu *****

	return 0;
}

