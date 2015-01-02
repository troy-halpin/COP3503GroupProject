#include "InterestSimulator.h"
#include "Account.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

interestSimulator* createSimulator(Account* a)			// function that gets inputs from user to create 
{															// an instance of the simulator object
	string		 input =		  "";
	double 		 currentBalance = a->getAccountBalance();		// get current balance for that account 
	double 		 interestRate =	  0.0;
	unsigned int numYears = 	  0;
	
	interestSimulator* i = new interestSimulator(currentBalance, interestRate, numYears); 	// create simulator object

	while (true)
	{
		cout << "\nEnter an interest rate (in decimal form): ";			// get interest rate from user
		getline(cin, input);
		stringstream ss1(input);
		
		if (ss1 >> interestRate)										// checks that input is a double
		{
			if (interestRate >= 0)										// checks that input is positive
			{
				break;
			}
		}

		cout << "Interest rate must be a positive decimal value." << endl;		// prints if input is bad
	}

	i->set_interestRate(interestRate);					// set interest rate of simulator object to interest rate from user

	while (true)
	{
		cout << "\nEnter a time interval (in years): ";					// get time span from user
		getline(cin, input);
		stringstream ss2(input);

		if (ss2 >> numYears)											// checks that input is a positive number (or 0)
		{
			break;
		}

		cout << "The time interval must be a positive integer." << endl;	// prints if input is bad
	}

	i->set_timeSpan(numYears);							// set time span of simulator object to time span from user

	return i;
}

int runSimulator(interestSimulator* i)				// function that calls other functions on the simulator that
{													// calculate the predicted new balance, depending on interest type
	string		 input =	     "";
	unsigned int choice = 	 	 0;
	unsigned int n =			 0;
	string 		 timeOfYear = 	 "";
	double 		 investAmt =  	 0.0;
	double 		 futureBalance = 0;

	while (true)
	{
		while (true)
		{
			cout << "\nChoose a type of interest:\n" << 			// lists options / types of interest
			"	(1) periodic compounding\n" <<
			"	(2) continuous compounding\n" << 
			"	(3) annual compounding with investment\n" << 
			"OR	(4) return to main menu\n" << endl;					
			cout << "Choice: ";
			getline(cin, input);									// get interest type from user
			stringstream ss3(input);

			if (ss3 >> choice)										// checks that input is a positive number
			{
				if ((choice > 0) && (choice < 5))					// checks that choice is between 1 and 5
				{
					break;
				}
			}

			cout << "You must enter a number between 1 and 4 to choose an option." << endl;		// prints if input is bad
		}

		switch (choice)
		{
			case 1:		while (true)
						{
							cout << "\nEnter a positive (whole) number of compounds per year: ";	// get compound rate from user
							getline(cin, input);
							stringstream ss4(input);

							if (ss4 >> n)							// checks that input is a positive number (or 0)
							{
								break;
							}

							cout << "The number of compounds per year must be a positive integer." << endl;		// prints if input is bad
						}

						futureBalance = i->periodic_cmpd(n);				// calculate future balance with periodic 
						i->printFutureBalance(futureBalance);				// compounding, then print future balance
						break;

			case 2: 	futureBalance = i->continuous_cmpd();				// calculate future balance with continuous 
						i->printFutureBalance(futureBalance);				// compounding, then print future balance
						break;

			case 3: 	while (true)
						{
							cout << "\nEnter an investment amount: ";			// get investment amount from user
							getline(cin, input);
							stringstream ss5(input);

							if (ss5 >> investAmt)								// checks that input is a double
							{
								if ((investAmt >= 0) && (fmod((investAmt * 1000.0), 10.0) == 0))	// checks that investAmt is positive (or 0) and 
								{																	// does not exceed 2 decimal places
									break;
								}
							}

							cout << "The investment amount must be a positive decimal value." << endl;		// prints if input is bad
						}

						while (true)
						{
							cout << "\nAdd investment at beginning or end of year? (enter 'beginning' or 'end'): ";	 // get time of year from user
							getline(cin, timeOfYear);
						
							if ((timeOfYear == "beginning") || (timeOfYear == "end"))	// checks that input is 'beginning' or 'end'
							{
								break;
							}

							cout << "You must enter the word 'beginning' or the word 'end'." << endl;	// prints otherwise
						}

						futureBalance = i->investment_cmpd(investAmt, timeOfYear);		// calculate future balance with annual 
						i->printFutureBalance(futureBalance);							// compounding + investment, then print it
						break;

			default: 	return 0;
		}
	}
}

int main()				// just for testing purposes
{
	// ***** choose account (made an account for testing purposes) *****
	string  name =  "Checking";
	double  bal = 	331.95;
	int 	type =  1;

	Account* a = new Account(name, bal, type);


	interestSimulator* i = createSimulator(a);		// create instance of simulator from user inputs and return it
	runSimulator(i);								// run simulator to calculate future balance from chosen interest type

	delete i;										// delete simulator to free memory

	// ***** return to main menu *****

	return 0;
}
