#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class interestSimulator
{
	double 		 numYears;
	double  	 currentBalance;
	double 		 interestRate;
	double  	 futureBalance;
	double 		 cmpd_rate;

	public:
		interestSimulator(double currentBalance, double interestRate, double numYears)	// constructor
		{
			this->currentBalance = currentBalance;
			this->interestRate = interestRate;
			this->numYears = numYears;

			cout << "\nYou have opened the Interest Simulator. This program will estimate your future balance after compounding interest." << endl;
		}

		int periodic_cmpd(double n)													// take in number of compounds per year
		{																			// to calculate compound rate, then
			cmpd_rate = interestRate / n;			
			futureBalance = currentBalance * (pow((1.0 + cmpd_rate), (numYears * n))); 	// calculate future balance with
			return futureBalance;														// periodic compounding
		}

		int continuous_cmpd()
		{
			futureBalance = currentBalance * exp(numYears * interestRate); 		// calculate future balance with
			return futureBalance;												// continuous compounding
		}

		int investment_cmpd(double investAmt, string timeOfYear)			// take in investment amount and "time of year"
		{
			if (timeOfYear == "beginning")				// if investment amount is added at the beginning of the year,
			{
				futureBalance = (currentBalance * pow((1 + interestRate), numYears)) + (investAmt * ((pow((1 + interestRate), numYears + 1) - (1 + interestRate)) / interestRate)); 
			}

			else if (timeOfYear == "end")				// if investment amount is added at the end of the year,
			{
				futureBalance = (currentBalance * pow((1 + interestRate), numYears)) + (investAmt * ((pow((1 + interestRate), numYears) - 1) / interestRate));  
			}

			cout << "\nAssuming that the initial balance included the interest growth from the previous year and did not yet include the new investment amount, " << endl;
			return futureBalance;				// return calculated future balance with annual compounding + investment
		}

		void set_interestRate(double interestRate)
		{
			this->interestRate = interestRate;					// sets interest rate inside of simulator object
		}

		void set_timeSpan(unsigned int numYears)
		{
			this->numYears = numYears;							// sets time span inside of simulator object
		}

		void printFutureBalance(double futureBalance)			// function that rounds future balance to 
		{														// 2 decimals and then prints it
			futureBalance = this->futureBalance;

			if (fmod((futureBalance * 1000.0), 10.0) > 5.0)
			{
				futureBalance = ceil(futureBalance * 100);		// round up
				futureBalance = futureBalance / 100;
			}


			else if (fmod((futureBalance * 1000.0), 10.0) <= 5.0)
			{
				futureBalance = floor(futureBalance * 100);		// round down
				futureBalance = futureBalance / 100;
			}

			cout << "\nYour future balance is: " << futureBalance << endl;		// print
		}
};
