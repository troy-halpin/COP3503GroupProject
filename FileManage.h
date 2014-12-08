#ifndef _FILE_MANAGE_H
#define _FILE_MANAGE_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class FileManage {
public:
	void writeFile(string user, string pw, string name, string salt, string accName1, string bal1, string accName2, string bal2, string accName3, string bal3) {
		ofstream myFile;
		myFile.open("accInfo.txt", ios::app);
		string username = user;
		string password = pw;
		string realName = name;
		string saltPW = salt;
		string accountName1 = accName1;
		string balance1 = bal1;
		string accountName2 = accName2;
		string balance2 = bal2;
		string accountName3 = accName3;
		string balance3 = bal3;
		string placeholder = "!!!";
		
		myFile << username << "\n";
		myFile << password << "\n";
		myFile << realName << "\n";
		myFile << saltPW << "\n";
		myFile << accountName1 << "\n";
		myFile << balance1 << "\n";
		myFile << accountName2 << "\n";
		myFile << balance2 << "\n";
		myFile << accountName3 << "\n";
		myFile << balance3 << "\n";
		myFile << placeholder << "\n";

		myFile.close();
	}

	void readFile(string username, string& password, string& realName, string& saltPW, string& accName1, string& bal1, string& accName2, string& bal2, string& accName3, string& bal3) {
		ifstream myFile;
		string buffer;
		string existingUser;
		myFile.open("accInfo.txt");

		//check to see file opened correctly
		if (myFile.fail()) {
			cerr << "Could not open file" << endl;
			exit(1);
		}

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
			cerr << "Could not open file" << endl;
			exit(1);
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

	bool findAccount(string user, string account) {
		ifstream myFile;
		myFile.open("accInfo.txt");

		//check to see file opened correctly
		if (myFile.fail()) {
			cerr << "Could not open file" << endl;
			exit(1);
		}

		int count = 0;
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
				}
			}
		}
	}

	int freeAccounts(string account) {
		ifstream myFile;
		myFile.open("accInfo.txt");

		//check to see file opened correctly
		if (myFile.fail()) {
			cerr << "Could not open file" << endl;
			exit(1);
		}

		int count = 0;
		string existingUser;
		string buffer;

		while (myFile.good()) {
			myFile >> existingUser;
			if (existingUser == account) {
				while (buffer != "!!!"){
					myFile >> buffer;
					if (buffer == "*") {
						count++;
					}
				}
			}
		}
		
		cout << "You have " << count/2 << " account(s) free." << endl;

		myFile.close();
	}

	void changeAccountName(string username, string accName, string newName) {
		FileManage manager;
		bool accountFound = manager.findAccount(username, accName);
		
		if (accountFound == true) {
			manager.writeToTemp(username, accName, newName);
		}
		manager.writeToMain();
	}

	void changeAccountBalance(string username, string accBalance, string newBalance) {
		FileManage manager;
		bool accountFound = manager.findAccount(username, accBalance);
		
		if (accountFound == true) {
			manager.writeToTemp(username, accBalance, newBalance);
		}
		manager.writeToMain();
	}

	void writeToTemp(string username, string existing, string updated) {
		//to read in file
		FileManage manager;
		ifstream myFile;
		myFile.open("accInfo.txt");
		string line;
		int i = 1;
		int count = manager.countOccurrence(username, existing);
		int totalCount = manager.countTotalOccurrence(existing);
		int wordPos = (count + 1);
		cout << "Count: " << count << endl;	
		cout << "Word position is: " << wordPos << endl;
		cout << "Total word occurrence is: " << totalCount << endl;
		//to write to temp file
		ofstream tempFile;
		tempFile.open("temp.txt");
		//read in from myFile

		while (getline(myFile, line)) {
			if (line != existing) {
				tempFile << line << "\n";
			}
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
		//counter to count how many times youve seen the word
		//create array of same size and put values in array
		//if (count == whatever)
		//fill in that instance of the word
		//ignore the word "count" times

		myFile.close();
		tempFile.close();	
	}

	void writeToMain() {
		//to read in file
		ifstream tempFile;
		tempFile.open("temp.txt");
		ofstream myFile;
		//to write to main file
		myFile.open("accInfo.txt");
		string line;

		//read in from myFile
		while (getline(tempFile, line)) {
			myFile << line << "\n";
		}

		myFile.close();
		tempFile.close();
	}

	int countOccurrence(string username, string given) {
		ifstream myFile;
		myFile.open("accInfo.txt");
		string buffer;
		string existingUser;
		int count = 0;
		bool userFound;
		
		//check to see file opened correctly
		if (myFile.fail()) {
			cerr << "Could not open file" << endl;
			exit(1);
		}

		while(buffer != username) {
			myFile >> buffer;
			if (buffer == given) {
				count++;
			}
		}
		//cout << "Instances counted: " << count << endl;
		return count;
		myFile.close();
	}

	int countTotalOccurrence(string existing) {
		ifstream myFile;
		myFile.open("accInfo.txt");
		string buffer;
		int count = 0;
				
		//check to see file opened correctly
		if (myFile.fail()) {
			cerr << "Could not open file" << endl;
			exit(1);
		}

		while (getline(myFile, buffer)) {
			if (buffer == existing) {
				count++;
			}
		}

		//cout << "Total instances counted: " << count << endl;
		return count;
		myFile.close();
	}

	bool emptyFileCheck() {
		int length;
		ifstream myFile;

		myFile.open("accInfo.txt");
		myFile.seekg(0, ios::end); // put the "cursor" at the end of the file
		length = myFile.tellg(); // find the position of the cursor
		myFile.close();

		if (length == 0 ){
			return true;
		}
		else {
			return false;
		}
	}

	void clearFile() {
		ofstream myFile;
		myFile.open("accInfo.txt", ofstream::out | ofstream::trunc);
		myFile.close();
	}
};

#endif
