#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdint>
#include"Authorization.h"
#include"Player.h"

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
	char choice;
	while (true)
	{
		cin >> choice;
		if (choice == 'n')
		{
			return false;
			break;
		}
		if (choice == 'y')
		{
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
	cout << "\n  1-�������� ������ � ����������\n  2-����������� ��� ������\n"
		"  3-�������� ������ �� ����\n  4-����������� ������ � ���� �����";
	cout << "\n  ��� �����?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}

void Main::showStats(vector<IdentityData> &vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	cout << "==================================================================================================================" << endl;
	cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
	cout << "==================================================================================================================" << endl;
	for (int i = 0; i < vec_of_players_data.size(); i++)
	{
		cout << "|" << setw(7) << vec_of_players_data.at(i).get_id()
			<< "|" << setw(15) << vec_of_players_data.at(i).get_surname()
			<< "|" << setw(15) << vec_of_players_data.at(i).get_name()
			<< "|" << setw(16) << vec_of_players_data.at(i).get_patronymic()
			<< "|" << setw(7) << vec_of_players_data.at(i).get_day()
			<< "/" << vec_of_players_data.at(i).get_month()
			<< "/" << vec_of_players_data.at(i).get_year();
		int j = find_same_id(vec_of_players_data.at(i).get_id(), vec_of_players_stats);
			cout << "|" << setw(9) << vec_of_players_stats.at(j).get_played_matches_quantity()
			<< "|" << setw(6) << vec_of_players_stats.at(j).get_goals_quantity()
			<< "|" << setw(6) << vec_of_players_stats.at(j).get_assists_quantity()
			<< "|" << setw(9) << vec_of_players_stats.at(j).get_red_cards_quantity()
			<< "|" << setw(8) << vec_of_players_stats.at(j).get_yellow_cards_quantity() << "|" << endl;
		cout << "==================================================================================================================" << endl;
	}

	push_and_clear_page();
}