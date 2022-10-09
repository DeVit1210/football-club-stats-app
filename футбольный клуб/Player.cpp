#include<iostream>
#include<fstream>
#include"Authorization.h"
#include"Player.h"
#include<vector>
#include<algorithm>

using namespace std;

void Statistics::set_start_stats(int id)
{
	player_id = id;
	m_match_played_quantity = 0;
	m_goals_quantity = 0;
	m_assists_quantity = 0;
	m_red_cards_quantity = 0;
	m_yellow_cards_quantity = 0;
}

void IdentityData::set_data(int id)
{
	player_id = id;
	cout << "Введите фамилию футболиста" << endl;
	string surname;
	cin >> surname;
	cin.ignore(32767, '\n');
	m_surname = surname;
	cout << "Введите имя футболиста" << endl;
	string name;
	cin >> name;
	m_name = name;
	cin.ignore(32767, '\n');
	cout << "Введите фамилию футболиста" << endl;
	string patronymic;
	cin >> patronymic;
	cin.ignore(32767, '\n');
	m_patronymic = patronymic;
	date.set_date();
	/*cout << "Укажите позицию футболиста:\n1-вратарь\n2-защитник\n3-полузащитник\n4-нападающий" << endl;
	int position;
	cin >> position;
	switch (position)
	{
	case 1: m_field_position = GOALKEEPER; break;
	case 2: m_field_position = DEFENDER; break;
	case 3: m_field_position = MIDFIELDER; break;
	case 4: m_field_position = FORWARD; break;
	}*/
}

void Date::set_date()
{
	set_year();
	set_month();
	set_day();

}

void Date::set_day()
{
	cout << "Введите день" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_day;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Упс! Что-то пошло не так. ППопробуйте еще раз" << endl;
		}
		if (m_day < 1 || m_day > 31)
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Указан неверный месяц рождения! Попробуйте еще раз" << endl;
		}
		else checker = true;
	}
}

void Date::set_month()
{
	cout << "Введите месяц" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_month;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Упс! Что-то пошло не так. ППопробуйте еще раз" << endl;
		}
		if (m_month < 1 || m_month > 12)
		{
			cout << "Указан неверный месяц рождения! Попробуйте еще раз" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else checker = true;
	}
}

void Date::set_year()
{
	cout << "Введите год" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_year;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Упс! Что-то пошло не так. ППопробуйте еще раз" << endl;
		}
		else if (m_year < 1960 || m_year>2008)
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Указан неверный год рождения! Попробуйте еще раз" << endl;
		}
		else checker = true;
	}
}

/*void Player::set_player_data()
{
	cout << "Введите игровой номер футболиста" << endl;
	int playerNumber;
	cin >> playerNumber;
	player_data.set_data();
	date_of_birth.set_date();
	player_stats.set_start_stats();
}*/

void playersWork()
{
	vector<IdentityData> players_data;
	vector<Statistics> players_stats;
	int number_of_players = readAmount(PLAYERS_NUM);
	Administrator admin;
	if (!players_data.empty())
	{
		read_players_data(players_data);
		read_stats_data(players_stats);
	}
	//else
	//{
		//cout << "Данные не добавлены! Желаете добавить?" << endl;
		//system("pause");
		//players_data = new IdentityData;
		//players_stats = new Statistics;
		//addfirst(players_data, players_stats);
		//number_of_players++;
	//}
	while (1)
	{
		switch (players_work_menu())
		{
		case 1: admin.addPlayer(players_data, players_stats, number_of_players); break;
		case 0:
			write_players_data(players_data, number_of_players);
			write_stats_data(players_stats, number_of_players);
			writeAmount(number_of_players, PLAYERS_NUM);
			return; break;
		}
	}
}

void read_players_data(vector<IdentityData>& vec_of_players)
{
	int number_of_players = readAmount(PLAYERS_NUM);
	ifstream fdata;
	fdata.open("playersData.txt");
	for (int i = 0; i < number_of_players; i++)
	{
		IdentityData temp;
		fdata >> temp.player_id;
			/*>>
			>> array_of_players[i].m_name
			>> array_of_players[i].m_patronymic
			>> array_of_players[i].date.m_day
			>> array_of_players[i].date.m_month
			>> array_of_players[i].date.m_year;*/

	}
	fdata.close();
}

void read_stats_data(vector<Statistics>& vec_of_players)
{
	int number_of_players = readAmount(PLAYERS_NUM);
	ifstream fstats("playersStats.txt");
	for (int i = 0; i < number_of_players; i++)
	{
		Statistics temp;
		fstats >> temp.player_id
			>> array_of_players[i].m_match_played_quantity
			>> array_of_players[i].m_goals_quantity
			>> array_of_players[i].m_assists_quantity
			>> array_of_players[i].m_red_cards_quantity
			>> array_of_players[i].m_yellow_cards_quantity;
	}
	fstats.close();
}

void write_players_data(vector<IdentityData>& vec_of_players, const int number_of_players)
{
	ofstream fdata(PLAYERS_DATA);
	for (int i = 0; i < number_of_players; i++)
	{
		fdata << array_of_players[i].player_id << endl
			<< array_of_players[i].m_surname << endl
			<< array_of_players[i].m_name << endl
			<< array_of_players[i].m_patronymic << endl
			<< array_of_players[i].date.m_day << endl
			<< array_of_players[i].date.m_month << endl
			<< array_of_players[i].date.m_year << endl;
	}
	fdata.close();
}

void write_stats_data(vector<Statistics>& array_of_players, const int number_of_players)
{
	ofstream fstats("playersStats.txt");
	for (int i = 0; i < number_of_players; i++)
	{
		fstats << array_of_players[i].player_id << endl
			<< array_of_players[i].m_match_played_quantity << endl
			<< array_of_players[i].m_goals_quantity << endl
			<< array_of_players[i].m_assists_quantity << endl
			<< array_of_players[i].m_red_cards_quantity << endl
			<< array_of_players[i].m_yellow_cards_quantity << endl;
	}
}


void addfirst(IdentityData* i, Statistics* j)
{
	IdentityData temp_data;
	Statistics temp_stats;
	cout << "Введите игровой номер футболиста" << endl;
	int id;
	cin >> id;
	temp_data.set_data(id);
	temp_stats.set_start_stats(id);

	i[0] = temp_data;
	j[0] = temp_stats;

}