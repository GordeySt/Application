#pragma once

#include <string>

using namespace std;

class Product
{
protected:
	string _name;
	string _producer;
	string _type;
	string typeOp;
	int _price;
	int _amount;

public:
	Product(string name, string producer, string type, string typeOperation, int price, int amount)
		: _name(name), _producer(producer), _type(type), typeOp(typeOperation), _price(price), _amount(amount) {}
	virtual ~Product() = 0;

	string getName() { return _name; }
	string getProducer() { return _producer; }
	string getType() { return _type; }
	int getPrice() { return _price; }
	int getAmount() { return _amount; }
	string getTypeOp() { return typeOp; }

	void setName(string name) { _name = name; }
	void setProducer(string producer) { _producer = producer; }
	void setType(string type) { _type = type; }

	void changeAmount(int amount, int index)
	{
		if (index == 1)
			_amount += amount;
		if (index == 2)
			_amount -= amount;
	}


	virtual ostream& print(ostream& out);
	virtual istream& set(istream& in);
	virtual void writeToFile(fstream& file);

	friend ostream& operator<<(ostream& out, Product* product);
	friend istream& operator>>(istream& in, Product* product);
};

class Import : public Product
{
private:
	string typeOperation = "Импорт";
	string _fromCountry;
	double _totalPrice;

public:
	Import(string name, string producer, string type, int price, int amount, string fromCountry)
		: Product(name, producer, type, "Импорт", price, amount), _fromCountry(fromCountry)
	{
		_totalPrice = double(amount) * price;
	}
	virtual ~Import() {}

	string getFromCountry() { return _fromCountry; }
	double getTotalPrice() { return _totalPrice; }

	virtual ostream& print(ostream& out);
	virtual istream& set(istream& in);
	virtual void writeToFile(fstream& file);
};

class Export : public Product
{
private:
	string typeOperation = "Экспорт";
	string _toCountry;
	double _totalPrice;

public:
	Export(string name, string producer, string type, int price, int amount, string toCountry)
		: Product(name, producer, type, "Экспорт", price, amount), _toCountry(toCountry)
	{
		_totalPrice = double(amount) * price;
	}
	virtual ~Export() {}

	string getToCountry() { return _toCountry; }
	double getTotalPrice() { return _totalPrice; }

	virtual ostream& print(ostream& out);
	virtual istream& set(istream& in);
	virtual void writeToFile(fstream& file);
};