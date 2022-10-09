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

const string WARNING = "  Изменение данных в этом поле просходит через добавление результатов игры! Вы точно хотите продолжить?";
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
	friend void read_stats_data(vector<Statistics>& vec_of_players);
	friend void write_stats_data(vector<Statistics>& vec_of_players, const int number_of_players);
	void set_played_matches_quantity();
	void set_goals_quantity();
	void set_assists_quuantity();
	void set_red_cards_quantity();
	void set_yellow_cards_quantity();
	int get_id() const { return player_id; }
	int get_played_matches_quantity() const { return m_match_played_quantity; }
	int get_goals_quantity() const { return m_goals_quantity; }
	int get_assists_quantity() const { return m_assists_quantity;  }
	int get_red_cards_quantity() const { return m_red_cards_quantity; }
	int get_yellow_cards_quantity() const { return m_yellow_cards_quantity; }
	void add_played_matches_quantity() { m_match_played_quantity++;  }
	void add_yellow_card_in_stats() { m_yellow_cards_quantity++; }
	void add_red_card_in_stats() { m_red_cards_quantity++; }
	void add_goals_quantity() { m_goals_quantity++; }
	void add_assists_quantity() { m_assists_quantity++;  }

	void change_id(int id) { player_id = id; }
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
	int get_day() const { return m_day; }
	int get_month() const { return m_month; }
	int get_year() const { return m_year;  }
	friend void playersWork();
	friend class IdentityData;
};

class IdentityData
{
	int player_id;
	string m_surname;
	string m_name;
	string m_patronymic;
	Date date;                      
public:
	void set_data(int id);
	friend void playersWork();
	friend void read_players_data(vector<IdentityData>& vec_of_players);
	friend void write_players_data(vector<IdentityData>& vec_of_players, const int number_of_players);
	int get_id() const { return player_id; };
	void set_surname();
	void set_name();
	void set_patronymic();
	string get_surname() const  { return m_surname; }
	string get_name() const { return m_name; }
	string get_patronymic() const  { return m_patronymic; }
	int get_day() const { return date.m_day;  }
	int get_month() const { return date.m_month; }
	int get_year() const { return date.m_year; }

	void change_id(int id) { player_id = id; }
	void change_surname();
	void change_name();
	void change_patronymic();
	void change_date();
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

void read_players_data(vector<IdentityData>& vec_of_players);

const int MAX_NUMBER_OF_PLAYERS = 25;
const string PLAYERS_NUM = "playersNum.txt";
const string PLAYERS_DATA = "playersData.txt";
const string PLAYERS_STATS = "playersStats.txt";

string get_month_name(int month);
int check_string_for_wrong_symbols(string string);

int find_same_id(const int id, vector<IdentityData>& vec_of_players);
int find_same_id(const int id, vector<Statistics>& vec_of_players);