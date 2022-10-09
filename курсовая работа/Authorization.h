#pragma once
#include<vector>
#include<string>
#include"Player.h"
#include"Game.h"

using namespace std;

const int LEFT_RANGE_FOR_DAYS = 1;
const int RIGHT_RANGE_30 = 30;
const int RIGHT_RANGE_31 = 31;
const int RIGHT_RANGE_FEBRUARY = 28;
const int LEFT_RANGE_FOR_MONTHS = 1;
const int RIGHT_RANGE_FOR_MONTHS = 12;
const int LEFT_RANGE_FOR_AGE = 1970;
const int RIGHT_RANGE_FOR_AGE = 2007;

const string BE_CAREFUL = "\n Будьте внимательнее при вводе данных!";
const string NO_PLAYER_IN_THE_SQUAD = "\n  Игрока с этим номером нет в составе на матч!";
const string TRY_IT_AGAIN = "Попробуйте еще раз :";

enum month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};


const string INPUT_ERROR = "Упс... Произошла ошибка ввода! Попробуйте еще раз!";
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
	bool check_password();                             // виртуальная функция для входа; будет переопрделена в классах Administrator и User
	void set_login();
	void set_password();
	void set_surname();
	void set_name();
	void set_patronymic();                                          // ввод данных 
	void showStats(vector<IdentityData>&, vector<Statistics>&);	    // отображение статистики всей команды
	void show_the_most_productive(vector<IdentityData>&, vector<Statistics>&);									// вывод на экран 6 самых результативных игрооков по системе "гол+пас"
	void showRedCardsStats(vector<IdentityData>&, vector<Statistics>&);										// вывод на экран статистики игроков, имеющих хотя бы одну красную карточку
	void sortStats(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats);	
	void show_games(vector<Game>& vec_of_games);
	// отсортировать статистику игроков
	void findStats(vector<IdentityData>&, vector<Statistics>&);
	void find_by_surname(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats);
	// поиск различной статистики игроков
};

class User;
class Administrator : public Main
{
public:
	void read_admin_data();
	void write_admin_data();
	void showAccounts(vector<User>& vec_of_users);
	void addAccount(vector<User>& vec_of_users);
	void editAccount(vector<User>& vec_of_users);
	void deleteAccount(vector<User>& vec_of_users);
	void addPlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats, int& number_of_players);
	void add_game_data(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats, vector<Game>& vec_of_games);
	void deletePlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats);
	void editPlayer(vector<IdentityData>& vec_of_players_data, vector<Statistics>& vec_of_players_stats);
	void registration();
	int Enter();
	bool check_login();
	friend class User;
	friend void admin_menu();
	friend void accountsWork();
};


class User : public Main
{
public:
	int Enter();
	void change_login();
	void change_password();
	void change_surname();
	void change_name();
	void change_patronymic();
	bool check_login(vector<User>& vec_of_users, int&);
	bool verify_password(vector<User>& vec_of_users);
	friend void read_user_data(vector<User>& vec_of_users);
	friend void write_user_data(vector<User>& vec_of_users);
	friend class Administrator;
	friend void accountsWork();
};

int menu();
void admin_menu();

int readAmount(string);
void writeAmount(int, string);

bool chooseNextStep();
bool registrationCheck(string);

void accountsWork();
int accounts_work_menu();
void playersWork();
int players_work_menu();

void user_module();

void clear_bufer();
void push_and_clear_page();

int get_correct_player_id();
