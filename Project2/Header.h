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
		cout << "�������� ����������� �� ���������..." << endl;
		length = 6;
		string = new char[length];
		strcpy(string, "hello");
	}
	String(int length)
	{
		cout << "�������� ����������� � �����������..." << endl;
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
		cout << "�������� ���������� �����������..." << endl;
		length = strlen(str.string) + 1;

		string = new char[length];
		strcpy(string, str.string);
	}
	~String()
	{
		cout << "�������� ����������..." << endl;
		delete string;
	}
	std::string get_string()
	{
		cout << "������:";
		return string;
	}
	int get_length()
	{
		cout << "�����:";
		return length;
	}
	void type_one();
	void input();
	friend istream& operator>>(istream&, String&);
	friend ostream& operator<<(ostream&, const String&);
};
int menu();
void type(String*, int);


