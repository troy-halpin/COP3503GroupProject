#include <iostream>
#include <cmath>

using namespace std;

class currencyConverter
{
	double amount;
	double newAmount; 

	public:
		currencyConverter(double amount)			// constructor
		{
			this->amount = amount;
		}

		double getAmount()						// returns the amount stored in the currency converter object
		{
			return amount;							
		}

		double to_EUR()								// converts amount from USD to euros
		{
			newAmount = amount * 0.81214;
			return newAmount;
		}

		double to_GBP()								// converts amount from USD to pounds
		{
			newAmount = amount * 0.63742;
			return newAmount;
		}

		double to_INR()								// converts amount from USD to rupees
		{
			newAmount = amount * 61.8981;
			return newAmount;
		}

		double to_AUD()								// converts amount from USD to Australian dollars
		{
			newAmount = amount * 1.19221;
			return newAmount;
		}

		double to_CAD()								// converts amount from USD to Canadian dollars
		{
			newAmount = amount * 1.13657;
			return newAmount;
		}

		double to_SGD()								// converts amount from USD to Singapore dollars
		{
			newAmount = amount * 1.31414;
			return newAmount;
		}

		double to_BRL()								// converts amount from USD to reals
		{
			newAmount = amount * 2.55245;
			return newAmount;
		}

		double to_MXN()								// converts amount from USD to pesos
		{
			newAmount = amount * 14.1360;
			return newAmount;
		}

		double to_ZAR()								// converts amount from USD to rands
		{
			newAmount = amount * 11.2172;
			return newAmount;
		}

		double to_JPY()								// converts amount from USD to yen
		{
			newAmount = amount * 119.935;
			return newAmount;
		}

		double from_EUR()							// converts amount from euros to USD
		{
			newAmount = amount * 1.23131;
			return newAmount;
		}

		double from_GBP()							// converts amount from pounds to USD
		{
			newAmount = amount * 1.56882;
			return newAmount;
		}

		double from_INR()							// converts amount from rupees to USD
		{
			newAmount = amount * 0.01616;
			return newAmount;
		}

		double from_AUD()							// converts amount from Australian dollars to USD
		{
			newAmount = amount * 0.83878;
			return newAmount;
		}

		double from_CAD()							// converts amount from Canadian dollars to USD
		{
			newAmount = amount * 0.87984;
			return newAmount;
		}

		double from_SGD()							// converts amount from Singapore dollars to USD
		{
			newAmount = amount * 0.760962;
			return newAmount;
		}

		double from_BRL()							// converts amount from reals to USD
		{
			newAmount = amount * 0.391780;
			return newAmount;
		}

		double from_MXN()							// converts amount from pesos to USD
		{
			newAmount = amount * 0.0707414;
			return newAmount;
		}

		double from_ZAR()							// converts amount from rands to USD
		{
			newAmount = amount * 0.0891489;
			return newAmount;
		}

		double from_JPY()							// converts amount from yen to USD
		{
			newAmount = amount * 0.00833787;
			return newAmount;
		}
};
