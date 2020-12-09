#include <iostream>
#include <windows.h>
#include <conio.h>
#include "get_number.h"
#include "account.h"
#include "product.h"
#include "table.h"
#include "account_repository.h"
#include "product_repository.h"

void menu();
void auth();
void registration();
void userMenu();
void adminMenu();
string getpass();

StreamTable table(cout);
AccountRepository accountRep("acc_rep.txt");
ProductRepository productRep("product_rep.txt");

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	table.SetCols(2, 20);
	table.MakeBorderExt(true);
	table.SetDelimCol(true, '|');
	table.SetDelimRow(true, '-');

	Acc* admin = new Acc("admin", "password", "Администратор");
	accountRep.addAcc(admin);
	accountRep.readFile();
	productRep.readFile();

	menu();

	return 0;
}

void menu()
{
	bool isEnd = false;
	int choice;

	do
	{
		system("cls");
		isEnd = false;

		cout << "1 - Аутентификация" << endl;
		cout << "2 - Регистрация" << endl;
		cout << "3 - Выход" << endl;

		choice = getNumber<int>("Ваш выбор: ");

		switch (choice)
		{
		case 1: auth(); break;
		case 2: registration(); break;
		case 3: isEnd = true; break;
		default: cout << "Некорректное число." << endl; system("pause"); break;
		}

	} while (!isEnd);
}

void auth()
{
	string login, password;
	cout << "Введите логин: "; cin >> login;
	cout << "Введите пароль: "; password = getpass();

	if (accountRep.findAcc(login, password))
	{
		if (accountRep[accountRep.getIndex(login)]->getLaw() == "Администратор")
		{
			adminMenu();
		}
		else
		{
			userMenu();
		}
	}
	else
	{
		cout << "Неверный логин или пароль." << endl;
		system("pause");
	}
}

void registration()
{
	string login, password;
	cout << "Введите логин: "; cin >> login;
	cout << "Введите пароль: "; password = getpass();

	accountRep.addAcc(new Acc(login, password));
}

void adminMenu()
{
	bool isEnd = false;
	bool isOn = true;
	int choice;

	do
	{
		system("cls");
		isEnd = false;

		cout << "1 - Добавить аккаунт." << endl;
		cout << "2 - Удалить аккаунт." << endl;
		cout << "3 - Изменить аккаунт." << endl;
		cout << "4 - Найти аккаунт." << endl;
		cout << "5 - Вывод всех аккаунтов." << endl;
		cout << "6 - Сортировка аккаунтов." << endl;
		cout << "7 - Открыть файл с аккаунтами." << endl;
		cout << "8 - Добавить препарат." << endl;
		cout << "9 - Удалить перпарат." << endl;
		cout << "10 - Изменить препарат." << endl;
		cout << "11 - Найти препарат." << endl;
		cout << "12 - Вывод импорта." << endl;
		cout << "13 - Вывод экспорта." << endl;
		cout << "14 - Сортировка препаратов." << endl;
		cout << "15 - Фильтрация препаратов по типу." << endl;
		cout << "16 - Открыть файл с препаратами." << endl;
		cout << "17 - Назад" << endl;

		choice = getNumber<int>("Ваш выбор: ");

		switch (choice)
		{
		case 1:
		{
			string login, password;
			cout << "Введите логин: "; cin >> login;
			cout << "Введите пароль: "; password = getpass();
			accountRep.addAcc(new Acc(login, password));
			break;
		}
		case 2:
		{
			string login;
			cout << "Введите логин: "; cin >> login;
			accountRep.deleteAcc(login);
			break;
		}
		case 3:
		{
			string login;
			cout << "Введите логин: "; cin >> login;
			accountRep.changeAcc(login);
			break;
		}
		case 4:
		{
			string login;
			cout << "Введите логин: "; cin >> login;
			if (accountRep.findAcc(login))
			{
				cout << *accountRep[accountRep.getIndex(login)];
			}
			else
			{
				cout << "Аккаунт с таким логином не найден." << endl;
			}
			system("pause");
			break;
		}
		case 5: accountRep.printRep(); system("pause"); break;
		case 6: accountRep.sortAccs(); cout << "Сортировка прошла успешно." << endl; system("pause"); break;
		case 7: system(("start " + accountRep.getFilename()).c_str()); break;
		case 8:
		{
			bool isEnd = false;
			int choice, price, amount;
			string name, producer, type, country;

			cout << "Введите название препарата: "; getline(cin, name);
			cout << "Введите производителя: "; getline(cin, producer);
			cout << "Введите тип препарата: "; getline(cin, type);
			price = getNumber<int>("Введите цену: ");
			amount = getNumber<int>("Введите количество: ");

			do
			{
				cout << "1 - Добавить в импорт." << endl;
				cout << "2 - Добавить в экспорт." << endl;
				choice = getNumber<int>("Ваш выбор: ");

				switch (choice)
				{
				case 1:
				{
					if (productRep.checkDuplicate(name, "Импорт"))
					{
						cout << "Такая запись уже существует. Воспользуйтесь изменением." << endl;
						isEnd = true;
						system("pause");
						break;
					}
					cout << "Введите из какой страны: "; getline(cin, country);
					productRep.addRecord(new Import(name, producer, type, price, amount, country), 1);
					isEnd = true;
					break;
				}
				case 2:
				{
					if (productRep.checkDuplicate(name, "Экспорт"))
					{
						cout << "Такая запись уже существует. Воспользуйтесь изменением." << endl;
						isEnd = true;
						system("pause");
						break;
					}
					cout << "Введите в какую страну: "; getline(cin, country);
					productRep.addRecord(new Export(name, producer, type, price, amount, country), 2);
					isEnd = true;
					break;
				}
				default: cout << "Неккоректное число." << endl; system("pause"); break;
				}

			} while (!isEnd);
			break;
		}
		case 9:
		{
			isOn = true;
			string name;
			cout << "Введите название препарата: "; cin >> name;
			do
			{
				cout << "Выберите, откуда хотите удалить препарат." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				int choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					productRep.deleteRecord(name, "Импорт");
					isOn = false;
					break;
				case 2:
					productRep.deleteRecord(name, "Экспорт");
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);
			break;
		}
		case 10:
		{
			isOn = true;
			string name;
			cout << "Введите название препарата: "; cin >> name;
			do
			{
				cout << "Выберите, где хотите изменить препарат." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				int choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					productRep.changeRecord(name, "Импорт");
					isOn = false;
					break;
				case 2:
					productRep.changeRecord(name, "Экспорт");
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);
			break;
		}
		case 11:
		{
			isOn = true;
			string name;
			cout << "Введите название препарата: "; cin >> name;
			do
			{
				cout << "Выберите, где хотите найти препарат." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				int choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					if (productRep.findRecord(name, "Импорт"))
					{
						cout << productRep[productRep.getIndex(name)];
					}
					else
					{
						cout << "Препарат с таким названием не найден." << endl;
					}
					isOn = false;
					break;
				case 2:
					if (productRep.findRecord(name, "Экспорт"))
					{
						cout << productRep[productRep.getIndex(name)];
					}
					else
					{
						cout << "Препарат с таким названием не найден." << endl;
					}
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);
			system("pause");
			break;
		}
		case 12: productRep.printImport(); system("pause"); break;
		case 13: productRep.printExport(); system("pause"); break;
		case 14: productRep.sortRecords(); cout << "Сортировка прошла успешно." << endl; system("pause"); break;
		case 15:
		{
			isOn = true;
			string typeOfProd;
			cout << "Введите тип препарата: "; cin >> typeOfProd;
			do
			{
				cout << "Выберите, где хотите отфильтровать препараты." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					productRep.filterRecord(typeOfProd, "Импорт");
					isOn = false;
					break;
				case 2:
					productRep.filterRecord(typeOfProd, "Экспорт");
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);
			system("pause");
			break;
		}
		case 16: system(("start " + productRep.getFilename()).c_str()); break;
		case 17: isEnd = true; break;
		default: cout << "Неккоректное число." << endl; system("pause"); break;
		}

	} while (!isEnd);
}

void userMenu()
{
	bool isEnd = false;
	bool isOn = true;
	int choice;

	do
	{
		system("cls");
		isEnd = false;

		cout << "1 - Добавить препарат." << endl;
		cout << "2 - Удалить препарат." << endl;
		cout << "3 - Изменить препарат." << endl;
		cout << "4 - Найти препарат." << endl;
		cout << "5 - Вывод импорта." << endl;
		cout << "6 - Вывод экспорта." << endl;
		cout << "7 - Сортировка препаратов." << endl;
		cout << "8 - Фильтрация препаратов по типу." << endl;
		cout << "9 - Открыть файл с препаратами." << endl;
		cout << "10 - Назад" << endl;
		
		choice = getNumber<int>("Ваш выбор: ");

		switch (choice)
		{
		case 1:
		{
			bool isEnd = false;
			int choice, price, amount;
			string name, producer, type, country;

			cout << "Введите название препарата: "; getline(cin, name);
			cout << "Введите производителя: "; getline(cin, producer);
			cout << "Введите тип препарата: "; getline(cin, type);
			price = getNumber<int>("Введите цену: ");
			amount = getNumber<int>("Введите количество: ");

			do
			{
				cout << "1 - Добавить в импорт." << endl;
				cout << "2 - Добавить в экспорт." << endl;
				choice = getNumber<int>("Ваш выбор: ");

				switch (choice)
				{
				case 1:
				{
					if (productRep.checkDuplicate(name, "Импорт"))
					{
						cout << "Такая запись уже существует. Воспользуйтесь изменением." << endl;
						isEnd = true;
						system("pause");
						break;
					}
					cout << "Введите из какой страны: "; getline(cin, country);
					productRep.addRecord(new Import(name, producer, type, price, amount, country), 1);
					isEnd = true;
					break;
				}
				case 2:
				{
					if (productRep.checkDuplicate(name, "Экспорт"))
					{
						cout << "Такая запись уже существует. Воспользуйтесь изменением." << endl;
						isEnd = true;
						system("pause");
						break;
					}
					cout << "Введите в какую страну: "; getline(cin, country);
					productRep.addRecord(new Export(name, producer, type, price, amount, country), 2);
					isEnd = true;
					break;
				}
				default: cout << "Неккоректное число." << endl; system("pause"); break;
				}

			} while (!isEnd);
			break;
		}
		case 2:
		{
			isOn = true;
			string name;
			cout << "Введите название препарата: "; cin >> name;
			
			do
			{
				cout << "Выберите, откуда хотите удалить препарат." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				int choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					productRep.deleteRecord(name, "Импорт");
					isOn = false;
					break;
				case 2:
					productRep.deleteRecord(name, "Экспорт");
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);

			break;
		}
		case 3:
		{
			isOn = true;
			string name;
			cout << "Введите название препарата: "; cin >> name;
			do
			{
				cout << "Выберите, откуда хотите удалить препарат." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					productRep.changeRecord(name, "Импорт");
					isOn = false;
					break;
				case 2:
					productRep.changeRecord(name, "Экспорт");
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);
			break;
		}
		case 4:
		{
			isOn = true;
			string name;
			cout << "Введите название препарата: "; cin >> name;
			do
			{
				cout << "Выберите, где хотите найти препарат." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					if (productRep.findRecord(name, "Импорт"))
					{
						cout << productRep[productRep.getIndex(name)];
					}
					else
					{
						cout << "Препарат с таким названием не найден не найден." << endl;
					}
					isOn = false;
					break;
				case 2:
					if (productRep.findRecord(name, "Экспорт"))
					{
						cout << productRep[productRep.getIndex(name)];
					}
					else
					{
						cout << "Препарат с таким названием не найден не найден." << endl;
					}
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);
			system("pause");
			break;
		}
		case 5: productRep.printImport(); system("pause"); break;
		case 6: productRep.printExport(); system("pause"); break;
		case 7: productRep.sortRecords(); cout << "Сортировка прошла успешно." << endl; system("pause"); break;
		case 8:
		{
			isOn = true;
			string typeOfProd;
			cout << "Введите тип препарата: "; cin >> typeOfProd;
			do
			{
				cout << "Выберите, где хотите отфильтровать препараты." << endl;
				cout << "1. Импорт" << endl;
				cout << "2. Экспорт" << endl;
				choice = getNumber<int>("Ваш выбор: ");
				switch (choice)
				{
				case 1:
					productRep.filterRecord(typeOfProd, "Импорт");
					isOn = false;
					break;
				case 2:
					productRep.filterRecord(typeOfProd, "Экспорт");
					isOn = false;
					break;
				default:
					cout << "Неккоректное число." << endl; break;
				}
			} while (isOn);
			system("pause");
			break;
		}
		case 9: system(("start " + productRep.getFilename()).c_str()); break;
		case 10: isEnd = true; break;
		default: cout << "Неккоректное число." << endl; system("pause"); break;
		}

	} while (!isEnd);
}