/********************************************************************
	
	hash

	Personal implementation of the SHA-1* (Secure Hashing Algorithm).
	Takes a string as input, returns a hashed string.

	* Note - This will NOT return the same hash as the actual
	SHA-1. It is a personal version that has not yet been cracked
	by malicious programmers. Algolithm is 100% secure, to date.

*********************************************************************
*/

#include <iostream>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;

/************************************************************

	leftRotate()

	Left Rotate X: Function that takes a string and rotates
	the string to the left by a given amount. For example,
	"string" rotate 4 would be "ngstri".

*************************************************************
*/

string leftRotate(string word, int length, int rotationAmount) 
{
	char* firstChars = new char[rotationAmount];

	for (int i = 0; i < rotationAmount; i++)
	{
		firstChars[i] = word[i];
	}

	for (int i = 0; i < rotationAmount; i++)
	{
		for (int j = 0; j < length; j++)
		{
			word[j] = word[j+1];
		}
	}

	for (int i = 0; i < rotationAmount; i++)
	{
		word[length - rotationAmount + i] = firstChars[i];
	}

	delete firstChars;

	return word;
}

/************************************************************

	convertToNot()

	Converts binary number to its "not" value. (binary number
	B would become B!). For example, "11011101" would become
	"00100010".

*************************************************************
*/

string convertToNot(string word, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (word[i] == '0')
		{
			word[i] = '1';
		}
		else
		{
			word[i] = '0';
		}
	}

	return word;
}

/************************************************************

	binarySum()

	Sums two binary numbers in string form in the fashion of
	standard binary addition. For example "101" + "101" =
	"1010". Accounts for strings of varying length by
	appending 0's in front of a smaller string.

*************************************************************
*/

string binarySum(string word0, string word1)
{
	string temp = "";
	string result = "";
	bool carry = false;
	int length = 0;

	while (word0.length() != word1.length())				// Append 0's to the beginning of a string until the strings are of equal length
	{
		if (word0.length() > word1.length())
		{
			word1 = "0" + word1;	
		}

		if (word0.length() < word1.length())
		{
			word0 = "0" + word0;
		}
	}
	
	length = word0.length();								// word0 chosen arbitrarily, word0 and word1 are the same length now

	for (int i = length - 1; i >= 0; i--)
	{
		if (word0[i] == word1[i] && word0[i] == '0')		// 0 and 0
		{
			if (carry)
			{
				temp = "1";
				carry = false;
			}
			else
			{
				temp = "0";
			}
		}
		else if (word0[i] == word1[i] && word0[i] == '1')	// 1 and 1
		{
			if (carry)
			{
				temp = "1";
				carry = true;
			}
			else
			{
				temp = "0";
				carry = true;
			}
		}
		else												// 1 and 0
		{
			if (carry)
			{
				temp = "0";
				carry = true;
			}
			else
			{
				temp = "1";
				carry = false;
			}
		}

		result = temp + result;
	}

	if (carry)												// Adds a '1' to the beginning of the string if a '1' is still being carried after the loop
	{
		result = "1" + result;
	}

	return result;
}

/************************************************************

	Primary algorithm is below. Steps are labeled throughout.

*************************************************************
*/

string hash(string input)
{
	//********* Initialize Variables And Recieve Input **************

	string h0, h1, h2, h3, h4, combinedBins, messagePadString;

	h0 = "01100111010001010010001100000001";
	h1 = "11101111110011011010101110001001";
	h2 = "10011000101110101101110011111110";
	h3 = "00010000001100100101010001110110";
	h4 = "11000011110100101110000111110000";

	int length = input.length();

	// ******************* Message Padding ***************************

	char* inputCharacters = new char[length];				// break input into characters

	for (int i = 0; i < length; i++)
	{
		inputCharacters[i] = input[i];
	}

	int* asciiValues = new int[length];						// convert chars to ASCII

	for (int i = 0; i < length; i++)
	{
		asciiValues[i] = int(inputCharacters[i]);
	}

	string* binaryValues = new string[length];				// convert numbers to 8-bit binary and combine them into one string
	combinedBins = "";

	for (int i = 0; i < length; i++)
	{
		bitset<8> binValue(asciiValues[i]);
		binaryValues[i] = binValue.to_string();
		combinedBins += binaryValues[i];
	}

	int originalMessageLEngth = combinedBins.length();

	combinedBins += "1";									// append 1 to the string

	int combinedBinsLength = originalMessageLEngth + 1;

	while (combinedBinsLength % 512 != 448)					// convert string to 512 mod 448 in length by appending 0's to the end
	{
		combinedBins += "0";
		combinedBinsLength++;
	}

	bitset<64> messagePadBin(originalMessageLEngth);		// convert the int value of the original binary mesage length to a 64-bit binary number 
	messagePadString = messagePadBin.to_string();			// 	and pad the message again with it

	combinedBins += messagePadString;

	// ************* Message Chunking ***********************

	int numberOfChunks = combinedBins.length() / 512;

	string* primaryChunks = new string[numberOfChunks];
	string* secondaryChunks = new string[numberOfChunks*80];

	for (int i = 0; i < numberOfChunks; i++)
	{
		primaryChunks[i] = combinedBins.substr(i*512, 512);				// chunk message into 512-bit binary numbers

		for (int j = 0; j < 16; j++)
		{
			secondaryChunks[j] = primaryChunks[i].substr(j*32, 32); 	// chunk those chunks into 16, 32-bit 'words'
		} 
	}

	// ************* Chunk Extension ***********************

	string temp[5];														// temp[0-3] will be placeholders for the words of interest
																		//	temp[4] will store the result
	int wordLength = secondaryChunks[0].length();

	for (int i = 16; i <= 79; i++)										// XOR the 'words' and store them as new words to extend the 16 to 80
	{
		temp[0] = secondaryChunks[i-3];
		temp[1] = secondaryChunks[i-8];
		temp[2] = secondaryChunks[i-14];
		temp[3] = secondaryChunks[i-16];
		temp[4] = temp[0];

		for (int j = 1; j < 4; j++)
		{
			for (int k = 0; k < wordLength; k++)
			{
				if (temp[4][k] == temp[j][k])
				{
					temp[4][k] = '0';
				}
				else
				{
					temp[4][k] = '1';
				}
			}
		}

		secondaryChunks[i] = leftRotate(temp[4], wordLength, 1);			// Perform a left rotate 1 on the XORed word and store as the new word
	}

	// ************** The Main Loop ***********************

	string A, B, C, D, E, F, K, Bnot, TEMP;
	A = h0;
	B = h1;
	C = h2;
	D = h3;
	E = h4;
	F = A;		// This is just to initialize F and K, which are temporary
	K = A;		// variables. This specific value serves no purpose.

	for (int i = 0; i < 80; i++)
	{
		if (i <= 19)														// Function 1: (B and C) or (B! and D)
		{
			for (int j = 0; j < wordLength; j++)
			{
				if (B[j] == C[j] && B[j] == '1')
				{
					F[j] = '1';
				}
				else
				{
					F[j] = '0';
				}
			}

			Bnot = convertToNot(B, wordLength);

			for (int j = 0; j < wordLength; j++)
			{
				if (Bnot[j] == D[j] && D[j] == '1')
				{
					K[j] = '1';
				}
				else
				{
					K[j] = '0';
				}
			}

			for (int j = 0; j < wordLength; j++)
			{
				if (F[j] == '0' && K[j] == '0')
				{
					F[j] = '0';
				}
				else
				{
					F[j] = '1';
				}
			}

			K = "01011010100000100111100110011001";
		}

		else if (i <= 39)														// Function 2: (B XOR C) XOR D
		{
			for (int i = 0; i < wordLength; i++)
			{
				if (B[i] == C[i])
				{
					F[i] = '0';
				}
				else
				{
					F[i] = '1';
				}
			}

			for (int i = 0; i < wordLength; i++)
			{
				if (F[i] == D[i])
				{
					F[i] = '0';
				}
				else
				{
					F[i] = '1';
				}
			}

			K = "01101110110110011110101110100001";
		}
		else if (i <= 59)														// Function 3: ((B AND C) OR (B AND D)) OR (C AND D)
		{
			for (int i = 0; i < wordLength; i++) //b and c
			{
				if (B[i] == C[i])
				{
					F[i] = '1';
				}
				else
				{
					F[i] = '0';
				}
			}
			for (int i = 0; i < wordLength; i++) // b and d
			{
				if (B[i] == D[i])
				{
					K[i] = '0';
				}
				else
				{
					K[i] = '1';
				}
			}
			for (int i = 0; i < wordLength; i++) // f or k
			{
				if (F[i] == '0' && K[i] == '0')
				{
					F[i] = '0';
				}
				else
				{
					F[i] = '1';
				}
			}
			for (int i = 0; i < wordLength; i++) // c and d
			{
				if (C[i] == D[i])
				{
					K[i] = '0';
				}
				else
				{
					K[i] = '1';
				}
			}
			for (int i = 0; i < wordLength; i++) // f or k
			{
				if (F[i] == '0' && K[i] == '0')
				{
					F[i] = '0';
				}
				else
				{
					F[i] = '1';
				}
			}

			K = "10001111000110111011110011011100";
		}
		else														// Function 4: (B XOR C) XOR D --> **Same as F2 with new K value**
		{
			for (int i = 0; i < wordLength; i++)
			{
				if (B[i] == C[i])
				{
					F[i] = '0';
				}
				else
				{
					F[i] = '1';
				}
			}

			for (int i = 0; i < wordLength; i++)
			{
				if (F[i] == D[i])
				{
					F[i] = '0';
				}
				else
				{
					F[i] = '1';
				}
			}

			K = "11001010011000101100000111010110";
		}

		TEMP = leftRotate(A, wordLength, 5);						// Perform a Left Rotate 5
		TEMP = binarySum(TEMP, F);									// then add A_lrot5 + F + E + K + word[i]
		TEMP = binarySum(TEMP, E);
		TEMP = binarySum(TEMP, K);
		TEMP = binarySum(TEMP, secondaryChunks[i]);
		TEMP = TEMP.substr(TEMP.length() - 32, 32);					// Truncate TEMP back to 32 bits
																	// Change up the values before repeating the loop
		E = D;
		D = C;
		C = leftRotate(B, wordLength, 30);
		B = A;
		A = TEMP;
	}

	// ************** Resetting of Initial Variables ***********************

	h0 = binarySum(h0, A);
	h1 = binarySum(h1, B);
	h2 = binarySum(h2, C);
	h3 = binarySum(h3, D);
	h4 = binarySum(h4, E);

	bitset<32> set_h0(h0);											// truncate all strings back to 32-bit binary numbers
	bitset<32> set_h1(h1);
	bitset<32> set_h2(h2);
	bitset<32> set_h3(h3);
	bitset<32> set_h4(h4);

	stringstream h0_hex, h1_hex, h2_hex, h3_hex, h4_hex;			// convert to hex and combine to one string

	h0_hex << hex << set_h0.to_ulong();
	h1_hex << hex << set_h1.to_ulong();
	h2_hex << hex << set_h2.to_ulong();
	h3_hex << hex << set_h3.to_ulong();
	h4_hex << hex << set_h4.to_ulong();

	string finalHash = h0_hex.str() + h1_hex.str() + h2_hex.str() + h3_hex.str() + h4_hex.str();

    return finalHash;
}
