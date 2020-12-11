#include "account.h"
#include "table.h"
#include "get_number.h"
#include <iostream>

string getpass();

int Acc::ID = 0;

extern StreamTable table;

ostream& operator<<(ostream& out, Acc& account)
{
	table.firstCell(true);

	table << "ИД: " << account.m_ID;
	table << "Логин: " << account._login;
	table << "Пароль: " << account._password;
	table << "Права: " << account._mode;

	return out;
}

istream& operator>>(istream& in, Acc& account)
{
	cout << "Введите логин: "; cin >> account._login;
	cout << "Введите пароль: "; account._password = getpass();
	account._mode = "Юзер";

	return in;
}