
#pragma once
#include<vector>
using namespace std;
#include"Player.h"
const string ADMINS_DATA = "Admins.txt";
const string ADMINS_AMOUNT = "adminNum.txt";
const string USERS_DATA = "usersData.txt";
const string USERS_AMOUNT = "usersNum.txt";

class Main
{
protected:
	string m_login;
	string m_password;
	string m_surname;
	string m_name;
	string m_patronymic;
public:
	virtual int Enter() = 0;
	virtual void registration() = 0;
	void input_registration_data();
	//void showStats();												// отображение статистики всей команды
	//void showTheMostProductive();									// вывод на экран 6 самых результативных игрооков по системе "гол+пас"
	//void showRedCardsStats();										// вывод на экран статистики игроков, имеющих хотя бы одну красную карточку
	//void sortStats();												// отсортировать статистику игроков
	//void findStats();												// поиск различной статистики игроков
};

class User;
class Administrator : public Main
{
public:
	void read_admin_data();
	void showAccounts(User*, int);
	//void addAccount();
	void editAccount(User*, int);
	void deleteAccount(User*, int&);
	void addPlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats, int& number_of_players);
	//void deletePlayer();
	//void editPlayer();
	int Enter();
	void registration();
	friend class User;
	friend void admin_menu();
	friend void accountsWork();
};


class User : public Main
{
public:
	int Enter();
	void registration();
	void change_login();
	void change_password();
	void change_surname();
	void change_name();
	void change_patronymic();
	friend void read_user_data(User*, int);
	friend void write_user_data(User*, int);
	friend class Administrator;
	friend void accountsWork();
};

int menu();
void admin_menu();

void read_user_data(User*, int);

int readAmount(string);
void writeAmount(int, string);

bool chooseNextStep();
bool registrationCheck(string);

void accountsWork();
int accounts_work_menu();
void playersWork();
int players_work_menu();

void push_and_clear_page();
