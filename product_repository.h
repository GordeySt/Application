#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "product.h"

using namespace std;

class ProductRepository
{
private:
	fstream _file;
	string _filename;
	vector<Product*> _products;

public:
	ProductRepository(string filename) : _filename(filename) {}

	Product* operator[](int index) { return _products[index]; }
	string getFilename() { return _filename; }

	void addRecord(Product* product, int type);
	bool findRecord(string name, string type);
	bool checkDuplicate(string name, string type);
	void deleteRecord(string name, string type);
	void changeRecord(string name, string type);
	void sortRecords();
	void readFile();
	void rewrite();
	void printImport();
	void printExport();
	int getIndex(string name);
};