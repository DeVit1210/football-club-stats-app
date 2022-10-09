#include<iostream>
#include<fstream>
#include"Authorization.h"

using namespace std;

int User::Enter()
{
	system("cls");
	int userQuantity = readAmount(USERS_AMOUNT);
	User* temp = new User[userQuantity];
	read_user_data(temp, userQuantity);
	cout << "������� �����" << endl;
	string userLogin;
	while (true)
	{
		cin >> userLogin;
		for (int i = 0; i < userQuantity; i++)
		{
			if (temp[i].m_login == userLogin)
			{
				cout << "����� ������ ���������. ������� ������:" << endl;
				string userPassword;
				while (true)
				{
					cin >> userPassword;
					if (temp[i].m_password == userPassword)
					{
						system("cls");
						cout << "����������� ������ �������!" << endl;
						cout << "\n  ����� ����������, " << temp[i].m_name << " " << temp[i].m_patronymic << "!" << endl;
						return 0;
					}
					else cout << "������ ������ �����������!" << endl;
					if (!chooseNextStep()) return -1;
					else cout << "������� ������" << endl;
				}
			}
		}
		cout << "����� ������ �����������!" << endl;
		if (!chooseNextStep()) return -1;
		else cout << "������� ������" << endl;
	}
}

void read_user_data(User* temp, const int number_of_users)
{
	ifstream fusers(USERS_DATA);
	for (int i = 0; i < number_of_users; i++)
	{
		fusers >> temp[i].m_login >> temp[i].m_password >> temp[i].m_surname
			>> temp[i].m_name >> temp[i].m_patronymic;
	}
	fusers.close();
}

void User::registration()
{
	system("cls");
	int userQuantity = readAmount(USERS_AMOUNT);
	input_registration_data();
	ofstream fusers(USERS_DATA, ios::app);
	fusers << m_login << endl << m_password << endl
		<< m_surname << endl << m_name << endl << m_patronymic << endl;
	fusers.close();
	userQuantity++;
	writeAmount(userQuantity, USERS_AMOUNT);
	cout << "����������� ������������ ��������� �������!" << endl;
	push_and_clear_page();
}

void User::change_login()
{
	system("cls");
	cout << "������� ����� �����" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_login;
		if (registrationCheck(m_login)) checker = true;
	}
	cout << "����� ������� �������!" << endl;
}

void User::change_password()
{
	system("cls");
	cout << "������� ����� ������" << endl;
	string newPassword;
	bool checker(false);
	while (!checker)
	{
		cin >> newPassword;
		if (registrationCheck(newPassword)) checker = true;
	}
	cout << "������ ������� �������!" << endl;
}

void User::change_surname()
{
	system("cls");
	cout << "������� ����� �������" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_surname;
		if (registrationCheck(m_surname)) checker = true;
	}
	cout << "������ ������� �������!" << endl;
}

void User::change_name()
{
	system("cls");
	cout << "������� ����� ���" << endl;
	string newName;
	bool checker(false);
	while (!checker)
	{
		cin >> m_name;
		if (registrationCheck(m_name)) checker = true;
	}
	cout << "��� ������� ��������!" << endl;
}

void User::change_patronymic()
{
	system("cls");
	cout << "������� ����� ��������" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_patronymic;
		if (registrationCheck(m_patronymic)) checker = true;
	}
	cout << "�������� ������� ��������!" << endl;
}

void write_user_data(User* temp, const int number_of_users)
{
	ofstream fusers(USERS_DATA);
	for (int i = 0; i < number_of_users; i++)
	{
		fusers << temp[i].m_login << endl << temp[i].m_password << endl << temp[i].m_surname << endl
			<< temp[i].m_name << endl << temp[i].m_patronymic << endl;
	}
	fusers.close();
}