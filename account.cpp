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

	table << "��: " << account.m_ID;
	table << "�����: " << account._login;
	table << "������: " << account._password;
	table << "�����: " << account._mode;

	return out;
}

istream& operator>>(istream& in, Acc& account)
{
	cout << "������� �����: "; cin >> account._login;
	cout << "������� ������: "; account._password = getpass();
	account._mode = "����";

	return in;
}