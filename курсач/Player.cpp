#include<iostream>
#include<fstream>
#include"Authorization.h"
#include"Player.h"
#include"Game.h"
#include<vector>
#include<ctype.h>
#include<algorithm>
#pragma warning(disable:4996)
using namespace std;
enum errors
{
	NO_PLAYER_WITH_SUCH_NUMBER_ERROR,
	DIGIT_ERROR,
	WRONG_SYMBOL_ERROR,
	NO_ERROR
};

void clear_bufer()
{
	cin.clear();
	cin.ignore(32767, '\n');
}
void Statistics::set_start_stats(int id)
{
	player_id = id;
	m_match_played_quantity = 0;
	m_goals_quantity = 0;
	m_assists_quantity = 0;
	m_red_cards_quantity = 0;
	m_yellow_cards_quantity = 0;
}

void Statistics::set_played_matches_quantity()
{
	cout << WARNING << endl;
	if (chooseNextStep())
	{
		system("cls");
		cout << "Введите новое количество сыгранных матчей" << endl;
		bool checker(false);
		while (!checker)
		{
			cin >> m_match_played_quantity;
			cin.ignore(32767, '\n');
			if (cin.fail())
			{
				cin.clear();
				cout << INPUT_ERROR << endl;
			}
			else if (m_match_played_quantity < 0)
				cout << "Нельзя сыграть отрицательное число матчей! Попробуйте еще раз!" << endl;
			else if (m_match_played_quantity > 50)
			{
				cout << "Вы уверены, что игрок провел аж " << m_match_played_quantity << " матчей?" << endl;
				if (chooseNextStep())
					checker = true;
				else cout << "Будьте внимательнее при вводе данных!\nПопробуйте еще раз!" << endl;
			}
			else checker = true;
		}

		cout << "Данные о количестве проведенных матчей успешно изменены!" << endl;
	}
}

void Statistics::set_assists_quuantity()
{
	cout << WARNING << endl;
	if (chooseNextStep())
	{
		system("cls");
		cout << "Введите новое количество отданных ассистов" << endl;
		bool checker(false);
		while (!checker)
		{
			cin >> m_assists_quantity;
			cin.ignore(32767, '\n');
			if (cin.fail())
			{
				cin.clear();
				cout << INPUT_ERROR << endl;
			}
			else if (m_assists_quantity < 0)
				cout << "Нельзя отдать отрицательное количество ассистов! Попробуйте еще раз!" << endl;
			else if (m_assists_quantity > 20)
			{
				cout << "Вы уверены, что игрок отдал аж " << m_assists_quantity << " ассистов?" << endl;
				if (chooseNextStep())
					checker = true;
				else cout << "Будьте внимательнее при вводе данных!\nПопробуйте еще раз!" << endl;
			}
			else checker = true;
		}

		cout << "Данные о количестве отданных ассистов успешно изменены!" << endl;
	}
}

void Statistics::set_goals_quantity()
{
	cout << WARNING << endl;
	if (chooseNextStep())
	{
		system("cls");
		cout << "Введите новое количество забитых голов" << endl;
		bool checker(false);
		while (!checker)
		{
			cin >> m_goals_quantity;
			cin.ignore(32767, '\n');
			if (cin.fail())
			{
				cin.clear();
				cout << INPUT_ERROR << endl;
			}
			else if (m_goals_quantity < 0)
				cout << "Нельзя забить отрицательное число голов! Попробуйте еще раз!" << endl;
			else if (m_goals_quantity > 50)
			{
				cout << "Вы уверены, что игрок забил аж " << m_match_played_quantity << " голов?" << endl;
				if (chooseNextStep())
					checker = true;
				else cout << "Будьте внимательнее при вводе данных!\nПопробуйте еще раз!" << endl;
			}
			else checker = true;
		}

		cout << "Данные о количестве забитых голов успешно изменены!" << endl;
	}
}

void Statistics::set_red_cards_quantity()
{
	cout << WARNING << endl;
	if (chooseNextStep())
	{
		system("cls");
		cout << "Введите новое количество красных карточек" << endl;
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
				cout << "Нельзя получить отрицательное количество красных карточек! Попробуйте еще раз!" << endl;
			else if (m_red_cards_quantity > 5)
			{
				cout << "Вы уверены, что игрок получил аж " << m_red_cards_quantity << " красных карточек?" << endl;
				if (chooseNextStep())
					checker = true;
				else cout << "Будьте внимательнее при вводе данных!\nПопробуйте еще раз!" << endl;
			}
			else checker = true;
		}

		cout << "Данные о количестве красных карточек успешно изменены!" << endl;
	}
}

void Statistics::set_yellow_cards_quantity()
{
	cout << WARNING << endl;
	if (chooseNextStep())
	{
		system("cls");
		cout << "Введите новое количество желтых карточек" << endl;
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
				cout << "Нельзя забить отрицательное число голов! Попробуйте еще раз!" << endl;
			else if (m_yellow_cards_quantity > 5)
			{
				cout << "Вы уверены, что игрок получил аж " << m_yellow_cards_quantity << " желтых карточек?" << endl;
				if (chooseNextStep())
					checker = true;
				else cout << "Будьте внимательнее при вводе данных!\nПопробуйте еще раз!" << endl;
			}
			else checker = true;
		}

		cout << "Данные о количестве желтых карточек успешно изменены!" << endl;
	}
}

void IdentityData::set_data(int id)
{
	player_id = id;
	cout << "Введите фамилию футболиста" << endl;
	set_surname();
	cout << "Введите имя футболиста" << endl;
	set_name();
	cout << "Введите отчество футболиста" << endl;
	set_patronymic();
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
	cout << "Введите день рождения футболиста: " << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_day;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Упс! Что-то пошло не так. Попробуйте еще раз" << endl;
		}
		else if ((m_month == APRIL) || (m_month==JUNE) || (m_month==SEPTEMBER) || (m_month==NOVEMBER))
		{
			if (m_day < 1 || m_day>30)
			{
				clear_bufer();
				cout << "Введено неправильное значение! В " << get_month_name(m_month) << " всего 30 дней! Попробуйте еще раз" << endl;
			}
			else checker = true;
		}
		else if ((m_month==FEBRUARY && m_day<1) || (m_month == FEBRUARY && m_day > 28))
		{
			clear_bufer();
			cout << "Введено неправильное значение! В феврале всего 28 дней! Попробуйте еще раз" << endl;
		}
		else if ((m_month==JANUARY) || (m_month==MARCH) || (m_month==MAY) || (m_month==JULY) || (m_month==AUGUST) || (m_month==OCTOBER) || (m_month==DECEMBER))
		{
			if (m_day < 1 || m_day>31)
			{
				clear_bufer();
				cout << "Введено неправильное значение! В " << get_month_name(m_month) << " всего 31 день! Попробуйте еще раз" << endl;
			}
			else checker = true;
		}
		else checker = true;
	}
}

void Date::set_month()
{
	cout << "Введите месяц рождения футболиста" << endl;
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
	cout << "Введите год рождения футболиста" << endl;
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

void IdentityData::set_surname()
{
	bool checker(false);
	while (!checker)
	{
		cin >> m_name;
		int result_of_checking = check_string_for_wrong_symbols(m_name);
		if (result_of_checking == DIGIT_ERROR)
			cout << "Строка не должна содержать цифры! Попробуйте еще раз!" << endl;
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "Строка должна содержать только буквы или тире! Попробуйте еще раз!" << endl;
		else checker = true;
	}
}

void IdentityData::set_name()
{
	cout << "Введите новое имя: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_name;
		int result_of_checking = check_string_for_wrong_symbols(m_name);
		if (result_of_checking == DIGIT_ERROR)
			cout << "Строка не должна содержать цифры! Попробуйте еще раз!" << endl;
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "Строка должна содержать только буквы или тире! Попробуйте еще раз!" << endl;
		else checker = true;
	}

	cout << "Имя изменено успешно!" << endl;
}

void IdentityData::set_patronymic()
{
	bool checker(false);
	while (!checker)
	{
		cin >> m_patronymic;
		int result_of_checking = check_string_for_wrong_symbols(m_patronymic);
		if (result_of_checking == DIGIT_ERROR)
			cout << "Строка не должна содержать цифры! Попробуйте еще раз!" << endl;
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "Строка должна содержать только буквы или тире! Попробуйте еще раз!" << endl;
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
	vector<Game> games_data;
	int number_of_players = readAmount(PLAYERS_NUM);
	Administrator admin;
	if (number_of_players)
	{
		read_players_data(players_data);
		read_stats_data(players_stats);
		read_game_data(games_data);
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
		case 2: admin.showStats(players_data, players_stats); break;
		case 3: admin.add_game_data(players_data, players_stats, games_data); break;
		case 4: admin.show_games(games_data); break;
		case 5: admin.deletePlayer(players_data, players_stats); break;
		case 6: admin.editPlayer(players_data, players_stats); break;
		case 0:
			write_players_data(players_data, number_of_players);
			write_stats_data(players_stats, number_of_players);
			write_game_data(games_data);
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
		fdata >> temp.player_id
			>> temp.m_surname
			>> temp.m_name
			>> temp.m_patronymic
			>> temp.date.m_day
			>> temp.date.m_month
			>> temp.date.m_year;

		vec_of_players.push_back(temp);

	}
	fdata.close();
}


void read_game_data(vector<Game>& vec_of_games)
{
	int number_of_games = readAmount(GAMES_NUM);
	ifstream fgames(GAMES_DATA);
	for (int i = 0; i < number_of_games; i++)
	{
		Game temp;
		fgames >> temp.m_date_of_game.m_day
			>> temp.m_date_of_game.m_month
			>> temp.m_date_of_game.m_year
			>> temp.m_opponent_name;
		for (int counter = 0; counter < PLAYERS_AMOUNT; counter++)
			fgames >> temp.m_squad_players_id[counter];

		fgames >> temp.m_scored_goals_quantity
			>> temp.m_conceded_goals_quantity
			>> temp.m_yellow_cards_quantity
			>> temp.m_red_cards_quantity;

		vec_of_games.push_back(temp);
	}
	fgames.close();
}
void read_stats_data(vector<Statistics>& vec_of_players)
{
	int number_of_players = readAmount(PLAYERS_NUM);
	ifstream fstats(PLAYERS_STATS);
	for (int i = 0; i < number_of_players; i++)
	{
		Statistics temp;
		fstats >> temp.player_id
			>> temp.m_match_played_quantity
			>> temp.m_goals_quantity
			>> temp.m_assists_quantity
			>> temp.m_red_cards_quantity
			>> temp.m_yellow_cards_quantity;

		vec_of_players.push_back(temp);
	}
	fstats.close();
}

void write_game_data(vector<Game>& vec_of_games)
{
	ofstream fgames(GAMES_DATA);
	for (int i = 0; i < vec_of_games.size(); i++)
	{
		fgames << vec_of_games.at(i).m_date_of_game.m_day << endl
			<< vec_of_games.at(i).m_date_of_game.m_month << endl
			<< vec_of_games.at(i).m_date_of_game.m_year << endl
			<< vec_of_games.at(i).m_opponent_name << endl;
		for (int counter = 0; counter < PLAYERS_AMOUNT; counter++)
			fgames << vec_of_games.at(i).m_squad_players_id[counter] << endl;
		fgames << vec_of_games.at(i).m_scored_goals_quantity << endl
			<< vec_of_games.at(i).m_conceded_goals_quantity << endl
			<< vec_of_games.at(i).m_yellow_cards_quantity << endl
			<< vec_of_games.at(i).m_red_cards_quantity << endl;
	}

	fgames.close();
}
void write_players_data(vector<IdentityData>& vec_of_players, const int number_of_players)
{
	ofstream fdata(PLAYERS_DATA);
	for (int i = 0; i < vec_of_players.size(); i++)
	{
		fdata << vec_of_players.at(i).player_id << endl
			<< vec_of_players.at(i).m_surname << endl
			<< vec_of_players.at(i).m_name << endl
			<< vec_of_players.at(i).m_patronymic << endl
			<< vec_of_players.at(i).date.m_day << endl
			<< vec_of_players.at(i).date.m_month << endl
			<< vec_of_players.at(i).date.m_year << endl;
	}
	fdata.close();
}

void write_stats_data(vector<Statistics>& vec_of_players, const int number_of_players)
{
	ofstream fstats("playersStats.txt");
	for (int i = 0; i < vec_of_players.size(); i++)
	{
		fstats << vec_of_players.at(i).player_id << endl
			<< vec_of_players.at(i).m_match_played_quantity << endl
			<< vec_of_players.at(i).m_goals_quantity << endl
			<< vec_of_players.at(i).m_assists_quantity << endl
			<< vec_of_players.at(i).m_red_cards_quantity << endl
			<< vec_of_players.at(i).m_yellow_cards_quantity << endl;
	}
}

string get_month_name(int month)
{
	if (month == JANUARY)
		return "январе";
	if (month == FEBRUARY)
		return "феврале";
	if (month == MARCH)
		return "марте";
	if (month == APRIL)
		return "апреле";
	if (month == MAY)
		return "мае";
	if (month == JUNE)
		return "июне";
	if (month == JULY)
		return "июле";
	if (month == AUGUST)
		return "августе";
	if (month == SEPTEMBER)
		return "сентябре";
	if (month == OCTOBER)
		return "октябре";
	if (month == NOVEMBER)
		return "ноябре";
	if (month == DECEMBER)
		return "декабре";

}

int check_string_for_wrong_symbols(string string)
{
	char digits[] = { "0123456789" };
	char symbols[] = { "/?.,!@#$%^&*()*+][]}{|" };
	char* temp_str = new char[string.length() + 1];
	strcpy(temp_str,string.c_str());
	for (int i = 0; i < strlen(temp_str); i++)
	{
		for (int j = 0; j < strlen(digits) ; j++)
		{
			if (temp_str[i] == digits[j])
			{
				clear_bufer();
				return DIGIT_ERROR;
			}
		}
	}
	for (int i = 0; i < strlen(temp_str) ; i++)
	{
		for (int j = 0; j < strlen(symbols) ; j++)
		{
			if (temp_str[i] == symbols[j])
			{
				clear_bufer();
				return WRONG_SYMBOL_ERROR;
			}
		}
	}
	return NO_ERROR;
}

int find_same_id(const int id, vector<IdentityData>& vec_of_players)
{
	for (int i = 0; i < vec_of_players.size(); i++)
		if (vec_of_players.at(i).get_id() == id)
			return i;
}

int find_same_id(const int id, vector<Statistics>& vec_of_players)
{
	for (int i = 0; i < vec_of_players.size(); i++)
		if (vec_of_players.at(i).get_id() == id)
			return i;
}

void IdentityData::change_surname()
{
	cout << " Введите новую фамилию: ";
	set_surname();
	cout << "Фамилия изменена успешно!" << endl;
}

void IdentityData::change_name()
{
	cout << "  Введите новое имя: ";
	set_name();
	cout << "Имя изменено успешно!" << endl;
}

void IdentityData::change_patronymic()
{
	cout << "Введите новое отчество: ";
	set_patronymic();
	cout << "Отчество успешно изменено!" << endl;
}

void IdentityData::change_date()
{
	cout << "  Введите новую дату рождения футболиста" << endl << endl;
	date.set_date();
	cout << "Дата рождения успешно изменена!" << endl;
}

