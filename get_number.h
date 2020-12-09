#pragma once

#include <iostream>

using namespace std;

template<class T>
T getNumber(const char* str)
{
	bool isCorrect = true;
	T number;

	do
	{
		isCorrect = true;
		cout << str;
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка. Вы ввели буквы. Введите число." << endl;
			isCorrect = false;
		}
		else
		{
			cin.ignore(32767, '\n');
		}
	} while (!isCorrect);

	return number;
}