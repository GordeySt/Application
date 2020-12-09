#pragma once

#include <string>

using namespace std;

class Acc
{
private:
	string _login;
	string _password;
	string _mode;

public:
	Acc() {}
	Acc(string login, string password, string mode = "Пользователь") : _login(login), _password(password), _mode(mode) {}

	string getLogin() { return _login; }
	string getPass() { return _password; }
	string getLaw() { return _mode; }


	friend ostream& operator<<(ostream& out, Acc& account);
	friend istream& operator>>(istream& in, Acc& account);
};