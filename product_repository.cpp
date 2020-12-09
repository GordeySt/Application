#include "product_repository.h"
#include "table.h"
#include "str_tolower.h"
#include <windows.h>
#include <iostream>
#include <algorithm>

using namespace std;

extern StreamTable table;

bool compareName(Product* firstProduct, Product* secondProduct)
{
	return firstProduct->getName() < secondProduct->getName();
}

bool compareProducer(Product* firstProduct, Product* secondProduct)
{
	return firstProduct->getProducer() < secondProduct->getProducer();
}

bool compareType(Product* firstProduct, Product* secondProduct)
{
	return firstProduct->getType() < secondProduct->getType();
}

bool comparePrice(Product* firstProduct, Product* secondProduct)
{
	return firstProduct->getPrice() < secondProduct->getPrice();
}

bool compareAmount(Product* firstProduct, Product* secondProduct)
{
	return firstProduct->getAmount() < secondProduct->getAmount();
}

void ProductRepository::addRecord(Product* product, int type)
{
	_products.push_back(product);
	cout << "������ ������� ���������. " << endl;

	rewrite();
	system("pause");
}

bool ProductRepository::findRecord(string name, string type)
{
	name = str_tolower(name);
	for (int i = 0; i < _products.size(); i++)
	{
		string prodName = str_tolower(_products[i]->getName());
		if (prodName == name && _products[i]->getTypeOp() == type)
		{
			return true;
		}
	}

	return false;
}

void ProductRepository::filterRecord(string typeOfProduct, string type)
{
	int count = 0;
	typeOfProduct = str_tolower(typeOfProduct);
	for (int i = 0; i < _products.size(); i++)
	{
		string typeName = str_tolower(_products[i]->getType());
		if (typeName == typeOfProduct && _products[i]->getTypeOp() == type)
		{
			table.firstCell(true);

			cout << _products[i] << endl;
		}
		else
		{
			count++;
		}
	}

	if (count == _products.size())
	{
		cout << "��� �� ������ ��������� � ����� �����." << endl;
	}
}

void ProductRepository::deleteRecord(string name, string type)
{
	int index;

	if (findRecord(name, type))
	{
		cout << "������ ������� �������." << endl;
		_products.erase(_products.begin() + getIndex(name));
		rewrite();
	}
	else
	{
		cout << "������ � ����� ������ �� �������." << endl;
	}
	system("pause");
}

void ProductRepository::sortRecords()
{
	int choice;
	cout << "1 - ���." << endl;
	cout << "2 - �������������." << endl;
	cout << "3 - ���." << endl;
	cout << "4 - ����." << endl;
	cout << "5 - ���������." << endl;

	cout << "��� �����: "; cin >> choice;

	switch (choice)
	{
	case 1:
	{
		std::sort(_products.begin(), _products.end(), compareName);
		break;
	}
	case 2:
	{
		std::sort(_products.begin(), _products.end(), compareProducer);
		break;
	}
	case 3:
	{
		std::sort(_products.begin(), _products.end(), compareType);
		break;
	}
	case 4:
	{
		std::sort(_products.begin(), _products.end(), comparePrice);
		break;
	}
	case 5:
	{
		std::sort(_products.begin(), _products.end(), compareAmount);
		break;
	}
	default: cout << "�� ����� ������������ �����." << endl; system("pause"); return;
	}
}

void ProductRepository::changeRecord(string name, string type)
{
	if (findRecord(name, type))
	{
		int choice;
		cout << "1 - ����� ������." << endl;
		cout << "2 - ���." << endl;
		cout << "3 - �������������." << endl;
		cout << "4 - ���." << endl;

		cout << "��� �����: "; cin >> choice;

		switch (choice)
		{
		case 1:
		{
			getchar();
			std::cin >> _products[getIndex(name)];
			break;
		}
		case 2:
		{
			string newname; cout << "������� ���: "; cin >> newname;
			_products[getIndex(name)]->setName(newname);
			break;
		}
		case 3:
		{
			string producer; cout << "������� �������������: "; cin >> producer;
			_products[getIndex(name)]->setProducer(producer);
			break;
		}
		case 4:
		{
			string type; cout << "������� ���: "; cin >> type;
			_products[getIndex(name)]->setType(type);
			break;
		}
		default: cout << "�� ����� ������������ �����." << endl; system("pause"); return;
		}
		cout << "������ ������� �������." << endl;
		rewrite();
	}
	else
	{
		cout << "������ � ����� ������ �� �������" << endl;
	}
	system("pause");
}

void ProductRepository::readFile()
{
	string name, producer, type, country, typeOperation;
	int price, amount, totalPrice;

	_file.open(_filename, ios_base::in);

	while (_file >> name)
	{
		_file >> producer;
		_file >> type;
		_file >> price;
		_file >> amount;
		_file >> typeOperation;
		_file >> country;
		_file >> totalPrice;
		if (typeOperation == "������")
			_products.push_back(new Import(name, producer, type, price, amount, country));
		if (typeOperation == "�������")
			_products.push_back(new Export(name, producer, type, price, amount, country));
	}

	_file.close();
}

void ProductRepository::rewrite()
{
	_file.open(_filename, ios_base::out);

	for (int i = 0; i < _products.size(); i++)
	{
		_products[i]->writeToFile(_file);
	}

	_file.close();
}

void ProductRepository::printImport()
{
	int count = 0;
	for (int i = 0; i < _products.size(); i++)
	{
		table.firstCell(true);
		if (_products[i]->getTypeOp() == "������")
			cout << _products[i] << endl;
		else
			count++;
	}

	if (count == _products.size())
	{
		cout << "��� ���������� � ���� �������." << endl;
	}
}

void ProductRepository::printExport()
{
	int count = 0;
	for (int i = 0; i < _products.size(); i++)
	{
		table.firstCell(true);
		if (_products[i]->getTypeOp() == "�������")
			cout << _products[i] << endl;
		else
			count++;
	}

	if (count == _products.size())
		cout << "��� ���������� � ���� ��������" << endl;
}

int ProductRepository::getIndex(string name)
{
	for (int i = 0; i < _products.size(); i++)
	{
		if (str_tolower(_products[i]->getName()) == str_tolower(name))
			return i;
	}

	return -1;
}

bool ProductRepository::checkDuplicate(string name, string type)
{
	for (int i = 0; i < _products.size(); i++)
	{
		if (_products[i]->getName() == name && _products[i]->getTypeOp() == type)
			return true;
	}

	return false;
}