#include<iostream>
#include<string>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include"header.h"
int menu()
{
	int n;
	cout << "1-вывод" << endl;
	cin >> n;
	return n;
}
void String::type_one()
{
	cout << string << endl;
}
void type(String* string, int kol)
{
	int i;
	for (i = 0; i < kol; i++)
	{
		string[i].type_one();
	}
}
void String::input()
{
	cout << "Введите строку" << endl;
	cin >> string;
}
istream& operator>>(istream& in, String& object)
{
	cout << "Работает перегрузка ввода..." << endl;
	cout << "Введите длину строки:";
	cin >> object.length;
	object.string = new char[object.length];
	cout << "Введите строку:";
	cin >> object.string;
	cout << endl;
	return in;
}
ostream& operator<<(ostream& out, const String& object)
{
	cout << "Работает перегрузка вывода..." << endl;
	out << "Длина:" << object.length << endl;
	out << "Строка:" << object.string << endl;
	cout << endl;
	return out;
}