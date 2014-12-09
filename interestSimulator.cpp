#include "InterestSimulator.h"
#include "Account.h"
#include <string>
#include <iostream>

using namespace std;

interestSimulator* createSimulator(Account* a)			// function that gets inputs from user to create 
{								// an instance of the simulator object
	double 		 currentBalance = a->getAccountBalance();		// get current balance for that account 
	double 		 interestRate =	  0.0;
	double 		 numYears = 	  0.0;
	
	interestSimulator* i = new interestSimulator(currentBalance, interestRate, numYears); 	// create simulator object

	cout << "\nEnter an interest rate (in decimal form): ";			// get interest rate from user
	cin >> interestRate;
	
	while (cin.fail() || interestRate < 0)							// catch bad input
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\nInterest rate must be a positive decimal value." << endl;
		cout << "Enter an interest rate: ";
		cin >> interestRate;
	}

	i->set_interestRate(interestRate);					// set interest rate of simulator object to interest rate from user

	cout << "\nEnter a time interval (in years): ";					// get time span from user
	cin >> numYears;

	while (cin.fail())												// catch bad input
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\nThe time interval must be a positive number." << endl;
		cout << "Enter a time interval: ";
		cin >> numYears;
	}

	i->set_timeSpan(numYears);							// set time span of simulator object to time span from user

	return i;
}

int runSimulator(interestSimulator* i)				// function that calls other functions on the simulator that
{													// calculate the predicted new balance, depending on interest type
	unsigned int choice = 	 	 0;
	unsigned int n =			 0;
	string 		 timeOfYear = 	 "";
	double 		 investAmt =  	 0.0;
	double 		 futureBalance = 0;

	while (true)
	{
		cout << "\nChoose a type of interest:\n" << 			// lists options / types of interest
		"	(1) periodic compounding\n" <<
		"	(2) continuous compounding\n" << 
		"	(3) annual compounding with investment\n" << 
		"OR	(4) return to main menu\n" << endl;					// ends program for now
		cout << "Choice: ";
		cin >> choice;											// get interest type from user

		while (cin.fail() || choice > 4)						// catch bad input
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nPlease enter a number between 1 and 4 to choose an option: ";
			cin >> choice;
		}

		switch (choice)
		{
			case 1:		
				cout << "\nEnter the number of compounds per year: ";			// get compound rate from user
				cin >> n;														// for periodic compounding
				while (cin.fail())					
				{																// catch bad input
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nThe number of compounds per year must be a positive number." << endl;
					cout << "Enter the number of compounds per year: ";
					cin >> n;
				}

				futureBalance = i->periodic_cmpd(n);				// calculate future balance with periodic 
				i->printFutureBalance(futureBalance);				// compounding, then print future balance
				break;

			case 2: 	
				futureBalance = i->continuous_cmpd();				// calculate future balance with continuous 
				i->printFutureBalance(futureBalance);				// compounding, then print future balance
				break;

			case 3: 	
				cout << "\nEnter an investment amount: ";			// get investment amount from user
				cin >> investAmt;									// for annual compounding w/ investment
				while (cin.fail() || investAmt < 0)
				{													// catch bad input
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nThe investment amount must be a positive decimal value." << endl;
					cout << "\nEnter an investment amount: ";
					cin >> investAmt;
				}

				cout << "\nAdd investment at beginning or end of year? (enter 'beginning' or 'end'): ";	 // get time of 
				cin >> timeOfYear;																		 // year from user
				while (cin.fail() || ((timeOfYear != "beginning") && (timeOfYear != "end")))
				{																						// catch bad input
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nYou must enter the word 'beginning' or the word 'end'." << endl;
					cout << "\nEnter the time of year to deposit investment: ";
					cin >> timeOfYear;
				}

				futureBalance = i->investment_cmpd(investAmt, timeOfYear);		// calculate future balance with annual 
				i->printFutureBalance(futureBalance);							// compounding + investment, then print it
				break;

			default: 	
				return 0;
		}
	}
}
