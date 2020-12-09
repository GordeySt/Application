#pragma once

#include "account.h"
#include <fstream>
#include <vector>

class AccountRepository
{
private:
	fstream _file;
	string _filename;
	vector<Acc*> _accounts;

public:
	AccountRepository(string filename) : _filename(filename) {}

	Acc* operator[](int index) { return _accounts[index]; }
	string getFilename() { return _filename; }

	void addAcc(Acc* account);
	bool findAcc(string login, string password = "");
	void deleteAcc(string login);
	void changeAcc(string login);
	void sortAccs();
	void readFile();
	void rewrite();
	void printRep();
	int getIndex(string login);
};