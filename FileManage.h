#ifndef _FILE_MANAGE_H
#define _FILE_MANAGE_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class FileManage {
public:
	//write user's information to text file
	void writeFile(string user, string pw, string name, string salt, string accName1, string bal1, string accName2, string bal2, string accName3, string bal3) {
		ofstream myFile;
		myFile.open("accInfo.txt", ios::app);

		//check to see file opened successfully
		if (myFile.fail()) {
			throw "Could not open file";
		}

		string placeholder = "!!!";
		
		//write to file
		myFile << user << "\n";
		myFile << pw << "\n";
		myFile << name << "\n";
		myFile << salt << "\n";
		myFile << accName1 << "\n";
		myFile << bal1 << "\n";
		myFile << accName2 << "\n";
		myFile << bal2 << "\n";
		myFile << accName3 << "\n";
		myFile << bal3 << "\n";
		myFile << placeholder << "\n";

		myFile.close();
	}

	//read in information for given username
	void readFile(string username, string& password, string& realName, string& saltPW, string& accName1, string& bal1, string& accName2, string& bal2, string& accName3, string& bal3) {
		ifstream myFile;
		string existingUser;
		myFile.open("accInfo.txt");

		//check to see file opened successfully
		if (myFile.fail()) {
			throw "Could not open file";
		}

		//read in values after username is found
		while (myFile.good()) {
			myFile >> existingUser;
			if (existingUser == username) {
				myFile>>password;
				myFile>>realName;
				myFile>>saltPW;
				myFile>>accName1;
				myFile>>bal1;
				myFile>>accName2;
				myFile>>bal2;
				myFile>>accName3;
				myFile>>bal3;
			}			
		}

		myFile.close();
	}

	//find out if a username exists
	bool findUsername(string &username) {
		ifstream myFile;
		string existingUser;
		myFile.open("accInfo.txt");

		//check to see file opened correctly
		if (myFile.fail()) {
			throw "Could not open file";
		}

		while (myFile.good()) {
			myFile >> existingUser;
			//cout<<existingUser<<"\n";
			if (existingUser == username) {
				return true;
			}			
		}

		myFile.close();
	}

	//check whether a certain user has an existing account with the name given
	bool findAccount(string user, string account) {
		ifstream myFile;
		myFile.open("accInfo.txt");

		//check to see file opened correctly
		if (myFile.fail()) {
			throw "Could not open file";
		}

		string existingUser;
		string buffer;

		while (myFile.good()) {
			myFile >> existingUser;
			if (existingUser == user) {
				while (buffer != "!!!"){
					myFile >> buffer;
					if (buffer == account) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
	}

	//find out how many free accounts someone has
	int freeAccounts(string account) {
		ifstream myFile;
		myFile.open("accInfo.txt");

		//check to see file opened correctly
		if (myFile.fail()) {
			throw "Could not open file";
		}

		int count = 0;
		int freeAccounts = 0;
		string existingUser;
		string buffer;

		//read in from myFile
		while (myFile.good()) {
			myFile >> existingUser;
			if (existingUser == account) {
				while (buffer != "!!!"){
					myFile >> buffer;
					//increase count for every "free account" found
					if (buffer == "*") {
						count++;
					}
				}
			}
		}
		
		freeAccounts = count/2;
		cout << "You have " << freeAccounts << " account(s) free." << endl;

		return freeAccounts;
		myFile.close();
	}

	//change a user's account name
	void changeAccountName(string username, string accName, string newName) {
		FileManage manager;
		bool accountFound = manager.findAccount(username, accName);
		
		if (accountFound == true) {
			manager.writeToTemp(username, accName, newName);
		}
		manager.writeToMain();
	}

	//change a user's account balance
	void changeAccountBalance(string username, string accBalance, string newBalance) {
		FileManage manager;
		bool accountFound = manager.findAccount(username, accBalance);
		
		if (accountFound == true) {
			manager.writeToTemp(username, accBalance, newBalance);
		}
		manager.writeToMain();
	}

	//read in from accInfo and export to temp file
	void writeToTemp(string username, string existing, string updated) {
		//to read in file
		FileManage manager;
		string line;
		int i = 1;
		int count = manager.countOccurrence(username, existing);
		int wordPos = (count + 1);
		
		//open file to read in from
		ifstream myFile;
		myFile.open("accInfo.txt");

		//check to see file opened successfully
		if (myFile.fail()) {
			throw "Could not open file";
		}

		//to write to temp file
		ofstream tempFile;
		tempFile.open("temp.txt");

		//check to see file opened successfully
		if (myFile.fail()) {
			throw "Could not open file";
		}

		//read in from myFile
		while (getline(myFile, line)) {
			if (line != existing) {
				tempFile << line << "\n";
			}
			//if word is found replace with updated word
			else if (line == existing) {
				if (i == wordPos) {
					tempFile << updated << "\n";
					existing = "@#$$^&$^&";
				}
				else if (i != wordPos) {
					tempFile << line << "\n";
					i++;
				}
			}
		}

		myFile.close();
		tempFile.close();	
	}

	//read in from temp and export to accInfo
	void writeToMain() {
		//to read in file
		ifstream tempFile;
		tempFile.open("temp.txt");
		ofstream myFile;
		//to write to main file
		myFile.open("accInfo.txt");
		string line;

		//read in from tempFile
		//read out to myFile
		while (getline(tempFile, line)) {
			myFile << line << "\n";
		}

		myFile.close();
		tempFile.close();
	}

	//count how many times an account name appears before given username
	int countOccurrence(string username, string given) {
		ifstream myFile;
		myFile.open("accInfo.txt");
		string buffer;
		string existingUser;
		int count = 0;
		
		//check to see file opened correctly
		if (myFile.fail()) {
			throw "Could not open file";
		}

		//increase count if word is found before username
		while(buffer != username) {
			myFile >> buffer;
			if (buffer == given) {
				count++;
			}
		}
		return count;
		myFile.close();
	}

	//count total time an account name appears
	int countTotalOccurrence(string existing) {
		ifstream myFile;
		myFile.open("accInfo.txt");
		string buffer;
		int count = 0;
				
		//check to see file opened correctly
		if (myFile.fail()) {
			throw "Could not open file";
		}

		//increase count if word is found
		while (getline(myFile, buffer)) {
			if (buffer == existing) {
				count++;
			}
		}

		return count;
		myFile.close();
	}

	//check if file is empty
	bool emptyFileCheck() {
		int length;
		ifstream myFile;
		myFile.open("accInfo.txt");

		//check if file opened successfully
		if (myFile.fail()) {
			throw "Could not open file";
		}

		//find size of file
		myFile.seekg(0, ios::end);
		length = myFile.tellg();
		myFile.close();

		if (length == 0 ){
			return true;
		}
		else {
			return false;
		}
	}

	//erase file
	void clearFile() {
		ofstream myFile;
		myFile.open("accInfo.txt", ofstream::out | ofstream::trunc);

		//check if file opened successfully 
		if (myFile.fail()) {
			throw "Could not open file";
		}

		myFile.close();
	}
};

#endif
