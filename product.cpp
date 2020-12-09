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
	table << "Имя" << _name;
	table << "Производитель" << _producer;
	table << "Тип" << _type;
	table << "Цена" << _price;
	table << "Количество" << _amount;

	return out;
}

istream& Product::set(istream& in)
{
	cout << "Введите имя: "; getline(cin, _name);
	cout << "Введите производителя: "; getline(cin, _producer);
	cout << "Введите тип: "; getline(cin, _type);
	_price = getNumber<int>("Введите цену: ");
	_amount = getNumber<int>("Введите количество: ");

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
	table << "Тип" << typeOperation;
	Product::print(out);
	table << "Из страны" << _fromCountry;
	table << "Общая цена" << _totalPrice;

	return out;
}

istream& Import::set(istream& in)
{
	Product::set(in);
	cout << "Введите из какой страны: "; getline(cin, _fromCountry);
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
	table << "Тип" << typeOperation;
	Product::print(out);
	table << "В страну" << _toCountry;
	table << "Общая цена" << _totalPrice;

	return out;
}

istream& Export::set(istream& in)
{
	Product::set(in);
	cout << "Введите в какую страну: "; getline(cin, _toCountry);
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