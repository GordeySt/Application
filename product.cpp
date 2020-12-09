#include "product.h"
#include "table.h"
#include "get_number.h"
#include <fstream>
#include <iostream>

Product::~Product() {}

extern StreamTable table;

ostream& operator<<(ostream& out, Product* product)
{
	return product->print(out);
}
istream& operator>>(istream& in, Product* product)
{
	return product->set(in);
}

ostream& Product::print(ostream& out)
{
	table << "���" << _name;
	table << "�������������" << _producer;
	table << "���" << _type;
	table << "����" << _price;
	table << "����������" << _amount;

	return out;
}

istream& Product::set(istream& in)
{
	cout << "������� ���: "; getline(cin, _name);
	cout << "������� �������������: "; getline(cin, _producer);
	cout << "������� ���: "; getline(cin, _type);
	_price = getNumber<int>("������� ����: ");
	_amount = getNumber<int>("������� ����������: ");

	return in;
}

void Product::writeToFile(fstream& file)
{
	file << _name << endl;
	file << _producer << endl;
	file << _type << endl;
	file << _price << endl;
	file << _amount << endl;
}

ostream& Import::print(ostream& out)
{
	table << "���" << typeOperation;
	Product::print(out);
	table << "�� ������" << _fromCountry;
	table << "����� ����" << _totalPrice;

	return out;
}

istream& Import::set(istream& in)
{
	Product::set(in);
	cout << "������� �� ����� ������: "; getline(cin, _fromCountry);
	_totalPrice = double(_amount) * _price;

	return in;
}

void Import::writeToFile(fstream& file)
{
	Product::writeToFile(file);
	file << typeOperation << endl;
	file << _fromCountry << endl;
	file << _totalPrice << endl;
}

ostream& Export::print(ostream& out)
{
	table << "���" << typeOperation;
	Product::print(out);
	table << "� ������" << _toCountry;
	table << "����� ����" << _totalPrice;

	return out;
}

istream& Export::set(istream& in)
{
	Product::set(in);
	cout << "������� � ����� ������: "; getline(cin, _toCountry);
	_totalPrice = double(_amount) * _price;

	return in;
}

void Export::writeToFile(fstream& file)
{
	Product::writeToFile(file);
	file << typeOperation << endl;
	file << _toCountry << endl;
	file << _totalPrice << endl;
}