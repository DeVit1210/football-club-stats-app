#include<iostream>
#include<fstream>
#include<conio.h>
#include"Authorization.h"

using namespace std;

int User::Enter()
{
	vector<User> users_data;
	read_user_data(users_data);
	if (users_data.empty())
		cout << "\n  Ни один пользователь еще не зарегистрирован в системе!" << endl;
	else
	{
		system("cls");
		string userLogin;
		int number_of_user;
		if (check_login(users_data, number_of_user))
			if (users_data[number_of_user].check_password())
				return SUCCESS;
	}

	push_and_clear_page();
	return AUTHORIZATION_ERROR;
}

bool User::verify_password(vector<User>& vec_of_users)
{
	for (size_t i = 0; i < vec_of_users.size(); i++)
		if (m_password == vec_of_users.at(i).m_password)
			return false;

	return true;
}

void User::change_login()
{
	system("cls");
	cout << "\n  Введите новый логин: ";
	while (true)
	{
		cin >> m_login;
		if (registrationCheck(m_login)) break;
	}
	cout << "\n  Логин успешно изменен!" << endl;
}

void User::change_password()
{
	system("cls");
	cout << "\n  Введите новый пароль: ";
	string newPassword;
	while (true)
	{
		cin >> newPassword;
		if (registrationCheck(newPassword)) break;
	}
	cout << "Пароль успешно изменен!" << endl;
}

void User::change_surname()
{
	system("cls");
	cout << "\n  Введите новую фамилию: " << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_surname;
		if (check_string_for_wrong_symbols(m_surname)) checker = true;
	}
	cout << "\n  Фамилия успешно изменена!" << endl;
}

void User::change_name()
{
	system("cls");
	cout << "\n  Введите новое имя: ";
	string newName;
	bool checker(false);
	while (!checker)
	{
		cin >> m_name;
		if (registrationCheck(m_name)) checker = true;
	}
	cout << "\n  Имя успешно изменено!" << endl;
}

void User::change_patronymic()
{
	system("cls");
	cout << "\n  Введите новое отчество" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_patronymic;
		if (registrationCheck(m_patronymic)) checker = true;
	}
	cout << "\n  Отчество успешно изменено!" << endl;
}

ostream& operator<<(ostream& fusers, User& obj)
{
	fusers << endl << obj.m_login << endl
		<< obj.m_password << endl
		<< obj.m_surname << endl
		<< obj.m_name << endl
		<< obj.m_patronymic;

	return fusers;
}

istream& operator>>(istream& fusers, User& obj)
{
	fusers >> obj.m_login
		>> obj.m_password
		>> obj.m_surname
		>> obj.m_name
		>> obj.m_patronymic;

	return fusers;
}

void write_user_data(vector<User>& vec_of_users)
{
	ofstream fusers(USERS_DATA);
	for (size_t i = 0; i < vec_of_users.size(); i++)
		fusers << vec_of_users.at(i);
	fusers.close();
}

void read_user_data(vector<User>& vec_of_users)
{
	int amount_of_users = readAmount(USERS_AMOUNT);
	ifstream fusers(USERS_DATA);
	for(int i=0; i<amount_of_users; i++)
	{
		User temp;
		fusers >> temp;
		vec_of_users.push_back(temp);
	}
	fusers.close();
}

void User::user_module()
{
	vector<IdentityData> players_data;
	vector<Statistics> players_stats;
	vector<Game> games_data;
	User user;
	int number_of_players = readAmount(PLAYERS_NUM);
	if (number_of_players)
	{
		read_players_data(players_data);
		read_stats_data(players_stats);
		read_game_data(games_data);
	}
	while (true)
	{
		cout << "\n  1-Просмотреть данные об игроках"
			"\n  2-Отсортировать данные об игроках  "
			"\n  3-Найти данные об игроке "
			"\n  4-Просмотреть статистику самых резуьтативных игроков  "
			"\n  5-Просмотреть статистику игроков с красными карточками  "
			"\n  6-Просмотреть статистику игр" 
			"\n  7-Выйти в главное меню"<< endl;

		cout << "\n  Ваш выбор?   ";
		int choice;
		cin >> choice;
		cin.ignore(32767, '\n');
		switch (choice)
		{
		case 1: showStats(players_data, players_stats); break;
		case 2: sortStats(players_data, players_stats); break;
		case 3: findStats(players_data, players_stats); break;
		case 4: show_the_most_productive(players_data, players_stats); break;
		case 5: showRedCardsStats(players_data, players_stats); break;
		case 6: show_games(games_data); break;
		case 7: system("cls");  return; break;
		default: 
			cout << "  " << INPUT_ERROR << endl;
			clear_bufer();
			break;
		}
		push_and_clear_page();
	}
}