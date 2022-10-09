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
				cout << "\n  Нельзя сыграть отрицательное число матчей!\n" << TRY_IT_AGAIN;
			else if (m_match_played_quantity > 50)
			{
				cout << "\n  Вы уверены, что игрок провел " << m_match_played_quantity << " матчей?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n" << TRY_IT_AGAIN;
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
				cout << "\n  Нельзя отдать отрицательное количество ассистов!\n" << TRY_IT_AGAIN;
			else if (m_assists_quantity > 20)
			{
				cout << "\n  Вы уверены, что игрок отдал " << m_assists_quantity << " ассистов?" << endl;
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n" << TRY_IT_AGAIN;
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
				cout << "\n  Нельзя забить отрицательное число голов!\n" << TRY_IT_AGAIN;
			else if (m_goals_quantity > 50)
			{
				cout << "\n  Вы уверены, что игрок забил " << m_match_played_quantity << " голов?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n" << TRY_IT_AGAIN;
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
				cout << "\n  Нельзя получить отрицательное количество красных карточек!\n" << TRY_IT_AGAIN;
			else if (m_red_cards_quantity > 5)
			{
				cout << "\n  Вы уверены, что игрок получил " << m_red_cards_quantity << " красных карточек?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n" << TRY_IT_AGAIN;
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
				cout << "\n  Нельзя забить отрицательное число голов!\n" << TRY_IT_AGAIN;
			else if (m_yellow_cards_quantity > 5)
			{
				cout << "\n  Вы уверены, что игрок получил " << m_yellow_cards_quantity << " желтых карточек?(y/n): ";
				if (chooseNextStep())
					checker = true;
				else cout << "\n  Будьте внимательнее при вводе данных!\n" << TRY_IT_AGAIN;
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
				cout << "\n  Введено неправильное значение!\n  В " << get_month_name(m_month) << " всего 30 дней!\n\n  Попробуйте еще раз: ";
			}
			else
			{
				cin.ignore(32767, '\n');
				checker = true;
			}
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
			else
			{
				cin.ignore(32767, '\n');
				checker = true;
			}
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
			cout << "\n  Указан неверный месяц рождения!\n  Попробуйте еще раз: " ;
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
			cout << "\n  Указан неверный год рождения!\n  Попробуйте еще раз: ";
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
		cin >> m_surname;
		int result_of_checking = check_string_for_wrong_symbols(m_surname);
		if (result_of_checking == DIGIT_ERROR)
			cout << "\n  Строка не должна содержать цифры!\n  Попробуйте еще раз:";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "\n  Строка должна содержать только буквы или тире!\n  Попробуйте еще раз:";
		else checker = true;
		cin.ignore(32767, '\n');
	}
}

void IdentityData::set_name()
{
	bool checker(false);
	while (!checker)
	{
		cin >> m_name;
		int result_of_checking = check_string_for_wrong_symbols(m_name);
		if (result_of_checking == DIGIT_ERROR)
			cout << "\n  Строка не должна содержать цифры!\n  Попробуйте еще раз: ";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "\n  Строка должна содержать только буквы или тире!\n  Попробуйте еще раз: ";
		else checker = true;
		cin.ignore(32767, '\n');
	}

}

void IdentityData::set_patronymic()
{
	bool checker(false);
	while (!checker)
	{
		cin >> m_patronymic;
		int result_of_checking = check_string_for_wrong_symbols(m_patronymic);
		if (result_of_checking == DIGIT_ERROR)
			cout << "  Строка не должна содержать цифры!\n  Попробуйте еще раз: ";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "  Строка должна содержать только буквы или тире!\n  Попробуйте еще раз: ";
		else checker = true;
		cin.ignore(32767, '\n');
	}
}

void Administrator::playersWork()
{
	vector<IdentityData> players_data;
	vector<Statistics> players_stats;
	vector<Game> games_data;
	int number_of_players = readAmount(PLAYERS_NUM);
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
		case 1: addPlayer(players_data, players_stats, number_of_players); break;
		case 2: showStats(players_data, players_stats); break;
		case 3: add_game_data(players_data, players_stats, games_data); break;
		case 4: show_games(games_data); break;
		case 5: deletePlayer(players_data, players_stats); break;
		case 6: editPlayer(players_data, players_stats); break;
		case 7: sortStats(players_data, players_stats); break;
		case 8: show_the_most_productive(players_data, players_stats); break;
		case 10: findStats(players_data, players_stats); break;
		case 9: showRedCardsStats(players_data, players_stats); break;
		case 11:
			write_players_data(players_data);
			write_stats_data(players_stats);
			write_game_data(games_data);
			writeAmount(players_data.size(), PLAYERS_NUM);
			system("cls");
			return; break;
		default: cout << "  " << INPUT_ERROR;
			clear_bufer();
		}
		push_and_clear_page();
	}
}

istream& operator>>(istream& fdata, IdentityData& obj)
{
	fdata >> obj.player_id
		>> obj.m_surname
		>> obj.m_name
		>> obj.m_patronymic
		>> obj.date.m_day
		>> obj.date.m_month
		>> obj.date.m_year;

	return fdata;
}

void read_players_data(vector<IdentityData>& vec_of_players)
{
	int number_of_players = readAmount(PLAYERS_NUM);
	ifstream fdata;
	fdata.open("playersData.txt");
	for(int i=0; i<number_of_players; i++)
	{
		IdentityData temp;
		fdata >> temp;
		vec_of_players.push_back(temp);
	}
	fdata.close();
}

ostream& operator<<(ostream& fdata, const IdentityData& obj)
{
	fdata << obj.player_id << endl
		<< obj.m_surname << endl
		<< obj.m_name << endl
		<< obj.m_patronymic << endl
		<< obj.date.m_day << endl
		<< obj.date.m_month << endl
		<< obj.date.m_year << endl;

	return fdata;
}

void write_players_data(vector<IdentityData>& vec_of_players)
{
	ofstream fdata(PLAYERS_DATA);
	for (size_t i = 0; i < vec_of_players.size(); i++)
		fdata << vec_of_players.at(i);
	fdata.close();
}

istream& operator>>(istream& fstats, Statistics& obj)
{
	fstats >> obj.player_id
		>> obj.m_match_played_quantity
		>> obj.m_goals_quantity
		>> obj.m_assists_quantity
		>> obj.m_red_cards_quantity
		>> obj.m_yellow_cards_quantity;

	return fstats;
}

void read_stats_data(vector<Statistics>& vec_of_players)
{
	int number_of_players = readAmount(PLAYERS_NUM);
	ifstream fstats(PLAYERS_STATS);
	for(int i=0; i<number_of_players; i++)
	{
		Statistics temp;
		fstats >> temp;
		vec_of_players.push_back(temp);
	}
	fstats.close();
}

ostream& operator<<(ostream& fstats, const Statistics& obj)
{
	fstats << obj.player_id << endl
		<< obj.m_match_played_quantity << endl
		<< obj.m_goals_quantity << endl
		<< obj.m_assists_quantity << endl
		<< obj.m_red_cards_quantity << endl
		<< obj.m_yellow_cards_quantity << endl;

	return fstats;
}

void write_stats_data(vector<Statistics>& vec_of_players)
{
	ofstream fstats(PLAYERS_STATS);
	for (size_t i = 0; i < vec_of_players.size(); i++)
		fstats << vec_of_players.at(i);
	fstats.close();
}

istream& operator>>(istream& fgames, Game& obj)
{
	fgames >> obj.m_opponent_name;
	for (int counter = 0; counter < PLAYERS_AMOUNT; counter++)
		fgames >> obj.m_squad_players_id[counter];

	fgames >> obj.m_scored_goals_quantity
		>> obj.m_conceded_goals_quantity
		>> obj.m_yellow_cards_quantity
		>> obj.m_red_cards_quantity;

	return fgames;
}

void read_game_data(vector<Game>& vec_of_games)
{
	int number_of_games = readAmount(GAMES_NUM);
	ifstream fgames(GAMES_DATA);
	for (int i = 0; i < number_of_games; i++)
	{
		Game temp;
		fgames >> temp;
		vec_of_games.push_back(temp);
	}
	fgames.close();
}

ostream& operator<<(ostream& fgames, const Game& obj)
{
	fgames << obj.m_opponent_name << endl;
	for (int counter = 0; counter < PLAYERS_AMOUNT; counter++)
		fgames << obj.m_squad_players_id[counter] << endl;
	fgames << obj.m_scored_goals_quantity << endl
		<< obj.m_conceded_goals_quantity << endl
		<< obj.m_yellow_cards_quantity << endl
		<< obj.m_red_cards_quantity << endl;

	return fgames;
}
void write_game_data(vector<Game>& vec_of_games)
{
	ofstream fgames(GAMES_DATA);
	for (size_t i = 0; i < vec_of_games.size(); i++)
		fgames << vec_of_games.at(i);
	writeAmount(vec_of_games.size(), GAMES_NUM);
	fgames.close();
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

	for (size_t i = 0; i < strlen(temp_str); i++)
		for (size_t j = 0; j < strlen(digits); j++)
			if (temp_str[i] == digits[j])
				return DIGIT_ERROR;

	for (size_t i = 0; i < strlen(temp_str); i++)
		for (size_t j = 0; j < strlen(symbols); j++)
			if (temp_str[i] == symbols[j])
				return WRONG_SYMBOL_ERROR;


	return SUCCESS;
}

int find_same_id(const int id, vector<IdentityData>& vec_of_players)
{
	for (size_t i = 0; i < vec_of_players.size(); i++)
		if (vec_of_players.at(i).get_id() == id)
			return i;
}

int find_same_id(const int id, vector<Statistics>& vec_of_players)
{
	for (size_t i = 0; i < vec_of_players.size(); i++)
		if (vec_of_players.at(i).get_id() == id)
			return i;
}

void IdentityData::change_surname()
{
	system("cls");
	cout << "\n  Введите новую фамилию: ";
	set_surname();
	cout << "\n  Фамилия изменена успешно!" << endl;
}

void IdentityData::change_name()
{
	system("cls");
	cout << "\n  Введите новое имя: ";
	set_name();
	cout << "\n  Имя изменено успешно!" << endl;
}

void IdentityData::change_patronymic()
{
	system("cls");
	cout << "\n  Введите новое отчество: ";
	set_patronymic();
	cout << "\n  Отчество успешно изменено!" << endl;
}

void IdentityData::change_date()
{
	system("cls");
	cout << "\n  Введите новую дату рождения футболиста" << endl << endl;
	date.set_date();
	cout << "\n  Дата рождения успешно изменена!" << endl;
}


void sort_by_goals_quantity(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	size_t i, j;
	int gap;
	int flag;
	for (gap = vec_of_players_data.size() / 2; gap > 0; gap /= 2)
	{
		do
		{
			flag = 0;
			for (i = 0, j = gap; j < vec_of_players_data.size(); i++, j++)
			{
				if (vec_of_players_stats.at(i).get_goals_quantity() < vec_of_players_stats.at(i + gap).get_goals_quantity())
				{
					swap(vec_of_players_data.at(i), vec_of_players_data.at(i+gap));
					swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + gap));
					flag = 1;
				}
			}
		} while (flag);
	}
	cout << "\n  Статистика игроков успешно отсортирована по количеству голов!" << endl;
}

void sort_by_assists_quantity(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	size_t i, j;
	int gap;
	int flag;
	for (gap = vec_of_players_data.size() / 2; gap > 0; gap /= 2)
	{
		do
		{
			flag = 0;
			for (i = 0, j = gap; j < vec_of_players_data.size(); i++, j++)
			{
				if (vec_of_players_stats.at(i).get_assists_quantity() < vec_of_players_stats.at(i + gap).get_assists_quantity())
				{
					swap(vec_of_players_data.at(i), vec_of_players_data.at(i + gap));
					swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + gap));
					flag = 1;
				}
			}
		} while (flag);
	}
	cout << "\n  Статистика игроков успешно отсортирована по количеству ассистов!" << endl;
}

void sort_by_played_matches_quantity(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	size_t i, j;
	int gap;
	int flag;
	for (gap = vec_of_players_data.size() / 2; gap > 0; gap /= 2)
	{
		do
		{
			flag = 0;
			for (i = 0, j = gap; j < vec_of_players_data.size(); i++, j++)
			{
				if (vec_of_players_stats.at(i).get_played_matches_quantity() < vec_of_players_stats.at(i + gap).get_played_matches_quantity())
				{
					swap(vec_of_players_data.at(i), vec_of_players_data.at(i + gap));
					swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + gap));
					flag = 1;
				}
			}
		} while (flag);
	}
	cout << "\n  Статистика игроков успешно отсортирована по количеству сыгранных матчей!" << endl;
}

void sort_by_surname(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	size_t i, j;
	int gap;
	int flag;
	for (gap = vec_of_players_data.size() / 2; gap > 0; gap /= 2)
	{
		do
		{
			flag = 0;
			for (i = 0, j = gap; j < vec_of_players_data.size(); i++, j++)
			{
				if (vec_of_players_data.at(i).get_surname() > vec_of_players_data.at(i+gap).get_surname())
				{
					swap(vec_of_players_data.at(i), vec_of_players_data.at(i+gap));
					swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + gap));
					flag = 1;
				}
			}
		} while (flag);
	}

	cout << "\n  Статистика игроков успешно отсортирована по фамилии!" << endl;
}

void sort_by_goals_and_assists(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats)
{
	int* goals_and_assists = new int[vec_of_players_data.size()];
	for (size_t i = 0; i < vec_of_players_data.size(); i++)
	{
		goals_and_assists[i] = vec_of_players_stats.at(i).get_goals_quantity() + vec_of_players_stats.at(i).get_assists_quantity();
	}
	size_t i, j;
	int gap;
	int flag;
	for (gap = vec_of_players_data.size() / 2; gap > 0; gap /= 2)
	{
		do
		{
			flag = 0;
			for (i = 0, j = gap; j < vec_of_players_data.size(); i++, j++)
			{
				if (goals_and_assists[i] < goals_and_assists[i+gap])
				{
					swap(vec_of_players_data.at(i), vec_of_players_data.at(i+gap));
					swap(vec_of_players_stats.at(i), vec_of_players_stats.at(i + gap));
					swap(goals_and_assists[i], goals_and_assists[i + gap]);
					flag = 1;
				}
			}
		} while (flag);
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