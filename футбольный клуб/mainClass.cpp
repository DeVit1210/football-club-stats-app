#include<iostream>
#include<fstream>
#include<cstdint>
#include"Authorization.h"

using namespace std;
int menu()
{
	cout << "��� ������������ ��������� ����� ���������� ����������� ����� '������'!" << endl;
	cout << "\n  �������� ������ ����� � �������: " << endl << endl;
	cout << "  1-����� ��� �������������" << endl << "  2-������������������ ��� �������������" << endl <<
		"  3-����� ��� �������������" << endl << "  4-����� �� ���������" << endl;
	cout << endl << "  ��� �����?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}


bool registrationCheck(string adminData)
{
	if (adminData.length() > 15)
	{
		cout << "���������� �������� �� ������ ��������� 15! ���������� ������ �����" << endl;
		return false;
	}
	if (adminData.length() < 5)
	{
		cout << "���������� �������� ������ ���� ������ 5! ���������� ��� ���" << endl;
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
	cout << "������ ����������� ��� ��� ? (y / n)" << endl;
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
			cout << "�������� ��������! ������� 'y' ��� 'n'" << endl;
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
	cout << "\n  1-����������� ��� ������� ������\n  2-�������� ������� ������\n"
		"  3-��������������� ������� ������\n  4-������� ������� ������\n";
	cout << "\n  ��� �����?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}

int players_work_menu()
{
	cout << "\n1-�������� ������ � ����������\n2-����������� ��� ������\n";
	cout << "\n  ��� �����?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}

