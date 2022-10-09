#include<iostream>
#include<iterator>
#include<iomanip>
#include<string>
#include<vector>
#include"Game.h"
#include"Authorization.h"


void Game::set_opp_name()
{
	cout << "\n  Введите название команды соперника: ";
	while (true)
	{
		cin >> m_opponent_name;
		int result_of_checking = check_string_for_wrong_symbols(m_opponent_name);
		if (result_of_checking == DIGIT_ERROR)
			cout << "Строка не должна содержать цифры! Попробуйте еще раз: ";
		else if (result_of_checking == WRONG_SYMBOL_ERROR)
			cout << "Строка должна содержать только буквы или тире! Попробуйте еще раз: ";
		else
		{
			cin.ignore(32767, '\n');
			break;
		}
	}
}

void Game::show_squad(vector<IdentityData>& vec_of_players)
{
	cout << "========================================" << endl;
	cout << "|  Номер  |   Фамилия   |      Имя     |" << endl;
	cout << "========================================" << endl;
	for (size_t i = 0; i < vec_of_players.size(); i++)
	{
		cout << "|" << setw(9) << vec_of_players.at(i).get_id()
			<< "|" << setw(14) << vec_of_players.at(i).get_surname()
			<< "|" << setw(14) << vec_of_players.at(i).get_name() << endl;

		cout << "========================================" << endl;
	}
}

void Game::show_match_squad(vector<IdentityData>& vec_of_players)
{
	cout << "========================================" << endl;
	cout << "|  Номер  |   Фамилия   |      Имя     |" << endl;
	cout << "========================================" << endl;
	for (int i = 0; i < PLAYERS_AMOUNT; i++)
	{
		cout << "|" << setw(9) << vec_of_players.at(i).get_id()
			<< "|" << setw(14) << vec_of_players.at(i).get_surname()
			<< "|" << setw(14) << vec_of_players.at(i).get_name() << endl;

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
		cout << "\n Введите id игрока, принявшего участие в матче: ";
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num!=NO_PLAYER_WITH_SUCH_NUMBER_ERROR && !is_already_in_the_squad(player_num, players_quantity))
		{
			cout << "\n  Вы хотите добавить игрока с фамилией " << vec_of_players.at(counter).get_surname() << "?(y/n): ";
			if (chooseNextStep())
			{
				m_squad_players_id[players_quantity] = player_num;
				players_quantity++;
				vec_of_players_stats.at(counter).add_played_matches_quantity();
				cout << "\n  Игрок № " << players_quantity << " успешно добавлен в состав!" << endl;
			}
		}
		else if (player_num!=NO_PLAYER_WITH_SUCH_NUMBER_ERROR)
			cout << "\n  Этот игрок уже включен в состав на матч! " << endl;
		else cout << "\n  Игрока с таким номером нет в составе команды!" << endl;
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
	cout << "\n  Введите количество забитых командой голов: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_scored_goals_quantity;
		if (cin.fail())
		{
			clear_bufer();
			cout << "  " << INPUT_ERROR << " ";
		}
		else if (m_scored_goals_quantity < 0)
			cout << "\n  К сожалению, нельзя забить отрицательное количество голов! " << endl <<  TRY_IT_AGAIN;
		else if (m_scored_goals_quantity > 10)
		{
			cout << "\n  Вы уверены, что команда забила " << m_scored_goals_quantity << " голов?(y/n): ";
			if (chooseNextStep())
				checker = true;
			else cout << BE_CAREFUL << TRY_IT_AGAIN;
		}
		else
		{
			cin.ignore(32767, '\n');
			checker = true;
		}
	}
	cout << "\n  Данные о забитых голах успешно введены!" << endl;
}

void Game::set_conceded_quantity()
{
	cout << "\n  Введите количество пропущенных командой голов: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_conceded_goals_quantity;
		if (cin.fail())
		{
			clear_bufer();
			cout << INPUT_ERROR << endl;
		}
		else if (m_conceded_goals_quantity < 0)
			cout << "\n  Нельзя пропустить отрицательное количество голов!" << TRY_IT_AGAIN;
		else if (m_conceded_goals_quantity > 10)
		{
			cout << "\n  Вы уверены, что команда пропустила " << m_conceded_goals_quantity << " голов?(y/n): ";
			if (chooseNextStep())
				checker = true;
			else cout << BE_CAREFUL << endl << TRY_IT_AGAIN;
		}
		else
		{
			cin.ignore(32767, '\n');
			checker = true;
		}
	}
	cout << "\n  Данные о пропущенных голах успешно введены!" << endl;
}

void Game::set_yellow_cards_quantity()
{
	cout << "\n  Введите количество желтых карточек в матче: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_yellow_cards_quantity;
		if (cin.fail())
		{
			clear_bufer();
			cout << INPUT_ERROR << endl;
		}
		else if (m_yellow_cards_quantity < 0)
			cout << "\n  Нельзя получить отрицательное количество карточек!" << TRY_IT_AGAIN;
		else if (m_yellow_cards_quantity > 10)
		{
			cout << "\n  Вы уверены, что команда получила " << m_yellow_cards_quantity << " желтых карточек?(y/n): ";
			if (chooseNextStep())
				checker = true;
			else cout << BE_CAREFUL << TRY_IT_AGAIN;
		}
		else
		{
			cin.ignore(32767, '\n');
			checker = true;
		}
	}
	cout << "\n  Данные о полученных желтых карточках успешно введены!" << endl;
	push_and_clear_page();
}

void Game::set_red_cards_quantity()
{
	cout << "\n  Введите количество красных карточек в матче: ";
	bool checker(false);
	while (!checker)
	{
		cin >> m_red_cards_quantity;
		if (cin.fail())
		{
			clear_bufer();
			cout << INPUT_ERROR << endl;
		}
		else if (m_red_cards_quantity < 0)
			cout << "\n  Нельзя получить отрицательное количество карточек!" << TRY_IT_AGAIN;
		else if (m_red_cards_quantity > 10)
		{
			cout << "\n  Вы уверены, что команда получила " << m_red_cards_quantity << " желтых карточек?(y/n): ";
			if (chooseNextStep())
				checker = true;
			else cout << BE_CAREFUL << TRY_IT_AGAIN;
		}
		else
		{
			cin.ignore(32767, '\n');
			checker = true;
		}
	}
	cout << "\n  Данные о полученных красных карточках успешно введены!" << endl;
	push_and_clear_page();
}


void Game::add_played_matches_in_stats(vector<Statistics>& vec_of_players)
{
	for (size_t i = 0; i < PLAYERS_AMOUNT; i++)
		for (size_t j = 0; i < vec_of_players.size(); j++)
			if (m_squad_players_id[i] = vec_of_players.at(j).get_id())
				vec_of_players.at(j).add_played_matches_quantity();
}

void Game::add_goals_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	int i = 0;
	while (i < m_scored_goals_quantity)
	{
		int counter = 0;
		show_match_squad(vec_of_players_data);
		cout << "\n  Введите номер игрока, забившего " << i + 1 << " гол: ";
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num >= 0 && is_already_in_the_squad(player_num, PLAYERS_AMOUNT))
		{
			cout << "\n  Гол № " << i + 1 << "забил " << vec_of_players_data.at(counter).get_surname()
				<< " " << vec_of_players_data.at(counter).get_name() << "?(y/n):";
			if (chooseNextStep())
			{
				vec_of_players_stats.at(counter).add_goals_quantity();
				add_assist_in_stats(vec_of_players_stats, vec_of_players_data, player_num);
				i++;
			}
		}
		else cout << NO_PLAYER_IN_THE_SQUAD << endl;
		push_and_clear_page();
	}
}

void Game::add_assist_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data, int id)
{
	cout << "\n  Гол был забит после паса?(y/n): ";
	if (!chooseNextStep())
		return;
	else
	{
		system("cls");
		bool checker(false);
		while (!checker)
		{
			show_match_squad(vec_of_players_data);
			int counter = 0;
			cout << "\n  Введите номер игрока, отдавшего ассист:  ";
			int player_num = check_id(vec_of_players_stats, counter);
			if (id == player_num)
			{
				cout << "\n  Игрок не может отдать голевой пас самому себе!" << endl;
				push_and_clear_page();
			}
			else if (player_num && is_already_in_the_squad(player_num, PLAYERS_AMOUNT))
			{
				cout << "\n  Ассист отдал " << vec_of_players_data.at(counter).get_surname()
					<< " " << vec_of_players_data.at(counter).get_name() << "?(y/n): ";
				if (chooseNextStep())
				{
					vec_of_players_stats.at(counter).add_assists_quantity();
					checker = true;
				}
				else system("cls");
			}
			else
			{
				cout << NO_PLAYER_IN_THE_SQUAD << endl;
				push_and_clear_page();
			}
		}
	}
}

void Game::add_cards_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	int cards_amount = 0;
	int* temp_red_cards_array = new int[m_red_cards_quantity];
	while (cards_amount != m_red_cards_quantity)
	{
		int counter = 0;
		show_match_squad(vec_of_players_data);
		cout << "\n  Введите id игрока, получившего красную карточку: ";
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num && is_already_in_the_squad(player_num, PLAYERS_AMOUNT))
		{
			cout << "\n  Красную карточку получил " << vec_of_players_data.at(counter).get_surname() << " "
				<< vec_of_players_data.at(counter).get_name() << "?(y/n): ";
			if (chooseNextStep())
			{
				if (check_for_two_red_cards(player_num, temp_red_cards_array))
				{
					temp_red_cards_array[cards_amount] = player_num;
					vec_of_players_stats.at(counter).add_red_card_in_stats();
					cards_amount++;
				}
				else cout << "\n  Игрок не может получить 2 красные карточки за матч!" << endl;
			}
			else push_and_clear_page();
		}
		else cout << NO_PLAYER_IN_THE_SQUAD << TRY_IT_AGAIN;
		push_and_clear_page();
	}
}

void Game::add_yellow_cards_in_stats(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	int cards_amount = 0;
	int* temp_yellow_cards_array = new int[m_yellow_cards_quantity];
	while (cards_amount != m_yellow_cards_quantity)
	{
		int counter = 0;
		show_match_squad(vec_of_players_data);
		cout << "Введите id игрока, получившего желтую карточку: " << endl;
		int player_num = check_id(vec_of_players_stats, counter);
		if (player_num && is_already_in_the_squad(player_num, PLAYERS_AMOUNT))
		{
			cout << "Желтую карточку получил " << vec_of_players_data.at(counter).get_surname() << " "
				<< vec_of_players_data.at(counter).get_name() << "?" << endl;
			if (chooseNextStep())
			{
				if (check_for_three_yellow_cards(player_num, temp_yellow_cards_array))
				{
					vec_of_players_stats.at(counter).add_yellow_card_in_stats();
					temp_yellow_cards_array[cards_amount] = player_num;
					cards_amount++;
				}
				else cout << "\n  Игрок не может получить 3 желтые карточки за матч!" << endl;
			}
		}
		else cout << NO_PLAYER_IN_THE_SQUAD << endl;
		push_and_clear_page();
	}
}

void Game::set_game_data(vector<Statistics>& vec_of_players_stats, vector<IdentityData>& vec_of_players_data)
{
	if (vec_of_players_stats.size() < PLAYERS_AMOUNT)
	{
		cout << "\n  К сожалению, в команде недостаточно игроков для проведения игры!" << endl;
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


		cout << "\n  Данные об игре успешно добавлены" << endl;
	}
}

int check_id(vector<Statistics>& vec_of_players_stats, int& counter)
{
	int id = get_correct_player_id();
	for (size_t i = 0; i < vec_of_players_stats.size(); i++)
	{
		if (id == vec_of_players_stats.at(i).get_id())
		{
			counter = i;
			return id;
		}
	}
	return NO_PLAYER_WITH_SUCH_NUMBER_ERROR;
}

int get_correct_player_id()
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
			cout << INPUT_ERROR << " ";
		}
		else if (id < 0 || id > 99)
			cout << "Вы ввели некорректный номер игрока! Введите число от 1 до 99: ";
		else
			checker = true;
	}

	return id;
}
int check_unique_number(vector<IdentityData>& vec_of_players)
{
	int id = get_correct_player_id();
	for (size_t i = 0; i < vec_of_players.size(); i++)
		if (id == vec_of_players.at(i).get_id())
			return -1;

	return id;
}

bool Game::check_for_two_red_cards(int id, int* array_of_cards)
{
	for (int i = 0; i < m_red_cards_quantity; i++)
		if (array_of_cards[i] == id)
			return false;
	return true;
}

bool Game::check_for_three_yellow_cards(int id, int* array_of_cards)
{
	int counter = 0;
	for (int i = 0; i < m_yellow_cards_quantity; i++)
		if (array_of_cards[i] == id)
			counter++;
	if (counter > 1)
		return false;

	return true;
}