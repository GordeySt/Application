#include "account_repository.h"
#include <iostream>
#include <algorithm>

#define KEY 2002

bool compareLogin(Acc* firstAcc, Acc* secondAcc)
{
	return firstAcc->getLogin() < secondAcc->getLogin();
}

string encryption(string password)
{
	for (int i = 0; i < password.size(); i++)
	{
		password[i] ^= KEY;
	}

	return password;
}

void AccountRepository::addAcc(Acc* account)
{
	if (findAcc(account->getLogin()))
	{
		cout << "Невозможно создать аккаунт. Данный логин уже существует" << endl;
	}
	else
	{
		_accounts.push_back(account);
		cout << "Аккаунт успешно создан." << endl;
		if (account->getLogin() != "admin")
			rewrite();
	}

	if (account->getLogin() != "admin")
		system("pause");
}

bool AccountRepository::findAcc(string login, string password)
{
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (password == "")
		{
			if (_accounts[i]->getLogin() == login)
			{
				return true;
			}
		}
		else
		{
			if (_accounts[i]->getLogin() == login && _accounts[i]->getPass() == password)
				return true;
		}
	}

	return false;
}

void AccountRepository::deleteAcc(string login)
{
	int index;

	if (findAcc(login))
	{
		cout << "Аккаунт успешно удален." << endl;
		_accounts.erase(_accounts.begin() + getIndex(login));
		rewrite();
	}
	else
	{
		cout << "Аккаут с таким логином не найден." << endl;
	}
	system("pause");
}

void AccountRepository::sortAccs()
{
	std::sort(_accounts.begin(), _accounts.end(), compareLogin);
}

void AccountRepository::changeAcc(string login)
{
	if (findAcc(login))
	{
		std::cin >> *_accounts[getIndex(login)];
		cout << "Аккаунт успешно изменён." << endl;
		rewrite();
	}
	else
	{
		cout << "Аккаунт с таким логином не найден" << endl;
	}
	system("pause");
}

void AccountRepository::readFile()
{
	string login, password;

	_file.open(_filename, ios_base::in);

	while (_file >> login >> password)
	{
		if (_file.eof()) break;
		password = encryption(password);
		_accounts.push_back(new Acc(login, password));
	}

	_file.close();
}

void AccountRepository::rewrite()
{
	_file.open(_filename, ios_base::out);

	for (int i = 1; i < _accounts.size(); i++)
	{
		_file << _accounts[i]->getLogin() << endl;
		_file << encryption(_accounts[i]->getPass()) << endl;
	}

	_file.close();
}

void AccountRepository::printRep()
{
	for (int i = 0; i < _accounts.size(); i++)
		cout << *_accounts[i] << endl;
}

int AccountRepository::getIndex(string login)
{
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->getLogin() == login)
			return i;
	}

	return -1;
}