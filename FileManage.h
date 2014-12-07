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

	void readFile(string username, string &password, string &realName, string &saltPW, string &accName1, string &bal1, string &accName2, string &bal2, string &accName3, string &bal3) {
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

				myFile.seekg(0, ios::cur);
			}			
		}
		cout << "Current pos: " << myFile.tellg() << endl;
		cout << "Hello " << realName << "." << endl;

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
		
		//cout << "You have " << count/2 << " account(s) free." << endl;
		count /= 2;

		myFile.close();

		return count;
	}

	void changeInformation(string username, string& password, string& realName, string& saltPW, string& accName1, string& bal1, string& accName2, string& bal2, string& accName3, string& bal3) {
		FileManage manager;
		ofstream myFile;
		//username = "jyoung";
		string placeholder = "!!!";
		int count = 0;
		int pos;
		myFile.open("accInfo.txt", ios::app);
		myFile.seekp(0, ios::beg);
		cout << "Current pos: " << myFile.tellp() << endl; 

		//find username given
		if (manager.findUsername(username) == true) {
			count = manager.countCharacters(username);
		}

		//read in information under that username
		manager.readFile(username, password, realName, saltPW, accName1, bal1, accName2, bal2, accName3, bal3);
		pos = myFile.tellp();
		cout << pos << endl;
		
		myFile.seekp(pos - count, ios::cur);
		cout << "Current pos: " << pos << endl;  
		
		//change the information needed
		//this will only be acc name and balance
		myFile << username << "\n";
		myFile << password << "\n";
		myFile << realName << "\n";
		myFile << saltPW << "\n";
		myFile << accName1 << "\n";
		myFile << bal1 << "\n";
		myFile << accName2 << "\n";
		myFile << bal2 << "\n";
		myFile << accName3 << "\n";
		myFile << bal3 << "\n";
		myFile << placeholder << "\n";

		myFile.close();
	}

	int countCharacters(string username) {
		ifstream myFile;
		myFile.open("accInfo.txt");
		string buffer;
		string existingUser;
		int count = 0;
		
		//check to see file opened correctly
		if (myFile.fail()) {
			cerr << "Could not open file" << endl;
			exit(1);
		}

		while(myFile.good()) {
			myFile >> existingUser;
			if (existingUser == username) {
				while (buffer != "!!!") {
					myFile >> buffer;
					count += buffer.length();
				}
			}
		}
		cout << "Characters counted: " << count << endl;
		return count;
		myFile.close();
	}

	void clearFile() {
		ofstream myFile;
		myFile.open("accInfo.txt", ofstream::out | ofstream::trunc);
		myFile.close();
	}
};
# endif
