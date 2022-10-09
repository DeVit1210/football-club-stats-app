#pragma once
#include<vector>
#include"Player.h"
using namespace std;
const string GAMES_DATA = "gamesData.txt";
const string GAMES_NUM = "gamesNum.txt";
enum result
{
	LOSE,
	DRAW,
	WIN
};

const int PLAYERS_AMOUNT = 4;
class Game
{
	Date m_date_of_game;
	string m_opponent_name;
	int m_squad_players_id[PLAYERS_AMOUNT];
	int m_scored_goals_quantity;
	int m_conceded_goals_quantity;
	int m_yellow_cards_quantity;
	int m_red_cards_quantity;
	result m_match_result;
public:
	void set_opp_name();
	void set_squad(vector<IdentityData>& vec_of_players, vector<Statistics>& vec_of_players_stats);
	bool is_already_in_the_squad(int id, int num_of_players);
	void set_scored_quantity();
	void set_conceded_quantity();
	void set_yellow_cards_quantity();
	void set_red_cards_quantity();
	void add_played_matches_in_stats(vector<Statistics>& vec_of_players);
	void add_goals_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vector_of_players_data);
	void add_assist_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vector_of_players_data, int);
	void add_cards_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vector_of_players_data);
	void add_yellow_cards_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vector_of_players_data);
	int get_day() const { return m_date_of_game.m_day; }
	int get_month() const { return m_date_of_game.m_month; }
	int get_year() const { return m_date_of_game.m_year; }
	string get_opp_name() const { return m_opponent_name; }
	int get_scored() const { return m_scored_goals_quantity; }
	int get_conceded() const { return m_conceded_goals_quantity; }
	int get_yellow_cards_quantity() const { return m_yellow_cards_quantity; }
	int get_red_cards_quantity() const { return m_red_cards_quantity; }
	friend void read_game_data(vector<Game>& vec_of_games);
	friend void write_game_data(vector<Game>& vec_of_games);
	bool check_for_two_red_cards(int, int*);
	bool check_for_three_yellow_cards(int, int*);
	void set_game_data(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vector_of_players_data);
	void show_match_squad(vector<IdentityData>& vector_of_players_data);
	void show_squad(vector<IdentityData>& vector_of_players_data);
};



int check_id(vector<Statistics>& vector_of_players_stats, int& counter);
int check_unique_number(vector<IdentityData>&);


