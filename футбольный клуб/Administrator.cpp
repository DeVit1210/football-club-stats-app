#include<iostream>
#include<fstream>
#include<iomanip>
#include"Authorization.h"
#include"Player.h"

using namespace std;
IdentityData* changeDataSize(IdentityData*, int old_size, int new_size, IdentityData newElement);
Statistics* changeStatsSize(Statistics*, int old_size, int new_size, Statistics newElement);
void Administrator::registration()
{
	int adminQuantity = readAmount(ADMINS_AMOUNT);
	if (adminQuantity == 1)
	{
		cout << "������������� ��� ��������������� � �������!\n\n������� �����?(y/n)" << endl;
		char choice;
		cin >> choice;
		cin.ignore(32767, '\n');
		if (choice == 'y')
		{
			system("cls");
			int i = Enter();
			if (i == 0)
				admin_menu();
		}
		else if (cin.fail() || choice != 'n')
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "������� �������� ��������!" << endl;
			push_and_clear_page();
		}
		else push_and_clear_page();
		return;
	}
	else
	{
		ofstream fadmins;
		fadmins.open(ADMINS_DATA, ios::app);
		input_registration_data();
		fadmins << m_login << endl << m_password << endl
			<< m_surname << endl << m_name << endl << m_patronymic << endl;
		fadmins.close();
		adminQuantity++;
		writeAmount(adminQuantity, ADMINS_AMOUNT);
		cout << "����������� �������������� ��������� �������!" << endl;
		push_and_clear_page();
	}
}

int Administrator::Enter()
{
	int adminQuantity = readAmount(ADMINS_AMOUNT);
	if (adminQuantity == 0)
	{
		cout << "������������� ��� �� ��������������� � �������!\n������� ������������������?" << endl;
		char choice;
		cin >> choice;
		cin.ignore(32767, '\n');
		if (choice == 'y')
		{
			system("cls");
			registration();
		}
		else if (cin.fail() || choice != 'n')
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "������� �������� ��������(" << endl;
			push_and_clear_page();
		}
		else push_and_clear_page();
		return 1;
	}
	system("cls");
	read_admin_data();
	cout << "������� �����" << endl;
	string adminLogin;
	while (true)
	{
		cin >> adminLogin;
		if (m_login == adminLogin)
		{
			cout << "����� ������ ���������. ������� ������:" << endl;
			string adminPassword;
			while (true)
			{
				cin >> adminPassword;
				if (m_password == adminPassword)
				{
					system("cls");
					cout << "����������� ������ �������!" << endl;
					cout << "\n����� ����������, " << m_name << " " << m_patronymic << "!" << endl;
					return 0;
				}
				else cout << "������ ������ �����������! " << endl;
				if (!chooseNextStep()) return -1;
				else cout << "������� ������" << endl;
			}
		}
		else
		{
			cout << "����� ������ �����������!" << endl;
			if (!chooseNextStep()) return -1;
			else cout << "������� �����" << endl;
		}
	}
}

void admin_menu()
{
	while (true)
	{
		cout << "\n  1-������ � �������� ��������\n"
			"  2-������ � �������\n"
			"  3-�����" << endl;
		int operation;
		cin >> operation;
		cin.ignore(32767, '\n');
		switch (operation)
		{
		case 1:
			system("cls");
			accountsWork();
			break;
		case 2:
			system("cls");
			playersWork();
			break;
		case 3: system("cls"); return; break;
		default: cout << "���... ��������� ������ �����" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			push_and_clear_page();
			break;
		}
	}
}

void Main::input_registration_data()
{
	bool checker(false);
	cout << "���������� �����(�� ����� 15 ��������)" << endl;
	while (!checker)
	{
		cin >> m_login;
		if (registrationCheck(m_login))
			checker = true;
	}
	cout << "���������� ������(�� ����� 15 ��������)" << endl;
	checker = false;
	while (!checker)
	{
		cin >> m_password;
		if (registrationCheck(m_password))
			checker = true;
	}
	cout << "������� �������" << endl;
	cin >> m_surname;
	cout << "������� ���" << endl;
	cin >> m_name;
	cout << "������� ��������" << endl;
	cin >> m_patronymic;
}

void Administrator::read_admin_data()
{
	ifstream fadmin(ADMINS_DATA);
	fadmin >> m_login >> m_password >> m_surname
		>> m_name >> m_patronymic;
	fadmin.close();
}

void Administrator::showAccounts(User* usersArray, int number_of_users)
{
	cout << "===================================================================================" << endl;
	cout << " �  |    �����     |    ������      |    �������     |    ���      |   ��������    |" << endl;
	cout << "===================================================================================" << endl;
	for (int i = 0; i < number_of_users; i++)
	{
		cout << setw(4) << i + 1 << "|" << setw(14) << usersArray[i].m_login << "|" << setw(16) << usersArray[i].m_password << "|"
			<< setw(16) << usersArray[i].m_surname << "|" << setw(14) << usersArray[i].m_name << "|"
			<< setw(14) << usersArray[i].m_patronymic << "|" << endl;
		cout << "====================================================================================" << endl;
	}
}

void accountsWork()
{
	Administrator admin;
	while (true)
	{
		int accountsQuantity = readAmount(USERS_AMOUNT);
		User* array_of_users;
		if (accountsQuantity != 0)
		{
			array_of_users = new User[accountsQuantity];
			read_user_data(array_of_users, accountsQuantity);
		}
		else array_of_users = new User;
		switch (accounts_work_menu())
		{
		case 1:
			if (accountsQuantity == 0)
			{
				cout << "� ���������, �� ���� ������������ �� ��������������� � �������!" << endl;
				push_and_clear_page();
			}
			else
			{
				admin.showAccounts(array_of_users, accountsQuantity);
				push_and_clear_page();
			}
			break;
		case 2:
		{
			User user;
			user.registration();
			break;
		}
		case 3: admin.editAccount(array_of_users, accountsQuantity); break;
		case 4: admin.deleteAccount(array_of_users, accountsQuantity); break;
		case 5: system("cls"); return; break;
		default: cout << "���... ��������� ������ �����" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			push_and_clear_page();
		}
	}
}

void Administrator::deleteAccount(User* array_of_users, int& number_of_accounts)
{
	system("cls");
	int number_of_deleted_account;
	cout << "������� ����� ��������� ������" << endl;
	cin >> number_of_deleted_account;
	cin.ignore(32767, '\n');
	number_of_deleted_account--;
	if (cin.good() && number_of_deleted_account >= 0 && number_of_deleted_account < number_of_accounts)
	{
		for (int i = number_of_deleted_account; i < number_of_accounts - 1; i++)
			array_of_users[i] = array_of_users[i + 1];
		number_of_accounts--;
		User* arrTemp = new User[number_of_accounts];
		for (int i = 0; i < number_of_accounts; i++)
			arrTemp[i] = array_of_users[i];

		delete[] array_of_users;
		array_of_users = arrTemp;

		write_user_data(array_of_users, number_of_accounts);
		writeAmount(number_of_accounts, USERS_AMOUNT);
	}
	else if (cin.good())
		cout << "���... ������ � ����� ������� �� ����������!" << endl;
	else
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "���... ��������� ������ �����!" << endl;
	}
	push_and_clear_page();
}

void Administrator::editAccount(User* array_of_users, const int number_of_accounts)
{
	system("cls");
	int number_of_edited_account;
	cout << "������� ����� ���������� ������" << endl;
	cin >> number_of_edited_account;
	cin.ignore(32767, '\n');
	number_of_edited_account--;
	if (cin.good() && number_of_edited_account >= 0 && number_of_edited_account < number_of_accounts)
	{
		cin.ignore(32767, '\n');
		cout << "��� ���������� ��������?" << endl;
		cout << "  1-�����\n  2-������\n  3-�������\n  4-���\n  5-��������\n";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1: array_of_users[number_of_edited_account].change_login(); break;
		case 2: array_of_users[number_of_edited_account].change_password(); break;
		case 3: array_of_users[number_of_edited_account].change_surname(); break;
		case 4: array_of_users[number_of_edited_account].change_name(); break;
		case 5: array_of_users[number_of_edited_account].change_patronymic(); break;
		default: cout << "������� �������� ��������";
			cin.clear();
			cin.ignore(32767, '\n');
		}
		write_user_data(array_of_users, number_of_accounts);
	}
	else if (cin.good())
		cout << "� ���������, ������ � ����� ������� �� ����������(" << endl;
	else
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "���... ��������� ������ �����" << endl;
	}
	push_and_clear_page();
}

void Administrator::addPlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats, int& number_of_players)
{
	IdentityData temp_data;
	Statistics temp_stats;
	cout << "������� ������� ����� ����������" << endl;
	int id;
	cin >> id;
	temp_data.set_data(id);
	temp_stats.set_start_stats(id);

	number_of_players++;

	cout << "������ ������� ���������!" << endl;
	push_and_clear_page();
}

IdentityData* changeDataSize(IdentityData* players_array, int old_size, int new_size, IdentityData newElement)
{
	IdentityData* newArr = new IdentityData[new_size];

	for (int i = 0; i < new_size; i++)
	{
		if (i < old_size)
			newArr[i] = players_array[i];
		else
			newArr[i] = newElement;
	}

	players_array = new IdentityData[new_size];

	return newArr;
}
Statistics* changeStatsSize(Statistics* stats_array, int old_size, int new_size, Statistics newElement)
{
	Statistics* newArr = new Statistics[new_size];

	for (int i = 0; i < new_size; i++)
	{
		if (i < new_size)
			newArr[i] = stats_array[i];
		else
			newArr[i] = newElement;
	}

	delete[] stats_array;
	stats_array = new Statistics[new_size];

	return newArr;
}