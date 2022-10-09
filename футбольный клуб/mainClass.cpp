#include<iostream>
#include<fstream>
#include<cstdint>
#include"Authorization.h"

using namespace std;
int menu()
{
	cout << "Вас приветствует программа учета статистики футбольного клуба 'Динамо'!" << endl;
	cout << "\n  Выберите способ входа в систему: " << endl << endl;
	cout << "  1-Войти как администратор" << endl << "  2-Зарегистрироваться как администратор" << endl <<
		"  3-Войти как пользоваатель" << endl << "  4-Выйти из программы" << endl;
	cout << endl << "  Ваш выбор?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}


bool registrationCheck(string adminData)
{
	if (adminData.length() > 15)
	{
		cout << "Количество символов не должно превышать 15! Придумайте другой логин" << endl;
		return false;
	}
	if (adminData.length() < 5)
	{
		cout << "Количество символов должно быть больше 5! Попробуйте еще раз" << endl;
		return false;
	}
	return true;
}

int readAmount(string path)
{
	ifstream fnum(path, ios::in);
	int amount;
	if (!fnum.is_open())
		return 0;
	else
		fnum >> amount;
	fnum.close();
	return amount;
}

void writeAmount(int amount, string path)
{
	ofstream fnum(path);
	fnum << amount;
	fnum.close();
}

bool chooseNextStep()
{
	cout << "Хотите попробовать еще раз ? (y / n)" << endl;
	char choice;
	while (true)
	{
		cin >> choice;
		cin.ignore(32767, '\n');
		if (choice == 'n')
		{
			system("cls");
			return false;
			break;
		}
		if (choice == 'y')
		{
			system("cls");
			return true;
			break;
		}
		if (cin.fail() || choice != 'y' || choice != 'n')
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Неверное значение! Введите 'y' или 'n'" << endl;
		}
	}
}

void push_and_clear_page()
{
	system("pause");
	system("cls");
}


int accounts_work_menu()
{
	cout << "\n  1-Просмотреть все учетные записи\n  2-Добавить учетную запись\n"
		"  3-Отредактировать учетную запись\n  4-Удалить учетную запись\n";
	cout << "\n  Ваш выбор?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}

int players_work_menu()
{
	cout << "\n1-Добавить запись о футболисте\n2-Просмотреть все записи\n";
	cout << "\n  Ваш выбор?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}

