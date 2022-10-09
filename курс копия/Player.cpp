#include<iostream>
#include<fstream>
#include"Authorization.h"
#include"Player.h"
#include"Game.h"
#include<vector>
#include<ctype.h>
#include<algorithm>
#include<iomanip>
#pragma warning(disable:4996)
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

void Statistics::set_played_matches_quantity()
{
	cout << WARNING;
	if (chooseNextStep())
	{
		system("cls");
		cout << "\n  Введите новое количество сыгранных матчей: ";
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
				cout << "\n  Нельзя сыграть отрицательное число матчей!\n  Попробуйте еще раз: ";
			else if (m_match_played_quantity > 50)
			{
				cout << "\n  Вы уверены, что игрок провел " << m_match_played_quantity << " матчей?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n  Попробуйте еще раз: " << endl;
			}
			else checker = true;
		}

		cout << "\n  Данные о количестве проведенных матчей успешно изменены!" << endl;
	}
}

void Statistics::set_assists_quuantity()
{
	cout << WARNING;
	if (chooseNextStep())
	{
		system("cls");
		cout << "\n  Введите новое количество отданных ассистов: ";
		bool checker(false);
		while (!checker)
		{
			cin >> m_assists_quantity;
			cin.ignore(32767, '\n');
			if (cin.fail())
			{
				cin.clear();
				cout << "  " << INPUT_ERROR << endl;
			}
			else if (m_assists_quantity < 0)
				cout << "Нельзя отдать отрицательное количество ассистов! Попробуйте еще раз:";
			else if (m_assists_quantity > 20)
			{
				cout << "Вы уверены, что игрок отдал " << m_assists_quantity << " ассистов?" << endl;
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n  Попробуйте еще раз!" << endl;
			}
			else checker = true;
		}

		cout << "\n  Данные о количестве отданных ассистов успешно изменены!" << endl;
	}
}

void Statistics::set_goals_quantity()
{
	cout << WARNING;
	if (chooseNextStep())
	{
		system("cls");
		cout << "\n  Введите новое количество забитых голов: ";
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
				cout << "\n  Нельзя забить отрицательное число голов!\n  Попробуйте еще раз: ";
			else if (m_goals_quantity > 50)
			{
				cout << "\n  Вы уверены, что игрок забил " << m_match_played_quantity << " голов?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n  Попробуйте еще раз: ";
			}
			else checker = true;
		}

		cout << "\n  Данные о количестве забитых голов успешно изменены!" << endl;
	}
}

void Statistics::set_red_cards_quantity()
{
	cout << WARNING;
	if (chooseNextStep())
	{
		system("cls");
		cout << "\n  Введите новое количество красных карточек: ";
		bool checker(false);
		while (!checker)
		{
			cin >> m_red_cards_quantity;
			cin.ignore(32767, '\n');
			if (cin.fail())
			{
				cin.clear();
				cout << "  " << INPUT_ERROR << endl;
			}
			else if (m_red_cards_quantity < 0)
				cout << "\n  Нельзя получить отрицательное количество красных карточек!\n  Попробуйте еще раз:";
			else if (m_red_cards_quantity > 5)
			{
				cout << "\n  Вы уверены, что игрок получил " << m_red_cards_quantity << " красных карточек?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n  Попробуйте еще раз: ";
			}
			else checker = true;
		}

		cout << "\n  Данные о количестве красных карточек успешно изменены!" << endl;
	}
}

void Statistics::set_yellow_cards_quantity()
{
	cout << WARNING;
	if (chooseNextStep())
	{
		system("cls");
		cout << "\n  Введите новое количество желтых карточек^ ";
		bool checker(false);
		while (!checker)
		{
			cin >> m_yellow_cards_quantity;
			cin.ignore(32767, '\n');
			if (cin.fail())
			{
				cin.clear();
				cout << "  " << INPUT_ERROR << endl;
			}
			else if (m_yellow_cards_quantity < 0)
				cout << "\n  Нельзя забить отрицательное число голов!\n  Попробуйте еще раз: ";
			else if (m_yellow_cards_quantity > 5)
			{
				cout << "\n  Вы уверены, что игрок получил " << m_yellow_cards_quantity << " желтых карточек?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n  Попробуйте еще раз: ";
			}
			else checker = true;
		}

		cout << "\n  Данные о количестве желтых карточек успешно изменены!" << endl;
	}
}

void IdentityData::set_data(int id)
{
	player_id = id;
	cout << "\n  Введите фамилию футболиста: ";
	set_surname();
	cout << "\n  Введите имя футболиста: ";
	set_name();
	cout << "\n  Введите отчество футболиста: ";
	set_patronymic();
	date.set_date();
}

void Date::set_date()
{
	set_year();
	set_month();
	set_day();
}

void Date::set_day()
{
	cout << "\n  Введите день рождения футболиста: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_day;
		if (cin.fail())
		{
			clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
		}
		else if ((m_month == APRIL) || (m_month == JUNE) || (m_month == SEPTEMBER) || (m_month == NOVEMBER))
		{
			if (m_day < LEFT_RANGE_FOR_DAYS || m_day>RIGHT_RANGE_30)
			{
				clear_bufer();
				cout << "\n  Введено неправильное значение!\n  В " << get_month_name(m_month) << " всего 30 дней!\n\n  Попробуйте еще раз:";
			}
			else checker = true;
		}
		else if ((m_month == FEBRUARY && m_day < LEFT_RANGE_FOR_DAYS) || (m_month == FEBRUARY && m_day > RIGHT_RANGE_FEBRUARY))
		{
			clear_bufer();
			cout << "\n  Введено неправильное значение!\n  В феврале всего 28 дней!\n\n  Попробуйте еще раз: ";
		}
		else if ((m_month == JANUARY) || (m_month == MARCH) || (m_month == MAY) || (m_month == JULY) || (m_month == AUGUST) || (m_month == OCTOBER) || (m_month == DECEMBER))
		{
			if (m_day < LEFT_RANGE_FOR_DAYS || m_day> RIGHT_RANGE_31)
			{
				clear_bufer();
				cout << "\n  Введено неправильное значение!\n  В " << get_month_name(m_month) << " всего 31 день!\n\n  Попробуйте еще раз: ";
			}
			else checker = true;
		}
		else
		{
			cin.ignore(32767, '\n');
			checker = true;
		}
	}
}

void Date::set_month()
{
	cout << "\n  Введите месяц рождения футболиста: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_month;
		if (cin.fail())
		{
			clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
		}
		if (m_month < LEFT_RANGE_FOR_MONTHS || m_month > RIGHT_RANGE_FOR_MONTHS)
		{
			clear_bufer();
			cout << "\n  Указан неверный месяц рождения!\n  Попробуйте еще раз:";
		}
		else
		{
			cin.ignore(32767, '\n');
			checker = true;
		}
	}
}

void Date::set_year()
{
	cout << "\n  Введите год рождения футболиста: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_year;
		if (cin.fail())
		{
			clear_bufer();
			cout << "  " << INPUT_ERROR << endl;
		}
		else if (m_year < LEFT_RANGE_FOR_AGE || m_year>RIGHT_RANGE_FOR_AGE)
		{
			clear_bufer();
			cout << "\n   Указан неверный год рождения!\n  Попробуйте еще раз: ";
		}
		else
		{
			cin.ignore(32767, '\n');
			checker = true;
		}
	}
}

void IdentityData::set_surname()
{
	bool checker(false);
	while (!checker)
	{
		getline(cin, m_surname, '\n');
		int result_of_checking = check_string_for_wrong_symbols(m_surname);
		if (result_of_checking == DIGIT_ERROR)
			cout << "\n  Строка не должна содержать цифры!\n  Попробуйте еще раз:";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "\n  Строка должна содержать только буквы или тире!\n  Попробуйте еще раз:";
		else checker = true;
	}
}

void IdentityData::set_name()
{
	bool checker(false);
	while (!checker)
	{
		getline(cin, m_name, '\n');
		int result_of_checking = check_string_for_wrong_symbols(m_name);
		if (result_of_checking == DIGIT_ERROR)
			cout << "\n  Строка не должна содержать цифры!\n  Попробуйте еще раз: ";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "\n  Строка должна содержать только буквы или тире!\n  Попробуйте еще раз: ";
		else checker = true;
	}
}

void IdentityData::set_patronymic()
{
	bool checker(false);
	while (!checker)
	{
		getline(cin, m_patronymic, '\n');
		int result_of_checking = check_string_for_wrong_symbols(m_patronymic);
		if (result_of_checking == DIGIT_ERROR)
			cout << "  Строка не должна содержать цифры!\n  Попробуйте еще раз: ";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "  Строка должна содержать только буквы или тире!\n  Попробуйте еще раз: ";
		else checker = true;
	}
}

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
		case 7: admin.sortStats(players_data, players_stats); break;
		case 8: admin.show_the_most_productive(players_data, players_stats); break;
		case 10: admin.findStats(players_data, players_stats); break;
		case 9: admin.showRedCardsStats(players_data, players_stats); break;
		case 0:
			write_players_data(players_data, players_data.size());
			write_stats_data(players_stats, players_data.size());
			write_game_data(games_data);
			writeAmount(players_data.size(), PLAYERS_NUM);
			return; break;
		default: cout << "  " << INPUT_ERROR;
			clear_bufer();
		}
		push_and_clear_page();
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
		fgames >> temp.m_opponent_name;
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
		fgames << vec_of_games.at(i).m_opponent_name << endl;
		for (int counter = 0; counter < PLAYERS_AMOUNT; counter++)
			fgames << vec_of_games.at(i).m_squad_players_id[counter] << endl;
		fgames << vec_of_games.at(i).m_scored_goals_quantity << endl
			<< vec_of_games.at(i).m_conceded_goals_quantity << endl
			<< vec_of_games.at(i).m_yellow_cards_quantity << endl
			<< vec_of_games.at(i).m_red_cards_quantity << endl;
	}
	writeAmount(vec_of_games.size(), GAMES_NUM);
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
	char symbols[] = { "/?.,!@#$%^&*()*+][]}{|_" };
	char* temp_str = new char[string.length() + 1];
	strcpy(temp_str, string.c_str());

	for (int i = 0; i < strlen(temp_str); i++)
		for (int j = 0; j < strlen(digits); j++)
			if (temp_str[i] == digits[j])
				return DIGIT_ERROR;

	for (int i = 0; i < strlen(temp_str); i++)
		for (int j = 0; j < strlen(symbols); j++)
			if (temp_str[i] == symbols[j])
				return WRONG_SYMBOL_ERROR;


	return SUCCESS;
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
	cout << "\n  Введите новую фамилию: ";
	set_surname();
	cout << "\n  Фамилия изменена успешно!" << endl;
}

void IdentityData::change_name()
{
	cout << "\n  Введите новое имя: ";
	set_name();
	cout << "\n  Имя изменено успешно!" << endl;
}

void IdentityData::change_patronymic()
{
	cout << "\n  Введите новое отчество: ";
	set_patronymic();
	cout << "\n  Отчество успешно изменено!" << endl;
}

void IdentityData::change_date()
{
	cout << "\n  Введите новую дату рождения футболиста" << endl << endl;
	date.set_date();
	cout << "\n  Дата рождения успешно изменена!" << endl;
}


void sort_by_goals_quantity(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	for (int iterations = 0; iterations < vec_of_players_data.size(); iterations++)
	{
		for (int i = 0; i < vec_of_players_data.size() - 1; i++)
		{
			if (vec_of_players_stats.at(i).get_goals_quantity() < vec_of_players_stats.at(i + 1).get_goals_quantity())
			{
				swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + 1));
				swap(vec_of_players_data.at(i), vec_of_players_data.at(i + 1));
			}
		}
	}
}

void sort_by_surname(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	for (int iterations = 0; iterations < vec_of_players_data.size(); iterations++)
	{
		for (int i = 0; i < vec_of_players_data.size() - 1; i++)
		{
			if (vec_of_players_data.at(i).get_surname() > vec_of_players_data.at(i + 1).get_surname())
			{
				swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + 1));
				swap(vec_of_players_data.at(i), vec_of_players_data.at(i + 1));
			}
		}
	}
}

void sort_by_goals_and_assists(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	int* goals_and_assists = new int[vec_of_players_data.size()];
	for (int i = 0; i < vec_of_players_data.size(); i++)
	{
		goals_and_assists[i] = vec_of_players_stats.at(i).get_goals_quantity() + vec_of_players_stats.at(i).get_assists_quantity();
	}
	for (int iterations = 0; iterations < vec_of_players_data.size(); iterations++)
	{
		for (int i = 0; i < vec_of_players_data.size() - 1; i++)
		{
			if (goals_and_assists[i] < goals_and_assists[i + 1])
			{
				swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + 1));
				swap(vec_of_players_data.at(i), vec_of_players_data.at(i + 1));
				swap(goals_and_assists[i], goals_and_assists[i + 1]);
			}
		}
	}
}

void show_certain_stats(IdentityData& player_data, Statistics& player_stats)
{
	cout << "|" << setw(7) << player_data.get_id()
		<< "|" << setw(15) << player_data.get_surname()
		<< "|" << setw(15) << player_data.get_name()
		<< "|" << setw(16) << player_data.get_patronymic()
		<< "|" << setw(5) << player_data.get_day()
		<< "/" << player_data.get_month()
		<< "/" << player_data.get_year();
	cout << "|" << setw(9) << player_stats.get_played_matches_quantity()
		<< "|" << setw(6) << player_stats.get_goals_quantity()
		<< "|" << setw(6) << player_stats.get_assists_quantity()
		<< "|" << setw(9) << player_stats.get_red_cards_quantity()
		<< "|" << setw(8) << player_stats.get_yellow_cards_quantity() << "|" << endl;
	cout << "==================================================================================================================" << endl;
}


