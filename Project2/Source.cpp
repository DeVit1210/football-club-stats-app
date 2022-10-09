
#include<iostream>
#include<Windows.h>
#include"header.h"
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	String string1;
	cout << string1.get_length() << endl;
	cout << string1.get_string() << endl;
	String string2(7);
	cout << string2.get_length() << endl;
	cout << string2.get_string() << endl;
	String string3(string2);
	cout << string3.get_length() << endl;
	cout << string3.get_string() << endl << endl << endl;
	String object1;
	cin >> object1;
	cout << "Объект 1:" << endl;
	cout << object1;
	char* string;
	string = new char;
	cout << "Введите строку:";
	cin >> string;
	String object2(string);
	cout << "Объект 2:" << endl;
	cout << object2;
	return 0;
}