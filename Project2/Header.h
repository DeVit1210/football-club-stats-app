#pragma once
#include<string>
using namespace std;
#pragma warning (disable:4996)
class String
{
	char* string;
	int length;
public:
	String()
	{
		cout << "Работает конструктор по умолчанию..." << endl;
		length = 6;
		string = new char[length];
		strcpy(string, "hello");
	}
	String(int length)
	{
		cout << "Работает конструктор с параметрами..." << endl;
		this->length = length;
		string = new char[length];
		 strcpy(string, "hello!");
	}
	String(char* strings)
	{
		length = strlen(strings) + 1;
		string = new char[length];
		strcpy(string, strings);
	}
	String(const String& str)
	{
		cout << "Работает коструктор копирования..." << endl;
		length = strlen(str.string) + 1;

		string = new char[length];
		strcpy(string, str.string);
	}
	~String()
	{
		cout << "Работает деструктор..." << endl;
		delete string;
	}
	std::string get_string()
	{
		cout << "Строка:";
		return string;
	}
	int get_length()
	{
		cout << "Длина:";
		return length;
	}
	void type_one();
	void input();
	friend istream& operator>>(istream&, String&);
	friend ostream& operator<<(ostream&, const String&);
};
int menu();
void type(String*, int);


