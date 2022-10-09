#pragma once
#pragma once
#include<iostream>
#include<vector>
using namespace std;
enum Position
{
	GOALKEEPER,
	DEFENDER,
	MIDFIELDER,
	FORWARD
};
class Statistics
{
	int player_id;
	int m_match_played_quantity;
	int m_goals_quantity;
	int m_assists_quantity;
	int m_red_cards_quantity;
	int m_yellow_cards_quantity;

public:
	void set_start_stats(int id);
	friend void playersWork();
	friend void read_stats_data(Statistics* array_of_players);
	friend void write_stats_data(Statistics* array_of_players, const int number_of_players);
};

class Date
{
public:
	int m_year;
	int m_month;
	int m_day;
public:
	void set_date();
	void set_year();
	void set_month();
	void set_day();
	friend void playersWork();
	friend class IdentityData;
};

class IdentityData
{
	int player_id;
	string m_surname;
	string m_name;
	string m_patronymic;
	Date date;                      // установить значение можно через геттеры
public:
	void set_data(int id);
	friend void playersWork();
	friend void read_players_data(IdentityData* array_of_players);
	friend void write_players_data(IdentityData* array_of_players, const int number_of_players);
};

class Player
{
	int id;
	Statistics player_stats;
	IdentityData player_data;
	Date date_of_birth;

public:
	void set_player_data();
};


const int MAX_NUMBER_OF_PLAYERS = 25;
const string PLAYERS_NUM = "playersNum.txt";
const string PLAYERS_DATA = "playersData.txt";