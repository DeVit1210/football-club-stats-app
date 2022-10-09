#include<iostream>
#include<iterator>
#include<iomanip>
#include<string>
#include<vector>
#include"Game.h"
#include"Authorization.h"

enum errors
{
	NO_PLAYER_WITH_SUCH_NUMBER_ERROR = -3,
	DIGIT_ERROR,
	WRONG_SYMBOL_ERROR,
	NO_ERROR
};

void Game::set_opp_name()
{
	cout << "������� �������� ������� ���������" << endl;
	cin >> m_opponent_name;
}

void Game::show_squad(vector<IdentityData>& vec_of_players)
{
	cout << "========================================" << endl;
	cout << "|  �����  |   �������   |      ���     |" << endl;
	cout << "========================================" << endl;
	for (int i = 0; i < PLAYERS_AMOUNT; i++)
	{
		cout << "|" << setw(9) << vec_of_players.at(i).get_id()
			<< "|" << setw(14) << vec_of_players.at(i).get_surname()
			<< "|" <<setw(14) << vec_of_players.at(i).get_name() << endl;

		cout << "========================================" << endl;
	}
}
void Game::set_squad(vector<IdentityData>& vec_of_players, vector<Statistics>& vec_of_players_stats)
{
	system("cls");
	int players_quantity = 0;
	while (players_quantity != PLAYERS_AMOUNT)
	{
		int counter = 0;
		show_squad(vec_of_players);
		cout << "������� id ������, ���������� ������� � �����" << endl;
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num && !is_already_in_the_squad(player_num, players_quantity))
		{
			cout << "�� ������ �������� ������ � �������� " << vec_of_players.at(counter).get_surname() << "?" << endl;
			if (chooseNextStep())
			{
				m_squad_players_id[players_quantity] = player_num;
				players_quantity++;
				vec_of_players_stats.at(counter).add_played_matches_quantity();
				cout << "����� � " << players_quantity << " ������� �������� � ������!" << endl;
			}

		}
		else if (player_num)
			cout << "���� ����� ��� ������� � ������ �� ����! " << endl;
		else cout << "������ � ����� ������� ��� � ������� �������!" << endl;
		push_and_clear_page();
	}
}

bool Game::is_already_in_the_squad(int id, int num_of_players)
{
	for (int i = 0; i < num_of_players; i++)
		if (m_squad_players_id[i] == id)
			return true;

	return false;
}

void Game::set_scored_quantity()
{
	cout << "������� ���������� ������� �������� �����" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_scored_goals_quantity;
		cin.ignore(32767, '\n');
		if (cin.fail())
		{
			cin.clear();
			cout << INPUT_ERROR << endl;
		}
		else if (m_scored_goals_quantity < 0)
			cout << "� ���������, ������ ������ ������������� ���������� �����! ���������� ��� ���!" << endl;
		else if (m_scored_goals_quantity > 10)
		{
			cout << "�� �������, ��� ������� ������ �� ����� " << m_scored_goals_quantity << " �����?" << endl;
			if (chooseNextStep())
				checker = true;
			else cout << "������ ������������ ��� ����� ������!\n���������� ��� ���!" << endl;
		}
		else checker = true;
	}
	cout << "������ � ������� ����� ������� �������!" << endl;
}

void Game::set_conceded_quantity()
{
	cout << "������� ���������� ����������� �������� �����" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_conceded_goals_quantity;
		cin.ignore(32767, '\n');
		if (cin.fail())
		{
			cin.clear();
			cout << INPUT_ERROR << endl;
		}
		else if (m_conceded_goals_quantity < 0)
			cout << "������ ���������� ������������� ���������� �����! ���������� ��� ���!" << endl;
		else if (m_conceded_goals_quantity > 10)
		{
			cout << "�� �������, ��� ������� ���������� �� ����� " << m_conceded_goals_quantity << " �����?" << endl;
			if (chooseNextStep())
				checker = true;
			else cout << "������ ������������ ��� ����� ������!\n���������� ��� ���!" << endl;
		}
		else checker = true;
	}
	cout << "������ � ����������� ����� ������� �������!" << endl;
}

void Game::set_yellow_cards_quantity()
{
	cout << "������� ���������� ������ �������� � �����" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_yellow_cards_quantity;
		cin.ignore(32767, '\n');
		if (cin.fail())
		{
			cin.clear();
			cout << INPUT_ERROR << endl;
		}
		else if (m_yellow_cards_quantity < 0)
			cout << "������ �������� ������������� ���������� ��������! ���������� ��� ���!" << endl;
		else if (m_yellow_cards_quantity > 10)
		{
			cout << "�� �������, ��� ������� �������� �� ����� " << m_yellow_cards_quantity << " ������ ��������?" << endl;
			if (chooseNextStep())
				checker = true;
			else cout << "������ ������������ ��� ����� ������!\n���������� ��� ���!" << endl;
		}
		else checker = true;
	}
	cout << "������ � ���������� ������ ��������� ������� �������!" << endl;
	push_and_clear_page();
}

void Game::set_red_cards_quantity()
{
	cout << "������� ���������� ������� �������� � �����" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_red_cards_quantity;
		cin.ignore(32767, '\n');
		if (cin.fail())
		{
			cin.clear();
			cout << INPUT_ERROR << endl;
		}
		else if (m_red_cards_quantity < 0)
			cout << "������ �������� ������������� ���������� ��������! ���������� ��� ���!" << endl;
		else if (m_red_cards_quantity > 10)
		{
			cout << "�� �������, ��� ������� �������� �� ����� " << m_red_cards_quantity << " ������ ��������?" << endl;
			if (chooseNextStep())
				checker = true;
			else cout << "������ ������������ ��� ����� ������!\n���������� ��� ���!" << endl;
		}
		else checker = true;
	}
	cout << "������ � ���������� ������� ��������� ������� �������!" << endl;
	push_and_clear_page();
}

void Game::set_match_result()
{
	if (m_scored_goals_quantity < m_conceded_goals_quantity)
		m_match_result = LOSE;
	else if (m_scored_goals_quantity > m_conceded_goals_quantity)
		m_match_result = WIN;
	else m_match_result = DRAW;
}

void Game::add_played_matches_in_stats(vector<Statistics>& vec_of_players)
{
	for (int i = 0; i < PLAYERS_AMOUNT; i++)
		for (int j = 0; i < vec_of_players.size(); j++)
			if (m_squad_players_id[i] = vec_of_players.at(j).get_id())
				vec_of_players.at(j).add_played_matches_quantity();
}

void Game::add_goals_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	int i = 0;
	while (i < m_scored_goals_quantity)
	{
		int counter = 0;
		show_squad(vec_of_players_data);
		cout << "������� ����� ������, ��������� " << i+1 << " ���: " << endl;
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num>=0)
		{
			cout << "��� � " << i+1 << "����� " << vec_of_players_data.at(counter).get_surname()
				<< " " << vec_of_players_data.at(counter).get_name() << "?(y/n)" << endl;
			if (chooseNextStep())
			{
				vec_of_players_stats.at(counter).add_goals_quantity();
				add_assist_in_stats(vec_of_players_stats, vec_of_players_data);
				i++;
			}
		}
		push_and_clear_page();
	}
}

void Game::add_assist_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	cout << "��� ��� ����� ����� ����?(y/n)" << endl;
	if (!chooseNextStep())
		return;
	else
	{
		system("cls");
		bool checker(false);
		while (!checker)
		{
			show_squad(vec_of_players_data);
			int counter = 0;
			cout << "������� ����� ������, ��������� ������ " << endl;
			int player_num = check_id(vec_of_players_stats, counter);
			if (player_num)
			{
				cout << "������ ����� " << vec_of_players_data.at(counter).get_surname()
					<< " " << vec_of_players_data.at(counter).get_name() << "?(y/n)" << endl;
				if (chooseNextStep())
				{
					vec_of_players_stats.at(counter).add_assists_quantity();
					checker = true;
				}
			}
		}
	}
}

void Game::add_cards_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	int cards_amount = 0;
	while (cards_amount != m_red_cards_quantity)
	{
		int counter = 0;
		show_squad(vec_of_players_data);
		cout << "������� id ������, ����������� ������� ��������: " << endl;
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num)
		{
			cout << "������� �������� ������� " << vec_of_players_data.at(counter).get_surname() << " "
					<< vec_of_players_data.at(counter).get_name() << "?" << endl;
			if (chooseNextStep())
			{
				vec_of_players_stats.at(counter).add_red_card_in_stats();
				cards_amount++;
			}
			else cout << "������ � ����� ������� � ������� �� ���� ���! ���������� ��� ���!" << endl;
		}
		push_and_clear_page();
	}
}

void Game::add_yellow_cards_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	int cards_amount = 0;
	while (cards_amount != m_yellow_cards_quantity)
	{
		int counter = 0;
		show_squad(vec_of_players_data);
		cout << "������� id ������, ����������� ������ ��������: " << endl;
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num>=0)
		{
			cout << "������ �������� ������� " << vec_of_players_data.at(counter).get_surname() << " "
				<< vec_of_players_data.at(counter).get_name() << "?" << endl;
			if (chooseNextStep())
			{
				vec_of_players_stats.at(counter).add_yellow_card_in_stats();
				cards_amount++;
			}
		}
		push_and_clear_page();
	}
}

void Game::set_game_data(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	if (vec_of_players_stats.size() < PLAYERS_AMOUNT)
	{
		cout << "� ���������, � ������� ������������ ������� ��� ���������� ����:(" << endl;
		push_and_clear_page();
		return;
	}
	else
	{
		set_opp_name();
		set_squad(vec_of_players_data, vec_of_players_stats);
		set_scored_quantity();
		set_conceded_quantity();
		system("cls");
		if (m_scored_goals_quantity)
		{
			add_goals_in_stats(vec_of_players_stats, vec_of_players_data);
		}
		set_yellow_cards_quantity();
		set_red_cards_quantity();
		if (m_yellow_cards_quantity)
			add_yellow_cards_in_stats(vec_of_players_stats, vec_of_players_data);
		if (m_red_cards_quantity)
			add_cards_in_stats(vec_of_players_stats, vec_of_players_data);


		cout << "������ �� ���� ������� ���������" << endl;
	}
}

int check_id(vector<Statistics>& vec_of_players_stats, int& counter)

{
	int id;
	bool checker(false);
	while (!checker)
	{
		cin >> id;
		cin.ignore(32767, '\n');
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << INPUT_ERROR << endl;
		}
		else if (id < 0 || id >99)
			cout << "�� ����� ������������ ����� ������! ������� ����� �� 1 �� 99" << endl;
		else
			checker = true;
	}
	for (int i = 0; i < vec_of_players_stats.size(); i++)
	{
		if (id == vec_of_players_stats.at(i).get_id())
		{
			counter = i;
			return id;
		}
	}

	return NO_PLAYER_WITH_SUCH_NUMBER_ERROR;
}