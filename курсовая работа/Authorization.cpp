#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include"Authorization.h"
#include"Game.h"
#include"Player.h"
#pragma warning(disable:4996)
using namespace std;



void clear_bufer()
{
	cin.clear();
	cin.ignore(32767, '\n');
}

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


bool registrationCheck(string string)
{
	if (string.length() > 15)
	{
		cout << "\n  ���������� �������� �� ������ ��������� 15!\n";
		return false;
	}
	if (string.length() < 5)
	{
		cout << "\n  ���������� �������� ������ ���� ������ 4!\n";
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
			cout << "�������� ��������! ������� 'y' ��� 'n'" << endl;
			clear_bufer();
		}
	}
}

void push_and_clear_page()
{
	system("pause");
	system("cls");
}

void Administrator::write_admin_data()
{
	ofstream fadmins;
	fadmins.open(ADMINS_DATA, ios::app);
	fadmins << m_login << endl << m_password << endl
		<< m_surname << endl << m_name << endl << m_patronymic << endl;
	fadmins.close();
}
int accounts_work_menu()
{
	cout << "\n  1-����������� ��� ������� ������\n  2-�������� ������� ������\n"
		"  3-��������������� ������� ������\n  4-������� ������� ������\n  5-����� � ���� ��������������\n";
	cout << "\n  ��� �����?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}

int players_work_menu()
{
	cout << "\n  1-�������� ������ � ����������"
		"\n  2-����������� ��� ������"
		"\n  3-�������� ������ �� ����"
		"\n  4-����������� ������ � ���� �����"
		"\n  5-������� ������ � ������"
		"\n  6-������������� ������ � ������"
		"\n  7-������������� ���������� �������"
		"\n  8-����������� ���������� ����� �������������� �������"
		"\n  9-����������� ���������� ������� � �������� ����������"
		"\n  10-����� ������ �� ������������ ������"
		"\n  0-����� � ���� ��������������" << endl;
	cout << "\n  ��� �����?" << endl;
	int operation;
	cin >> operation;
	cin.ignore(32767, '\n');
	return operation;
}

void Main::showStats(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	cout << "==================================================================================================================" << endl;
	cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
	cout << "==================================================================================================================" << endl;
	for (int i = 0; i < vec_of_players_data.size(); i++)
		show_certain_stats(vec_of_players_data.at(i), vec_of_players_stats.at(i));
}

bool User::check_login(vector<User>& vec_of_users, int& number_of_user)
{
	bool checker(false);
	while (!checker)
	{
		cout << "\n  ������� �����: ";
		string user_login;
		cin >> user_login;
		for (int i = 0; i < vec_of_users.size(); i++)
		{
			if (user_login == vec_of_users.at(i).m_login)
			{
				cout << "\n  ����� ������ ���������!\n  ������� ������: ";
				number_of_user = i;
				return true;
			}
		}
		cout << "\n  ����� ������ �����������!\n  ������ ����������� ��� ���?(y/n): ";
		if (!chooseNextStep()) return false;
		else cout << "\n  ������� �����: ";
	}
}

bool Main::check_password()
{
	while (true)
	{
		string user_password;
		char pass_input;
		while ((pass_input = _getch()) != '\r')
		{
			user_password.push_back(pass_input);
			_putch('*');
		}
		if (m_password == user_password)
		{
			system("cls");
			cout << "����������� ������ �������!" << endl;
			cout << "\n  ����� ����������, " << m_name << " " << m_patronymic << "!" << endl;
			return true;
		}
		else
		{
			cout << "\n  ������ ������ �����������\n  ������ ����������� ��� ���?(y/n): ";
			if (!chooseNextStep()) return false;
			else cout << "  ������� ������: " ;
		}
	}
}

void Main::set_surname()
{
	cout << "\n  ������� �������: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_surname;
		int result_of_checking = check_string_for_wrong_symbols(m_surname);
		if (result_of_checking == DIGIT_ERROR)
			cout << "  ������ �� ������ ��������� �����!\n  ���������� ��� ���: ";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "  ������ ������ ��������� ������ ����� ��� ����!\n  ���������� ��� ���: ";
		else checker = true;
	}
}

void Main::set_name()
{
	cout << "\n  ������� ���: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_name;
		int result_of_checking = check_string_for_wrong_symbols(m_name);
		if (result_of_checking == DIGIT_ERROR)
			cout << "  ������ �� ������ ��������� �����!\n  ���������� ��� ���:" ;
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "  ������ ������ ��������� ������ ����� ��� ����!\n  ���������� ��� ���: ";
		else checker = true;
	}
}

void Main::set_patronymic()
{
	cout << "\n  ������� ��������: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_patronymic;
		int result_of_checking = check_string_for_wrong_symbols(m_patronymic);
		if (result_of_checking == DIGIT_ERROR)
			cout << "  ������ �� ������ ��������� �����!\n  ���������� ��� ���: ";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "  ������ ������ ��������� ������ ����� ��� ����!\n  ���������� ��� ���: ";
		else checker = true;
	}
}

void Main::set_login()
{
	cout << "\n  ���������� �����(�� ����� 15 ��������): ";
	while (true)
	{
		getline(cin, m_login);
		if (registrationCheck(m_login))
			break;
		else cout << "  ���������� ������ �����: ";
	}
	cout << "\n  ����� ������ �������!" << endl;
}

void Main::set_password()
{
	cout << "  ���������� ������(�� ����� 15 ��������): ";
	while (true)
	{
		getline(cin, m_password);
		if (registrationCheck(m_password))
			break;
		else cout << "  ���������� ������ ������: ";
	}
}

void Main::show_the_most_productive(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	if (!vec_of_players_data.size())
		cout << "\n  � ���������, �� ������ ������ ��� � �������" << endl;
	else
	{
		sort_by_goals_and_assists(vec_of_players_data, vec_of_players_stats);
		const int NUMBER_OF_THE_MOST_PRODUCTIVE = 6;
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		if (vec_of_players_data.size() < NUMBER_OF_THE_MOST_PRODUCTIVE)
		{
			for (int i = 0; i < vec_of_players_data.size(); i++)
				show_certain_stats(vec_of_players_data.at(i), vec_of_players_stats.at(i));
		}
		else
		{
			for (int i = 0; i < NUMBER_OF_THE_MOST_PRODUCTIVE; i++)
				show_certain_stats(vec_of_players_data.at(i), vec_of_players_stats.at(i));
		}
	}

	push_and_clear_page();
}

void Main::findStats(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	cout << "\n  ����� �� ������ ��������� �� ������ �����������?" << endl;
	cout << "  1-�� �������� ������"
		"  2-�� �������"
		"  3-�� ���� ��������" << endl;
	cout << "\n  ��� �����?" << endl;
	int choice; 
	cin >> choice;
	cin.ignore(32767, '\n');
	switch (choice)
	{
	case 1: find_by_id(vec_of_players_data, vec_of_players_stats); break;
	case 2: find_by_surname(vec_of_players_data, vec_of_players_stats); break;
	case 3: find_by_year_of_birth(vec_of_players_data, vec_of_players_stats); break;
	default:  
		clear_bufer();
		cout << "  " << INPUT_ERROR << endl;
		break;
	}

	push_and_clear_page();
}

void find_by_id(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	system("cls");
	cout << "\n  ������� ����� ������: ";
	int player_number = 0;
	if (check_id(vec_of_players_stats, player_number) == NO_PLAYER_WITH_SUCH_NUMBER_ERROR)
		cout << "\n  � ���������, � ������� ��� ������ � ���� �������!" << endl;
	else
	{
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		show_certain_stats(vec_of_players_data.at(player_number), vec_of_players_stats.at(player_number));
	}

}

void Main::find_by_surname(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	system("cls");
	cout << "\n  ������� ������� ������: ";
	string surname_to_find;
	bool checker(false);
	while (!checker)
	{
		cin >> surname_to_find;
		int result_of_checking = check_string_for_wrong_symbols(surname_to_find);
		if (result_of_checking == DIGIT_ERROR)
			cout << "  ������ �� ������ ��������� �����!\n  ���������� ��� ���:";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "  ������ ������ ��������� ������ ����� ��� ����!\n  ���������� ��� ���: ";
		else checker = true;
	}

	bool flag(false);
	bool is_first_letters_matched(false);

	for (int i = 0; i < vec_of_players_data.size(); i++)
	{
		if (surname_to_find == vec_of_players_data.at(i).get_surname())
			flag = true;
		if (vec_of_players_data.at(i).find_similar(surname_to_find))
			is_first_letters_matched = true;
	}

	if (flag)
	{
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		for (int i = 0; i < vec_of_players_data.size(); i++)
			if (surname_to_find == vec_of_players_data.at(i).get_surname())
				show_certain_stats(vec_of_players_data.at(i), vec_of_players_stats.at(i));
	}
	else if (!flag && is_first_letters_matched)
	{
		cout << "\n  � ���������, ������ �� ������ � ��������� �������� �� �������\n  ��������, �� ������ ���:" << endl;
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		for (int i = 0; i < vec_of_players_data.size(); i++)
			if (vec_of_players_data.at(i).find_similar(surname_to_find))
				show_certain_stats(vec_of_players_data.at(i), vec_of_players_stats.at(i));
	}
	else cout << "\n  � ���������, ���������� �� �������!" << endl;

	push_and_clear_page();
}


bool IdentityData::find_similar(string surname)
{
	const int number_of_checking_symbols = 4;
	char first_temp_string[number_of_checking_symbols];
	strncpy(first_temp_string, surname.c_str(), number_of_checking_symbols-1);
	first_temp_string[number_of_checking_symbols-1] = '\0';
	char second_temp_string[number_of_checking_symbols];
	strncpy(second_temp_string, m_surname.c_str(), number_of_checking_symbols-1);
	second_temp_string[number_of_checking_symbols-1] = '\0';
	if (strcmp(second_temp_string, first_temp_string)==0)
		return true;
	else return false;
}

void find_by_year_of_birth(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	cout << "\n  ������� ��� �������� ����������: " << endl;
	const int left_range = 1970;
	const int right_range = 2006;
	int year_of_birth;
	cin.ignore(32767, '\n');
	while (true)
	{
		cin >> year_of_birth;
		if (cin.fail())
		{
			clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
		}
		else if (year_of_birth<left_range || year_of_birth>right_range)
		{
			cout << "\n  �������� ��������! ���������� ��� ���!" << endl;
			clear_bufer();
		}
		else break;
	}
	bool flag(false);
	for (int i = 0; i < vec_of_players_data.size(); i++)
		if(vec_of_players_data.at(i).get_year()==year_of_birth)
			flag=true;

	if (flag)
	{
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		for (int i = 0; i < vec_of_players_data.size(); i++)
			if (vec_of_players_data.at(i).get_year() == year_of_birth)
				show_certain_stats(vec_of_players_data.at(i), vec_of_players_stats.at(i));
	}

	push_and_clear_page();
}


void Main::showRedCardsStats(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	bool is_players_with_red_cards_exist(false);
	for (int i = 0; i < vec_of_players_data.size(); i++)
		if (vec_of_players_stats.at(i).get_red_cards_quantity() > 0)
			is_players_with_red_cards_exist = true;

	if (is_players_with_red_cards_exist)
	{
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		for (int i = 0; i < vec_of_players_data.size(); i++)
			if (vec_of_players_stats.at(i).get_red_cards_quantity() > 0)
				show_certain_stats(vec_of_players_data.at(i), vec_of_players_stats.at(i));
	}

	push_and_clear_page();
}

void user_module()
{
	vector<IdentityData> players_data;
	vector<Statistics> players_stats;
	vector<Game> games_data;
	User user;
	int number_of_players = readAmount(PLAYERS_NUM);
	if (number_of_players)
	{
		read_players_data(players_data);
		read_stats_data(players_stats);
		read_game_data(games_data);
	}
	while (true)
	{
		cout << "\n  1-����������� ������ �� �������"
			"\n  2-������������� ������ �� �������  "
			"\n  3-����� ������ �� ������ "
			"\n  4-����������� ���������� ����� ������������� �������  "
			"\n  5-����������� ���������� ������� � �������� ����������  "
			"\n  6-����������� ���������� ���" << endl;

		cout << "\n  ��� �����?" << endl;
		int choice;
		cin >> choice;
		cin.ignore(32767, '\n');
		switch (choice)
		{
		case 1: user.showStats(players_data, players_stats); break;
		case 2: user.sortStats(players_data, players_stats); break;
		case 3: user.findStats(players_data, players_stats); break;
		case 4: user.show_the_most_productive(players_data, players_stats); break;
		case 5: user.showRedCardsStats(players_data, players_stats); break;
		case 6: user.show_games(games_data); break;
		default: clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
		}
		push_and_clear_page();
	}
}