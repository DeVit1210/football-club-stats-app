#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<conio.h>
#include"Authorization.h"
#include"Player.h"
#include"Game.h"
using namespace std;

void Administrator::registration()
{
	int adminQuantity = readAmount(ADMINS_AMOUNT);
	if (adminQuantity == 1)
	{
		cout << "\n  ������������� ��� ��������������� � �������!\n\n  ������� �����?(y/n): ";
		char choice;
		cin >> choice;
		if (choice == 'y')
		{
			system("cls");
			cin.ignore(32767, '\n');
			int i = Enter();
			if (i == SUCCESS)
				admin_menu();
		}
		else if (cin.fail() || choice != 'n')
		{
			clear_bufer();
			cout << "������� �������� ��������!" << endl;
			push_and_clear_page();
		}
		else
		{
			push_and_clear_page();
			cin.ignore(32767, '\n');
			return;
		}
	}
	else
	{
		set_login();
		set_password();
		set_surname();
		set_name();
		set_patronymic();
		write_admin_data();
		writeAmount(++adminQuantity, ADMINS_AMOUNT);
		cout << "\n  ����������� �������������� ��������� �������!" << endl;
		push_and_clear_page();
		admin_menu();
	}
}

int Administrator::Enter()
{
	int adminQuantity = readAmount(ADMINS_AMOUNT);
	if (adminQuantity == 0)
	{
		cout << "\n  ������������� ��� �� ��������������� � �������!\n  ������� ������������������?(y/n): ";
		char choice;
		cin >> choice;
		if (choice == 'y')
		{
			cin.ignore(32767, '\n');
			system("cls");
			registration();
			return AUTHORIZATION_ERROR;
		}
		else if (cin.fail() || choice != 'n')
		{
			clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
			push_and_clear_page();
			return AUTHORIZATION_ERROR;
		}
		else
		{
			push_and_clear_page();
			return AUTHORIZATION_ERROR;
		}
	}
	system("cls");
	read_admin_data();
	if (check_login())
		if (check_password())
			return SUCCESS;

	push_and_clear_page();
	return AUTHORIZATION_ERROR;
}

bool Administrator::check_login()
{
	cout << "\n  ������� �����: ";
	string admin_login;
	while (true)
	{
		cin >> admin_login;
		if (m_login == admin_login)
		{
			cout << "\n  ������� ������: ";
			return true;
		}
		else
		{
			cout << "\n  ����� ������ �����������!\n  ������ ����������� ��� ���(y/n): ";
			if (!chooseNextStep()) return false;
			else cout << "  ������� �����: ";
		}
	}
}
void Administrator::admin_menu()
{
	while (true)
	{
		cout << "\n  1-������ � �������� ��������\n"
			"  2-������ � �������\n"
			"  3-�����\n"
			"\n  ��� �����?   ";
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
		default: cout << "  " << INPUT_ERROR << endl;
			clear_bufer();
			push_and_clear_page();
			break;
		}
	}
}

void Administrator::read_admin_data()
{
	ifstream fadmin(ADMINS_DATA);
	fadmin >> m_login >> m_password >> m_surname
		>> m_name >> m_patronymic;
	fadmin.close();
}

void Administrator::showAccounts(vector<User>& vec_of_users)
{
	cout << "===================================================================================" << endl;
	cout << " �  |    �����     |    ������      |    �������     |    ���      |   ��������    |" << endl;
	cout << "===================================================================================" << endl;

	for (size_t i = 0; i < vec_of_users.size(); i++)
	{
		vec_of_users.at(i).hash_password();
		cout << setw(4) << i + 1
			<< "|" << setw(14) << vec_of_users.at(i).m_login
			<< "|" << setw(16) << vec_of_users.at(i).m_password
			<< "|" << setw(16) << vec_of_users.at(i).m_surname
			<< "|" << setw(14) << vec_of_users.at(i).m_name << "|"
			<< setw(14) << vec_of_users.at(i).m_patronymic << "|" << endl;
		cout << "====================================================================================" << endl;
		vec_of_users.at(i).hash_password();
	}
}

void Administrator::addAccount(vector<User>& vec_of_users)
{
	system("cls");
	User new_user;
	new_user.set_login();
	while (true)
	{
		new_user.set_password();
		if (new_user.verify_password(vec_of_users))
		{
			hash_password();
			cout << "\n  ������ ������ �������!" << endl;
			break;
		}
		else cout << "\n  � ���������, ���� ������ ��� �����!\n  ���������� ��� ���!" << endl;
	}
	new_user.set_surname();
	new_user.set_name();
	new_user.set_patronymic();
	vec_of_users.push_back(new_user);
	cout << "\n  ����������� ������������ ��������� �������!" << endl;
}


void Administrator::accountsWork()
{
	int accountsQuantity = readAmount(USERS_AMOUNT);
	vector <User> user_data;
	user_data.reserve(accountsQuantity);
	read_user_data(user_data);
	while (true)
	{
		switch (accounts_work_menu())
		{
		case 1:
			if (user_data.size() == 0)
				cout << "\n  � ���������, �� ���� ������������ �� ��������������� � �������!" << endl;
			else showAccounts(user_data);
			break;
		case 2: addAccount(user_data); break;
		case 3: editAccount(user_data); break;
		case 4: deleteAccount(user_data); break;
		case 5: write_user_data(user_data);
			writeAmount(user_data.size(), USERS_AMOUNT);
			system("cls");
			return; break;
		default: cout << INPUT_ERROR << endl;
			clear_bufer();
		}
		push_and_clear_page();
	}
}
void Administrator::deleteAccount(vector<User>& vec_of_users)
{
	if (!vec_of_users.size())
	{
		cout << "\n  � ���������, �� ���� ������������ �� �������� � �������!" << endl;
		return;
	}
	system("cls");
	showAccounts(vec_of_users);
	size_t number_of_deleted_account;
	cout << "\n  ������� ����� ��������� ������: ";
	cin >> number_of_deleted_account;
	cin.ignore(32767, '\n');
	number_of_deleted_account--;
	if (cin.good() && number_of_deleted_account >= 0 && number_of_deleted_account < vec_of_users.size())
	{
		vec_of_users.erase(vec_of_users.begin() + number_of_deleted_account);
		cout << "\n  �������� ������ ��������� �������!" << endl;
	}
	else if (cin.good())
		cout << "\n  ���... ������ � ����� ������� �� ����������!" << endl;
	else
	{
		clear_bufer();
		cout << "  " << INPUT_ERROR << endl;
	}
}

void Administrator::editAccount(vector<User>& vec_of_users)
{
	if (!vec_of_users.size())
	{
		cout << "\n  � ���������, �� ���� ������������ �� �������� � �������!" << endl;
		return;
	}
	system("cls");
	showAccounts(vec_of_users);
	size_t number_of_edited_account;
	cout << "\n  ������� ����� ���������� ������: ";
	cin >> number_of_edited_account;
	cin.ignore(32767, '\n');
	number_of_edited_account--;
	if (cin.good() && number_of_edited_account >= 0 && number_of_edited_account < vec_of_users.size())
	{
		cout << "\n  ��� ���������� ��������?" << endl;
		cout << "\n  1-�����\n  2-������\n  3-�������\n  4-���\n  5-��������\n";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1: vec_of_users.at(number_of_edited_account).change_login(); break;
		case 2: vec_of_users.at(number_of_edited_account).change_password(); break;
		case 3: vec_of_users.at(number_of_edited_account).change_surname(); break;
		case 4: vec_of_users.at(number_of_edited_account).change_name(); break;
		case 5: vec_of_users.at(number_of_edited_account).change_patronymic(); break;
		default: cout << "  " << INPUT_ERROR << endl;
			clear_bufer();
		}
	}
	else if (cin.good())
		cout << "\n  � ���������, ������ � ����� ������� �� ����������" << endl;
	else
	{
		clear_bufer();
		cout << INPUT_ERROR << endl;
	}
}

void Administrator::addPlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats, int& number_of_players)
{
	system("cls");
	IdentityData temp_data;
	Statistics temp_stats;
	cout << "\n  ������� ������� ����� ����������: ";
	int id = get_id(vec_of_players_data);
	temp_data.set_data(id);
	temp_stats.set_start_stats(id);
	vec_of_players_data.push_back(temp_data);
	vec_of_players_stats.push_back(temp_stats);
	cout << "\n  ������ ������� ���������!" << endl;
}

void Administrator::add_game_data(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats, vector<Game>& vec_of_games)
{
	system("cls");
	Game game;
	game.set_game_data(vec_of_players_stats, vec_of_players_data);
	vec_of_games.push_back(game);
}

void Main::show_games(vector<Game>& vec_of_games)
{
	if (vec_of_games.empty())
		cout << "\n  � ���������, �� ���� ������ �� ���� �� ���� ���������!" << endl;
	else
	{
		cout << "============================================" << endl;
		cout << "|  ��������  |   C���  | ������ | �������  |" << endl;
		cout << "============================================" << endl;
		for (size_t i = 0; i < vec_of_games.size(); i++)
		{
			cout << "|" << setw(12) << vec_of_games.at(i).get_opp_name()
				<< "|" << setw(6) << vec_of_games.at(i).get_scored()
				<< ":" << setw(2) << vec_of_games.at(i).get_conceded()
				<< "|" << setw(7) << vec_of_games.at(i).get_yellow_cards_quantity()
				<< "|" << setw(7) << vec_of_games.at(i).get_red_cards_quantity() << endl;
			cout << "=============================================" << endl;
		}
	}
}

void Administrator::deletePlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	if (vec_of_players_data.empty())
		cout << "\n  � ���������, �� ���� ����� �� �������� � ������ �������!" << endl;
	else
	{
		system("cls");
		showStats(vec_of_players_data, vec_of_players_stats);
		cout << "\n  ������� ����� ������, ������ � ������� ���������� �������: ";
		int index_for_delete = 0;
		int deleted_player_id = check_id(vec_of_players_stats, index_for_delete);
		if (deleted_player_id == NO_PLAYER_WITH_SUCH_NUMBER_ERROR)
		{
			cout << "\n  � ���������, ������ � ����� ������� � ������� ���!" << endl;
			return;
		}
		cout << "\n  �� ������ ������� ������ c �������� " << vec_of_players_data.at(index_for_delete).get_surname() << "?(y/n): ";
		if (chooseNextStep())
		{
			vec_of_players_stats.erase(vec_of_players_stats.begin() + index_for_delete);
			vec_of_players_data.erase(vec_of_players_data.begin() + index_for_delete);
			cout << "\n  �������� ��������� �������!" << endl;
		}
	}
}

void Administrator::editPlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	if (vec_of_players_data.empty())
		cout << "\n  � ���������, �� ���� ����� �� ��� �������� � ������ �������!" << endl;
	else
	{
		showStats(vec_of_players_data, vec_of_players_stats);
		cout << "\n  ������� ����� ������, ������ � ������� ���������� ��������: ";
		int number_of_edited_player;
		int edited_player_id = check_id(vec_of_players_stats, number_of_edited_player);
		if (edited_player_id == NO_PLAYER_WITH_SUCH_NUMBER_ERROR)
		{
			cout << "\n  � ���������, ������ � ����� ������� � ������� ���!" << endl;
			return;
		}
		system("cls");
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		show_certain_stats(vec_of_players_data.at(number_of_edited_player), vec_of_players_stats.at(number_of_edited_player));
		cout << "\n  ��� �� ������ ��������?" << endl << endl;
		cout << "  1-������� �����" << endl;
		cout << "  2-�������" << endl;
		cout << "  3-���" << endl;
		cout << "  4-��������" << endl;
		cout << "  5-���� ��������" << endl;
		cout << "  6-���������� ��������� ������" << endl;
		cout << "  7-���������� ������� �����" << endl;
		cout << "  8-���������� ��������" << endl;
		cout << "  9-���������� ������ �������� " << endl;
		cout << "  10-���������� ������� ��������" << endl << endl;
		cout << "  ��� �����?" << endl;
		int choice;
		cin >> choice;
		cin.ignore(32767, '\n');
		int id;
		switch (choice)
		{
		case 1:
			cout << "\n  ������� ����� id: " << endl;
			id = check_unique_number(vec_of_players_data);
			if (id > 0)
			{
				vec_of_players_data.at(number_of_edited_player).change_id(id);
				vec_of_players_stats.at(number_of_edited_player).change_id(id);
			}
			else cout << "\n  ����� � ����� ������� ��� ���� � �������!" << endl;
			break;
		case 2: vec_of_players_data.at(number_of_edited_player).change_surname(); break;
		case 3: vec_of_players_data.at(number_of_edited_player).change_name(); break;
		case 4: vec_of_players_data.at(number_of_edited_player).change_patronymic(); break;
		case 5: vec_of_players_data.at(number_of_edited_player).change_date(); break;
		case 6: vec_of_players_stats.at(number_of_edited_player).set_played_matches_quantity(); break;
		case 7: vec_of_players_stats.at(number_of_edited_player).set_goals_quantity(); break;
		case 8: vec_of_players_stats.at(number_of_edited_player).set_assists_quuantity(); break;
		case 9: vec_of_players_stats.at(number_of_edited_player).set_yellow_cards_quantity(); break;
		case 10: vec_of_players_stats.at(number_of_edited_player).set_red_cards_quantity(); break;
		default: cout << INPUT_ERROR << endl;
			clear_bufer();
		}
		cout << "==================================================================================================================" << endl;
		cout << "| ����� |    �������    |      ���      |    ��������    |���� ��������| C������ | ���� | ���� | ������� | ������ | " << endl;
		cout << "==================================================================================================================" << endl;
		show_certain_stats(vec_of_players_data.at(number_of_edited_player), vec_of_players_stats.at(number_of_edited_player));
	}
}

bool compare_stats_by_id(Statistics obj1, Statistics obj2)
{
	return obj1.player_id < obj2.player_id;
}

bool compare_data_by_id(IdentityData obj1, IdentityData obj2)
{
	return obj1.player_id < obj2.player_id;
}

void Main::sortStats(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	system("cls");
	if (vec_of_players_data.empty())
		cout << "\n  � ���������, �� ���� ����� �� ��� �������� � ������ �������!" << endl;

	else
	{
		cout << "\n  1-������������� �� id\n"
			"  2-������������� �� �������\n"
			"  3-������������� �� ���������� ������� �����\n"
			"  4-������������� �� ���������� ��������\n"
			"  5-������������� �� ���������� ��������� ������\n"
			"\n  ��� ����� ?  ";
		int choice;
		cin >> choice;
		cin.ignore(32767, '\n');
		switch (choice)
		{
		case 1:std::sort(vec_of_players_data.begin(), vec_of_players_data.end(), compare_data_by_id);
			sort(vec_of_players_stats.begin(), vec_of_players_stats.end(), compare_stats_by_id); 
			cout << "\n  ���������� ������� ������� ������������� �� id!" << endl;
			break;
		case 2: sort_by_surname(vec_of_players_data, vec_of_players_stats); break;
		case 3: sort_by_goals_quantity(vec_of_players_data, vec_of_players_stats); break;
		case 4: sort_by_assists_quantity(vec_of_players_data, vec_of_players_stats); break;
		case 5: sort_by_played_matches_quantity(vec_of_players_data, vec_of_players_stats); break;
		default: clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
		}
		showStats(vec_of_players_data, vec_of_players_stats);
	}
}

int get_id(vector<IdentityData>& vec_of_players_data)
{
	while (true)
	{
		int id;
		bool checker(true);
		cin >> id;
		cin.ignore(32767, '\n');
		if (cin.fail())
		{
			clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
			checker = false;
		}
		else if (id<LEFT_NUMBER_RANGE || id>RIGHT_NUMBER_RANGE)
		{
			cout << "  ������ �����! ������� ����� �� 1 �� 99: ";
			checker = false;
		}
		for (size_t i = 0; i < vec_of_players_data.size(); i++)
		{
			if (vec_of_players_data.at(i).get_id() == id)
			{
				cout << "  ����� � ����� ������� ��� ����!\n  ������� ������ id: ";
				checker = false;
			}
		}
		if (checker) return id;
	}
}

void Main::hash_password()
{
	for (int i = 0; i < m_password.length(); i++)
	{
		int new_symb=0;
		int buf = m_password.at(i)+256;
		int bits[8];
		for (int j = 7; j >= 0; j--)
		{
			bits[j] = buf % 2;
			buf = buf / 2;
		}
		for (int j = 0; j < 7;j=j+2)
		{
			int temp = bits[j];
			bits[j] = bits[j + 1];
			bits[j + 1] = temp;
		}
		int k = 0;
		for (int j = 7; j >= 0; j--)
		{
			new_symb += bits[j] * pow(2, k);
			k++;
		} 
		m_password.at(i) = new_symb;
	}
}