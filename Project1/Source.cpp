#include <iostream>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <math.h>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class Administrator;
class User;
class Bets;

int menu_a(Administrator& adm); //Меню администратора со всеми возможностями
int menu(); //Основное меню, функция, с которой начинается приложение
int menu_u(User& us); //Меню пользователя со всеми возможности
int admin(); //Регистрация администратора
int admin_enter(); //Вход администратора 
int m_sort(User* us, int k); //Обобщённая сортировка пользователей
int m_filtr(User* us, int k); //Обобщённая фильтрация пользователей
int m_find(User* us, int k); //Поиск пользователей по параметрам
int s_sort(Bets* bets, int k);  //Обобщённая функция сортировки ставок
int s_find(Bets* bets, int k); //Поиск ставок по параметрам
int s_filtr(Bets* bets, int k); //Фильтрация ставок по коэффициентам
int user(); //Регистрация пользователя
int user_enter(); //Вход пользователя
int Game(); //Эмуляция игры команд
int DelUser(); //Удаление пользователя
int DelStav(); //Удаление ставки
int EditUser(); //Редактирование параметров пользователя
int EditBet(); //Редактирование параметров ставок

class Imain {
protected:
	string login;
	string password;
	string surname;
	string name;
	string patronymic;
public:
	int virtual Enter() = 0;
	int virtual Register() = 0;
	int virtual Show() = 0;
	friend int admin();
	friend int user();
	friend int user_enter();
	friend int admin_enter();
	friend int menu_a(Administrator& adm);
	friend int menu_u(User& us);
	friend int m_sort(User* us, int k);
	friend int m_filtr(User* us, int k);
	friend int m_find(User* us, int k);
	friend int DelUser();
	friend int EditUser();
};

class Bets {
	string command_1; //Название 1 команды
	string command_2; //название 2 команды
	double koef1; //Коэффициент 1 команды
	double koef2; //Коэффициент 2 команды
	int timeH; //Время начала игры в часах
	int timeM; //Время начала игры в минутах
	int goals_1; //Счёт 1 команды
	int goals_2; //Счёт 2 команды
public:
	Bets() {

	}
	Bets(string com1, string com2, double k, double k1, int t1, int t2, int g1, int g2) //Конструктор с параметрами, создаёт игру
		:koef1(k), koef2(k1), timeH(t1), timeM(t2), goals_1(g1), goals_2(g2), command_1(com1), command_2(com2)
	{
		int l;
		ifstream fin("n_s.txt");
		if (!fin.is_open()) {
			ofstream fon("n_s.txt");
			fon << 1;
			fon.close();
		}
		else {
			fin >> l;
			l++;
			ofstream fun("n_s.txt");
			fun << l;
			fun.close();
			fin.close();
		}
		fin.close();
		ofstream bet("Bets.txt", ios_base::app);
		bet << this->command_1 << "\n";
		bet << this->command_2 << "\n";
		bet << this->koef1 << "\n";
		bet << this->koef2 << "\n";
		bet << this->timeH << "\n";
		bet << this->timeM << "\n";
		bet << this->goals_1 << "\n";
		bet << this->goals_2 << "\n";
		bet.close();
	}
	friend class Administrator;
	friend class User;
	friend int s_sort(Bets* bets, int k);
	friend int s_find(Bets* bets, int k);
	friend int s_filtr(Bets* bets, int k);
	friend int DelStav();
	friend int EditBet();
};

class User :public Imain {
protected:
	double balance = 0;
public:
	int Enter() { //Обобщённая функция пользовательского входа
		cout << "Добро пожаловать в нашу букмекерскую контору \" Всё или ничего \"" << endl;
		return user_enter();
	}

	int Register() { //обобщённая функция регистрации пользователя
		ifstream fin("Users.txt");
		cout << "Доброго времени суток!" << endl;
		cout << "Хорошей регистрации!" << endl;
		user();
		return 0;
	}

	int AddBalance() { //Функция начисления баланса пользовтелю
		ifstream fonk;
		ifstream cifra;
		int k;
		int b = 0;
		string card1; //Номер карты
		int card2_m = 0; //Месяц карты
		int card2_y = 0; //год карты
		string card3; //CVV-код
		string tel; //Мобильный телефон
		double sum; //Сумма для вывода
		fonk.open("Users.txt");
		cifra.open("n_u.txt");
		cifra >> k;
		cifra.close();
		ofstream fink;
		User* us = new User[k];
		for (int i = 0; i < k; i++) {
			fonk >> us[i].login;
			fonk >> us[i].password;
			fonk >> us[i].name;
			fonk >> us[i].surname;
			fonk >> us[i].patronymic;
			fonk >> us[i].balance;
			if (this->login.compare(us[i].login) == 0 && this->name.compare(us[i].name) == 0 && this->surname.compare(us[i].surname) == 0) {
				b = i;
			}
		}
		fonk.close();
		while (true) {
			cout << "Выберите тип оплаты:" << endl;
			cout << "1. Картой" << endl;
			cout << "2. Мобильный телефон" << endl;
			cout << "0. Отменить действие" << endl;
			switch (_getch()) {
			case '1':
				do {
					cout << "Введите 16 цифр с лицевой стороны карты" << endl;
					cin >> card1;
					system("cls");
				} while (card1.length() < 16 || card1.length() > 16);
				do {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Введите срок действия карты в формате: мм гг" << endl;
					scanf_s("%d%d", &card2_m, &card2_y);
					system("cls");
				} while (card2_y > 2021 || card2_y < 2017 || card2_m >12 || card2_m < 1 || isalpha(card2_m) || isalpha(card2_y));
				do {
					cout << "Введите защитный код (CVV) с оборотной стороны карты" << endl;
					cin >> card3;
					system("cls");
				} while (card3.length() < 3 || card3.length() > 3);
			l1:
				cout << "Введите сумму для начисления (мин - 1 000, макс - 100 000)" << endl;
				cin >> sum;
				if (sum < 1000 || sum > 100000) {
					cout << "Ошибка, некорректная сумма" << endl;
					goto l1;
				}
				this->balance = this->balance + sum;
				us[b].balance = this->balance;
				fink.open("Users.txt");
				for (int i = 0; i < k; i++) {
					fink << us[i].login << "\n";
					fink << us[i].password << "\n";
					fink << us[i].name << "\n";
					fink << us[i].surname << "\n";
					fink << us[i].patronymic << "\n";
					fink << us[i].balance << "\n";
				}
				fink.close();
				return 0;
			case '2':
				do
				{
					cout << "Введите номер мобильного телефона (+375...)" << endl;
					cin >> tel;
					system("cls");
				} while (tel.length() < 12 && tel[0] != '+' && tel[1] != '3' && tel[2] != '7' && tel[3] != '5');
			l3:
				cout << "Введите сумму для начисления (мин - 1 000, макс - 100 000)" << endl;
				cin >> sum;
				if (sum < 1000 || sum > 100000 || sum > this->balance || isalpha(sum)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Ошибка, некорректная сумма" << endl;
					goto l3;
				}
				this->balance = this->balance + sum;
				us[b].balance = this->balance;
				fink.open("Users.txt");
				for (int i = 0; i < k; i++) {
					fink << us[i].login << "\n";
					fink << us[i].password << "\n";
					fink << us[i].name << "\n";
					fink << us[i].surname << "\n";
					fink << us[i].patronymic << "\n";
					fink << us[i].balance << "\n";
				}
				fink.close();
				delete[] us;
				return 0;
			case '0':
				system("cls");
				delete[] us;
				return 0;
			default:
				cout << "Неверная команда, повторите ещё раз!";
			}
		}
		return 0;
	}

	int Show() {
		return 0;
	}

	int Out() { //Функция вывода средств пользователем
		ifstream fonk;
		ifstream cifra;
		int k;
		int b = 0;
		string card1; //Номер карты
		int card2_m = 0; //Месяц карты
		int card2_y = 0; //год карты
		string card3; //CVV-код
		string tel; //Мобильный телефон
		double sum; //Сумма для вывода
		fonk.open("Users.txt");
		cifra.open("n_u.txt");
		cifra >> k;
		cifra.close();
		ofstream fink;
		User* us = new User[k];
		for (int i = 0; i < k; i++) {
			fonk >> us[i].login;
			fonk >> us[i].password;
			fonk >> us[i].name;
			fonk >> us[i].surname;
			fonk >> us[i].patronymic;
			fonk >> us[i].balance;
			if (this->login.compare(us[i].login) == 0 && this->name.compare(us[i].name) == 0 && this->surname.compare(us[i].surname) == 0) {
				b = i;
			}
		}
		fonk.close();
		while (true) {
			cout << "Выберите способ вывода:" << endl;
			cout << "1. На карту" << endl;
			cout << "2. На мобильный телефон" << endl;
			cout << "0. Отменить действие" << endl;
			switch (_getch()) {
			case '1':
				do {
					cout << "Введите 16 цифр с лицевой стороны карты" << endl;
					cin >> card1;
					system("cls");
				} while (card1.length() < 16 || card1.length() > 16);
				do {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Введите срок действия карты в формате: мм гг" << endl;
					scanf_s("%d%d", &card2_m, &card2_y);
					system("cls");
				} while (card2_y > 2021 || card2_y < 2017 || card2_m >12 || card2_m < 1 || isalpha(card2_m) || isalpha(card2_y));
				do {
					cout << "Введите защитный код (CVV) с оборотной стороны карты" << endl;
					cin >> card3;
					system("cls");
				} while (card3.length() < 3 || card3.length() > 3);
			l1:
				cout << "Введите сумму для вывода (мин - 10 000, макс - 1 000 000)" << endl;
				cin >> sum;
				if (sum < 10000 || sum > 1000000 || sum > this->balance || isalpha(sum)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Ошибка, некорректная сумма" << endl;
					goto l1;
				}
				this->balance -= sum;
				us[b].balance -= sum;
				fink.open("Users.txt");
				for (int i = 0; i < k; i++) {
					fink << us[i].login << "\n";
					fink << us[i].password << "\n";
					fink << us[i].name << "\n";
					fink << us[i].surname << "\n";
					fink << us[i].patronymic << "\n";
					fink << us[i].balance << "\n";
				}
				fink.close();
				return 0;
			case '2':
				do
				{
					cout << "Введите номер мобильного телефона (+375...)" << endl;
					cin >> tel;
					system("cls");
				} while (tel.length() < 12 && tel[0] != '+' && tel[1] != '3' && tel[2] != '7' && tel[3] != '5');
			l2:
				cout << "Введите сумму для вывода (мин - 10 000, макс - 1 000 000)" << endl;
				cin >> sum;
				if (sum < 1000 || sum > 100000 || sum > this->balance || isalpha(sum)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Ошибка, некорректная сумма" << endl;
					goto l2;
				}
				this->balance -= sum;
				us[b].balance -= sum;
				fink.open("Users.txt");
				for (int i = 0; i < k; i++) {
					fink << us[i].login << "\n";
					fink << us[i].password << "\n";
					fink << us[i].name << "\n";
					fink << us[i].surname << "\n";
					fink << us[i].patronymic << "\n";
					fink << us[i].balance << "\n";
				}
				fink.close();
				delete[] us;
				return 0;
			case '0':
				delete[] us;
				system("cls");
				return 0;
			default:
				cout << "Неверная команда, повторите ещё раз!";
			}
		}
		return 0;

	}

	int PlaceBet() {
		char o;
		ifstream fun("n_u.txt");
		int u; //переменная для подсчёта количества юзеров
		fun >> u;
		fun.close();
		User* us = new User[u];
		int i = 0;
		ifstream fonk;
		fonk.open("Users.txt");
		while (i < u) {
			fonk >> us[i].login;
			fonk >> us[i].password;
			fonk >> us[i].name;
			fonk >> us[i].surname;
			fonk >> us[i].patronymic;
			fonk >> us[i].balance;
			i++;
		}
		i = 0;
		int z; //переменная для запоминания юзера;
		while (i < u) {
			if (this->login == us[i].login && this->name == us[i].name && this->surname == us[i].surname) {
				z = i;
				break;
			}
		}
		double stavka; //количество рубликов, которое поставит пользователь
		fonk.close();
		while (true) {
			ifstream bet("Bets.txt");
			ifstream fin("n_s.txt");
			if (!fin.is_open()) {
				cout << "На данный момент в системе нет ни одной ставки!" << endl;
				system("pause");
				system("cls");
				return 0;
			}
			int k;
			fin >> k;
			fin.close();
			Bets* bets = new Bets[k];
			for (int i = 0; i < k; i++) {
				bet >> bets[i].command_1;
				bet >> bets[i].command_2;
				bet >> bets[i].koef1;
				bet >> bets[i].koef2;
				bet >> bets[i].timeH;
				bet >> bets[i].timeM;
				bet >> bets[i].goals_1;
				bet >> bets[i].goals_2;
			}
			bet.close();
			system("cls");
			printf("********************************************************************************\n");
			printf("| № |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("********************************************************************************\n");
			for (int i = 0; i < k; i++) {
				cout << "|" << setw(3) << i << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
				printf("********************************************************************************\n");
			}
			char g;
			int b;
			cout << "1. Сделать ставку" << endl;
			cout << "2. Отменить" << endl;
			switch (_getch()) {
			case '1':
				cout << "Выберите номер игры, на которую хотите сделать ставку:" << endl;
				g = _getch();
				b = g - '0';
				if (b >= k) {
					system("cls");
					cout << "Такой ставки не существует!" << endl;
					system("pause");
					system("cls");
					break;
				}
			l2:
				system("cls");
				printf("****************************************************************************\n");
				printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
				printf("****************************************************************************\n");
				cout << "|" << setw(17) << bets[b].command_1 << "|" << setw(16) << bets[b].command_2 << "|" << setw(9) << bets[b].koef1 << "|" << setw(9) << bets[b].koef2 << "|" << setw(3) << bets[b].goals_1 << ":" << setw(2) << bets[b].goals_2 << "|" << setw(5) << bets[b].timeH << ":" << setw(6) << bets[b].timeM << "|" << endl;
				printf("****************************************************************************\n");
				cout << "Вы выбрали нужную игру?" << endl;
				cout << "1. Да" << endl;
				cout << "2. Нет" << endl;
				o = _getch();
				if (o == '2')	break;
				else if (o != '1') {
					system("cls");
					cout << "Такой команды нет!" << endl;
					system("pause");
					goto l2;
				}
			r1:
				cout << "Введите сумму вашей ставки: ";
				cin >> stavka;
				if (stavka > this->balance || stavka < 0 || isalpha(stavka)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Вы ввели некорректную ставку" << endl;
					cout << "Ваш баланс равен " << this->balance << endl;
					system("pause");
					system("cls");
					goto r1;
				}
				system("cls");
			ll:
				printf("****************************************************************************\n");
				printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
				printf("****************************************************************************\n");
				cout << "|" << setw(17) << bets[b].command_1 << "|" << setw(16) << bets[b].command_2 << "|" << setw(9) << bets[b].koef1 << "|" << setw(9) << bets[b].koef2 << "|" << setw(3) << bets[b].goals_1 << ":" << setw(2) << bets[b].goals_2 << "|" << setw(5) << bets[b].timeH << ":" << setw(6) << bets[b].timeM << "|" << endl;
				printf("****************************************************************************\n");
				cout << "Выберите номер команды, на которую хотите поставить";
				switch (_getch()) {
				case '1': {
					system("cls");
					this->balance -= stavka;
					if (Game() == 1) {
						cout << "Вы выиграли!" << endl;
						cout << "Сумма выигрыша составила " << stavka * bets[b].koef1 << endl;
						this->balance = this->balance + (stavka * bets[b].koef1);
						us[z].balance = this->balance;
						ofstream fout("Users.txt");
						i = 0;
						while (i < u) {
							fout << us[i].login << "\n";
							fout << us[i].password << "\n";
							fout << us[i].name << "\n";
							fout << us[i].surname << "\n";
							fout << us[i].patronymic << "\n";
							fout << us[i].balance << "\n";
							i++;
						}
						system("cls");
						fout.close();
					}
					else if (Game() == 2) {
						cout << "К сожалению, вы проиграли!" << endl;
						us[z].balance = this->balance;
						ofstream fout("Users.txt");
						i = 0;
						while (i < u) {
							fout << us[i].login << "\n";
							fout << us[i].password << "\n";
							fout << us[i].name << "\n";
							fout << us[i].surname << "\n";
							fout << us[i].patronymic << "\n";
							fout << us[i].balance << "\n";
							i++;
						}
						system("pause");
						system("cls");
						fout.close();
					}
					i = 0;
					ofstream bit("Bets.txt");
					while (i < k) {
						if (i != b) {
							bit << bets[i].command_1 << "\n";
							bit << bets[i].command_2 << "\n";
							bit << bets[i].koef1 << "\n";
							bit << bets[i].koef2 << "\n";
							bit << bets[i].timeH << "\n";
							bit << bets[i].timeM << "\n";
							bit << bets[i].goals_1 << "\n";
							bit << bets[i].goals_2 << "\n";
						}
						i++;
					}
					bit.close();
					ofstream fen("n_s.txt");
					k--;
					fen << k;
					fen.close();
				}
						break;

				case '2': {
					this->balance -= stavka;
					if (Game() == 2) {
						cout << "Вы выиграли!" << endl;
						cout << "Сумма выигрыша составила " << stavka * bets[b].koef2 << endl;
						this->balance = this->balance + (stavka * bets[b].koef2);
						us[z].balance = this->balance;
						ofstream fout("Users.txt");
						i = 0;
						while (i < u) {
							fout << us[i].login << "\n";
							fout << us[i].password << "\n";
							fout << us[i].name << "\n";
							fout << us[i].surname << "\n";
							fout << us[i].patronymic << "\n";
							fout << us[i].balance << "\n";
							i++;
						}
						system("pause");
						system("cls");
						fout.close();
					}
					else {
						cout << "К сожалению, вы проиграли!" << endl;
						us[z].balance = this->balance;
						ofstream fout("Users.txt");
						i = 0;
						while (i < u) {
							fout << us[i].login << "\n";
							fout << us[i].password << "\n";
							fout << us[i].name << "\n";
							fout << us[i].surname << "\n";
							fout << us[i].patronymic << "\n";
							fout << us[i].balance << "\n";
							i++;
						}
						system("pause");
						system("cls");
						fout.close();
					}
					i = 0;
					ofstream bit("Bets.txt");
					while (i < k) {
						if (i != b) {
							bit << bets[i].command_1 << "\n";
							bit << bets[i].command_2 << "\n";
							bit << bets[i].koef1 << "\n";
							bit << bets[i].koef2 << "\n";
							bit << bets[i].timeH << "\n";
							bit << bets[i].timeM << "\n";
							bit << bets[i].goals_1 << "\n";
							bit << bets[i].goals_2 << "\n";
						}
						i++;
					}
					bit.close();
					ofstream fen("n_s.txt");
					k--;
					fen << k;
					fen.close();
				}
						break;
				default:
					system("cls");
					cout << "Такой команды нет" << endl;
					system("pause");
					system("cls");
					goto ll;
				}
			case '2':
				delete[] us;
				delete[] bets;
				return 0;
			default:
				system("cls");
				cout << "Такой команды нет" << endl;
				system("pause");
				system("cls");
			}
		}
		return 0;
	}

	User* operator=(User us) {
		this->name = us.name;
		this->surname = us.surname;
		this->patronymic = us.patronymic;
		this->login = us.login;
		this->balance = us.balance;
		return this;
	}

	friend int user();
	friend int menu_u(User& us);
	friend int user_enter();
	friend class Administrator;
	friend int m_sort(User* us, int k);
	friend int m_filtr(User* us, int k);
	friend int m_find(User* us, int k);
	friend int DelUser();
	friend int EditUser();
};

class Administrator :public Imain {
public:

	int Show() { //Функция отображения всех пользователей и ставок
		while (true) {
			system("cls");
			cout << "Выберите нужный пункт:" << endl;
			cout << "1. Отобразить список зарегестрированных пользователей" << endl;
			cout << "2. Отобразить все текущие ставки" << endl;
			cout << "0. Выход" << endl;
			switch (_getch()) {
			case '1': {
				system("cls");
				ifstream nu("n_u.txt");
				int k;
				int i = 0;
				ifstream us("Users.txt");
				if (!nu.is_open()) {
					cout << "В системе не зарегестрировано ни одного пользователя" << endl;
					system("pause");
					system("cls");
					break;
				}
				else nu >> k;
				User* user = new User[k];
				while (i < k) {
					us >> user[i].login;
					us >> user[i].password;
					us >> user[i].name;
					us >> user[i].surname;
					us >> user[i].patronymic;
					us >> user[i].balance;
					i++;
				}
				printf("********************************************************************************\n");
				printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
				printf("********************************************************************************\n");
				i = 0;
				while (i < k) {
					cout << "|" << setw(10) << user[i].login << "|" << setw(11) << user[i].name << "|" << setw(21) << user[i].surname << "|" << setw(20) << user[i].patronymic << "|" << setw(12) << user[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					i++;
				}
			r1:
				cout << "\n\nВыберите нужный пункт:" << endl;
				cout << "1. Сортировка списка пользователей" << endl;
				cout << "2. Поиск пользователей" << endl;
				cout << "3. Фильтрация пользователей" << endl;
				cout << "0. Отменить" << endl;
				switch (_getch()) {
				case '1':
					system("cls");
					m_sort(user, k);
					break;
				case '2':
					system("cls");
					m_find(user, k);
					break;
				case '3':
					system("cls");
					m_filtr(user, k);
					break;
				case '0':
					system("cls");
					delete[] user;
					break;
				default:
					system("cls");
					cout << "Такого пункта нет" << endl;
					system("pause");
					system("cls");
					goto r1;
				}
			}
					break;
			case '2': {
				ifstream bet("Bets.txt");
				ifstream fin("n_s.txt");
				if (!fin.is_open()) {
					cout << "На данный момент в системе нет ни одной ставки!" << endl;
					system("pause");
					system("cls");
					break;
				}
				int k; //переменная для количества ставок
				fin >> k;
				fin.close();
				Bets* bets = new Bets[k];
				for (int i = 0; i < k; i++) {
					bet >> bets[i].command_1;
					bet >> bets[i].command_2;
					bet >> bets[i].koef1;
					bet >> bets[i].koef2;
					bet >> bets[i].timeH;
					bet >> bets[i].timeM;
					bet >> bets[i].goals_1;
					bet >> bets[i].goals_2;
				}
				bet.close();
				printf("****************************************************************************\n");
				printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
				printf("****************************************************************************\n");
				for (int i = 0; i < k; i++) {
					cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
					printf("****************************************************************************\n");
				}
				cout << "Выберите нужный пункт" << endl;
				cout << "1. Отсортировать список" << endl;
				cout << "2. Поиск по параметру" << endl;
				cout << "3. Фильтрация" << endl;
				cout << "0. Выход" << endl;
				switch (_getch()) {
				case '1':
					system("cls");
					s_sort(bets, k);
					break;
				case '2':
					system("cls");
					s_find(bets, k);
					break;
				case '3':
					system("cls");
					s_filtr(bets, k);
					break;
				case '0':
					delete[] bets;
					system("cls");
					break;
				default:
					system("cls");
					cout << "Такого пункта нет" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
					break;
			case '0':
				system("cls");
				return 0;
			default:
				system("cls");
				cout << "Такого пункта нет" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		return 0;
	}


	int Enter() { //Обобщённая функция входа администратора
		return admin_enter();
	}

	int Register() { //обобщённая функция регистрации администратора
		ofstream fout("AdminCheck.txt");
		fout << "123456";
		fout.close();
		system("cls");
		cout << "Введите секретный пароль для администраторов" << endl;
		ifstream fin("AdminCheck.txt"); //открываем папку с нашим секретным паролем
		string checking; //переменная для сравнивания введённого секретного пароля с тем, который лежит в папке
		string checking_; //переменная, в которую мы внесём наш секретный пароль
		fin >> checking_;
		if (!fin.is_open()) {
			cout << "Ой, а пароля няма..." << endl;
		}
	rep1:
		cin >> checking; //просим будущего администратора ввести пароль
		if (checking_ != checking) {
			system("cls");
			cout << "Что ж, это было прекрасная попытка, желаете попытать удачи ещё раз?" << endl;
			cout << "1. Да" << endl;
			cout << "2. Нет" << endl;
			switch (_getch()) {
			case '1':
				system("cls");
				cout << "Введите секретный пароль администратора:" << endl;
				goto rep1;
				break;
			case '2':
				cout << "Мы так и знали, что вы не настоящий администратор" << endl << endl;
				system("pause");
				system("cls");
				break;
			default:
				system("pause");
				cout << "Очень сожалеем, но у вас нет другого выбора =)" << endl << endl;
				cout << "Введите секретный пароль администратора:" << endl;
			}
		}
		else {
			system("cls");
			cout << "Вам всё же удалось..." << endl;
			Sleep(1500);
			system("cls");
			cout << "Прекрасно, мы верим, что вы наш будущий администратор" << endl << endl;
			cout << "Теперь вас ждёт процесс придумывания логина и пароля для входа" << endl << endl;
			admin();

		}
		return 0;
	}

	int Del() { //Удаление ставок и пользователей
		system("cls");
		while (true) {
			cout << "Выберите нужный пункт" << endl;
			cout << "1. Удаление ставки" << endl;
			cout << "2. Удаление пользователя" << endl;
			cout << "0. Отменить" << endl;
			switch (_getch()) {
			case '1':
				DelStav();
				break;
			case '2':
				DelUser();
				break;
			case '0':
				system("cls");
				return 0;
			default:
				system("cls");
				cout << "Такой команды не существует, повторите ввод!" << endl;
			}
		}
		return 0;
	}

	int Edit() {
		while (true) {
			system("cls");
			cout << "Выберите нужный пункт" << endl;
			cout << "1. Редактирование пользователя" << endl;
			cout << "2. Редактирование ставок" << endl;
			cout << "0. Отмена" << endl;
			switch (_getch()) {
			case '1':
				EditUser();
				break;
			case '2':
				EditBet();
				break;
			case '0':
				system("cls");
				return 0;
			default:
				system("cls");
				cout << "Такой команды не существует, повторите ввод!" << endl;
				system("pause");
			}
		}
		return 0;
	}

	int SetBet() { //"создать" игру
		string command;
		string command1;
		double koef;
		double koef1;
		int time1;
		int time2;
		cout << "Введите название первой команды" << endl;
		cin >> command;
		system("cls");
		cout << "Введите название второй команды" << endl;
		cin >> command1;
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			system("cls");
			cout << "Введите коэффициент для расчёта выплат (на первую команду)" << endl;
			cin >> koef;
		} while (koef < 0 || koef > 10 || isalpha(koef) || !cin.good());
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			system("cls");
			cout << "Введите коэффициент для расчёта выплат (на вторую команду)" << endl;
			cin >> koef1;
		} while (koef1 < 0 || koef1 > 10 || isalpha(koef1) || !cin.good());
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			system("cls");
			cout << "Введите время начала игры (часы)" << endl;
			cin >> time1;
		} while (time1 > 24 || time1 <= 0 || !cin.good());
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Введите время начала игры (минуты)" << endl;
			cin >> time2;
			system("cls");
		} while (time2 > 59 || time2 < 1 || isalpha(time2) || !cin.good());
		Bets bet(command, command1, koef, koef1, time1, time2, 0, 0);
		cout << "Игра добавлена успешно!" << endl;
		return 0;
	}

	friend int menu_a(Administrator& adm);
	friend int admin_enter();
	friend class User;
	friend int admin();
};

int main() {
	SetConsoleCP(1251);
	setlocale(LC_ALL, "rus");
	menu();
	return 0;
}

int menu() { //головная функция, с которой стартует вся программа
	while (true) {
		cout << "Здравствуйте! Вас приветствует букмекерская контора \"Всё или ничего\"" << endl << endl;
		cout << "Пожалуйста, выберите метод входа/регистрации" << endl;
		cout << "1. Войти как пользователь" << endl;
		cout << "2. Войти как администратор" << endl;
		cout << "3. Зарегистрироваться как пользователь" << endl;
		cout << "4. Зарегистрироваться как администратор" << endl;
		cout << "0. Выйти из системы" << endl;
		switch (_getch()) {
		case '1': {
			Imain* ptr;
			User user;
			ptr = &user;
			if (ptr->Enter() == 1) {
			} //вызываем метод "вход" у юзера

			break;
		}
		case '2': {
			Imain* ptr;
			Administrator admin;
			ptr = &admin;
			if (ptr->Enter() == 1) {

			} //вызываем метод "вход" у админа

			break;
		}
		case '3': {
			Imain* ptr;
			User user;
			ptr = &user;
			ptr->Register(); //вызываем метод "регистрация" у юзера

			break;
		}
		case '4': {
			Imain* ptr;
			Administrator admin;
			ptr = &admin;
			ptr->Register(); //вызываем метод "регистрация" у администратора

			break;
		}
		case '0':
			return 0;
			break;
		default:
			system("cls");
			cout << "Такой команды не существует, повторите ввод!" << endl << endl << endl;
		}
	}
	return 0;
}

int admin() { //регистрация администратора
	Administrator admin;
	ifstream fin("Shifr.txt");
	int sdvig;
	fin >> sdvig;
	fin.close();
	char m = '0';//переменная для запоминания нажатой клавиши
	int i = 0; //Номер символа
	int l = 1; //начальный счётчик админов
	char pass[100];
	system("cls");
	cout << "Придумайте логин:" << endl;
res2:
	cin >> admin.login;
	if ((admin.login).length() > 21) {
		system("cls");
		cout << "Достигнуто максимальное количество символов! Введите не более 20" << endl;
		Sleep(3000);
		system("cls");
		cout << "Повторите ввод логина:" << endl;
		goto res2;
	}
	system("cls");
	cout << "Придумайте пароль (не более 20 символов):" << endl;
res3:
	i = 0;
	while (1) {
		m = _getch();
		if (m == '\n' || m == '\r') {
			pass[i] = '\0';

			break;
		}
		pass[i] = m;
		m = '*';
		cout << m;
		i++;
		if (i == 22) {
			system("cls");
			cout << "Достигнуто максимальное количество символов" << endl;
			Sleep(1000);
			system("cls");
			cout << "Повторите ввод пароля:\n" << endl;
			goto res3;
		}
	}
	admin.password = pass;
	i = 0;
	while (i < strlen(pass)) {
		admin.password[i] = admin.password[i] + sdvig;
		i++;
	}
	system("cls");
	cout << "Введите ваше имя: " << endl;
	cin >> admin.name;
	system("cls");
	cout << "Введите вашу фамилию: " << endl;
	cin >> admin.surname;
	system("cls");
	cout << "Введите ваше отчество: " << endl;
	cin >> admin.patronymic;
	system("cls");
	ofstream fout("Admins.txt", ios_base::app);
	fout << admin.login << "\n";
	fout << admin.password << "\n";
	fout << admin.name << "\n";
	fout << admin.surname << "\n";
	fout << admin.patronymic << "\n";
	system("cls");
	ofstream f("now.txt");
	f << admin.login << "\n";
	f << admin.password << "\n";
	f << admin.name << "\n";
	f << admin.surname << "\n";
	f << admin.patronymic << "\n";
	f.close();
	fout.close();
	ifstream fon("n_a.txt");
	int k;
	if (!fon.is_open()) {
		ofstream fout_t("n_a.txt");
		fout_t << 1;
		fout_t.close();
	}
	else {
		fon >> k;
		k++;
		ofstream fout("n_a.txt");
		fout << k;
		fout.close();
		fin.close();
	}
	return 0;
}

int user() { //регистрация пользователя
	User us;
	ifstream fin("Shifr.txt");
	int sdvig;
	fin >> sdvig;
	fin.close();
	system("cls");
	char m = '0';//переменная для запоминания нажатой клавиши
	int i = 0; //Номер символа
	int l = 1; //начальный счётчик админов
	char pass[100];
	cout << "Придумайте логин:" << endl;
res2:
	cin >> us.login;
	if ((us.login).length() > 21) {
		system("cls");
		cout << "Достигнуто максимальное количество символов! Введите не более 20" << endl;
		Sleep(3000);
		system("cls");
		cout << "Повторите ввод логина:" << endl;
		goto res2;
	}
	system("cls");
	cout << "Придумайте пароль (не более 20 символов):" << endl;
res3:
	i = 0;
	while (1) {
		m = _getch();
		if (m == '\n' || m == '\r') {
			pass[i] = '\0';

			break;
		}
		pass[i] = m;
		m = '*';
		cout << m;
		i++;
		if (i == 22) {
			system("cls");
			cout << "Достигнуто максимальное количество символов" << endl;
			Sleep(1000);
			system("cls");
			cout << "Повторите ввод пароля:\n" << endl;
			goto res3;
		}
	}
	us.password = pass;
	i = 0;
	while (i < strlen(pass)) {
		us.password[i] = us.password[i] + sdvig;
		i++;
	}
	system("cls");
	cout << "Введите ваше имя: " << endl;
	cin >> us.name;
	system("cls");
	cout << "Введите вашу фамилию: " << endl;
	cin >> us.surname;
	system("cls");
	cout << "Введите ваше отчество: " << endl;
	cin >> us.patronymic;
	system("cls");
	ofstream fout("Users.txt", ios_base::app);
	fout << us.login << "\n";
	fout << us.password << "\n";
	fout << us.name << "\n";
	fout << us.surname << "\n";
	fout << us.patronymic << "\n";
	fout << us.balance << "\n";
	system("cls");
	fout.close();
	ifstream fon("n_u.txt");
	int k;
	if (!fon.is_open()) {
		ofstream fout_t("n_u.txt");
		fout_t << 1;
		fout_t.close();
	}
	else {
		fon >> k;
		k++;
		ofstream fout("n_u.txt");
		fout << k;
		fout.close();
	}
	fon.close();
	return 0;
}

int user_enter() { //вход для пользователя
	ifstream fin("n_u.txt");
	int k; //переменная для подсчёта количества юзеров
	string user_l; //переменная для сравнивания введённого логина
	char userPass[100];
	string userPassword; //переменная для сравнивания введённого пароля
	int l = 0; //идентификатор правильности ввода логина/пароля
	int b; //перменная для запоминания номера нужного юзера
	char m;
	if (!fin.is_open()) {
		cout << "В системе не зарегестрировано ни одного пользователя!" << endl;
		system("pause");
		system("cls");
		return 1;
	}
	else fin >> k;
	User* us = new User[k];
	int i = 0;
	ifstream fonk;
	fonk.open("Users.txt");
	while (i < k) {
		fonk >> us[i].login;
		fonk >> us[i].password;
		fonk >> us[i].name;
		fonk >> us[i].surname;
		fonk >> us[i].patronymic;
		fonk >> us[i].balance;
		i++;
	}
	system("cls");
	cout << "Введите свой логин:\n";
r1:
	cin >> user_l;
	for (i = 0; i < k; i++) {
		if ((us[i].login).compare(user_l) == 0) {
			b = i;
			system("cls");
			cout << "Вы ввели верный логин!" << endl;
			l++;
		res3:
			cout << "Введите пароль: ";
			i = 0;
			while (1) {
				m = _getch();
				if (m == '\n' || m == '\r') {
					userPass[i] = '\0';
					break;
				}
				userPass[i] = m;
				m = '*';
				printf("%c", m);
				i++;
				if (i == 22) {
					system("cls");
					printf("Достигнуто максимальное количество символов\n");
					Sleep(1000);
					system("cls");
					printf("Повторите ввод пароля:\n");
					goto res3;
				}
			}
			i = 0;
			ifstream fin("Shifr.txt");
			int sdvig;
			fin >> sdvig;
			fin.close();
			userPassword = userPass;
			while (i < (us[b].password).length()) {
				us[b].password[i] = us[b].password[i] - sdvig;
				i++;
			}
			if (us[b].password.compare(userPassword) == 0) {
				cout << "Вход осуществлён успешно!" << endl;
				User user;
				user.login = us[b].login;
				user.password = us[b].password;
				user.name = us[b].name;
				user.surname = us[b].surname;
				user.patronymic = us[b].patronymic;
				user.balance = us[b].balance;
				delete[] us;
				menu_u(user);
				return b;
			}
			else {
				cout << "\n";
				cout << "Пароль введён неправильно!" << endl;
				i = 0;
				while (i < (us[b].password).length()) {
					us[b].password[i] = us[b].password[i] + sdvig;
					i++;
				}
				system("pause");
				system("cls");
				goto res3;
			}
			break;
		}
	}
	if (l == 0) {
		system("cls");
		cout << "Вы ввели неверный логин, повторите ещё раз:" << endl;
		goto r1;
	}

	return 0;
}

int admin_enter() { //вход для адимнистратора
	ifstream fin("n_a.txt");
	int k; //переменная для подсчёта количества админов
	string admin_l; //переменная для сравнивания введённого логина
	char adminPass[100];
	string adminPassword; //переменная для сравнивания введённого пароля
	int l = 0; //идентификатор правильности ввода логина/пароля
	int b; //перменная для запоминания номера нужного админа
	char m;
	system("cls");
	if (!fin.is_open()) {
		cout << "В системе не зарегестрировано ни одного администратора!" << endl;
		system("pause");
		system("cls");
		return 1;
	}
	else fin >> k;
	Administrator* adm = new Administrator[k];
	int i = 0;
	ifstream fonk;
	fonk.open("Admins.txt");
	while (i < k) {
		fonk >> adm[i].login;
		fonk >> adm[i].password;
		fonk >> adm[i].name;
		fonk >> adm[i].surname;
		fonk >> adm[i].patronymic;
		i++;
	}
	cout << "Введите свой логин:\n";
r1:
	cin >> admin_l;
	for (i = 0; i < k; i++) {
		if ((adm[i].login).compare(admin_l) == 0) {
			b = i;
			cout << "Вы ввели верный логин!" << endl;
			l++;
		res3:
			cout << "Введите пароль: ";
			i = 0;
			while (1) {
				m = _getch();
				if (m == '\n' || m == '\r') {
					adminPass[i] = '\0';
					break;
				}
				adminPass[i] = m;
				m = '*';
				printf("%c", m);
				i++;
				if (i == 22) {
					system("cls");
					printf("Достигнуто максимальное количество символов\n");
					Sleep(1000);
					system("cls");
					printf("Повторите ввод пароля:\n");
					goto res3;
				}
			}
			i = 0;
			ifstream fin("Shifr.txt");
			int sdvig;
			fin >> sdvig;
			fin.close();
			adminPassword = adminPass;
			while (i < (adm[b].password).length()) {
				adm[b].password[i] = adm[b].password[i] - sdvig;
				i++;
			}
			if (adm[b].password.compare(adminPassword) == 0) {
				Administrator admin;
				admin.login = adm[b].login;
				admin.password = adm[b].password;
				admin.name = adm[b].name;
				admin.surname = adm[b].surname;
				admin.patronymic = adm[b].patronymic;
				delete[] adm;
				menu_a(admin);
				return b;
			}
			else {
				cout << "\n";
				cout << "Пароль введён неправильно!" << endl;
				i = 0;
				while (i < (adm[b].password).length()) {
					adm[b].password[i] = adm[b].password[i] + sdvig;
					i++;
				}
				system("pause");
				system("cls");
				goto res3;
			}
			break;
		}
	}
	if (l == 0) {
		system("cls");
		cout << "Вы ввели неверный логин, повторите ещё раз:" << endl;
		goto r1;
	}

	return 0;
}

int menu_u(User& us) {
	system("cls");
	while (true) {
		cout << "Добро пожаловать," << us.name << " " << us.patronymic << "!";
		cout << "\t\tТекущий баланс:	 " << us.balance << endl << endl;
		cout << "Выберите нужное Вам действие:\n";
		cout << "1. Сделать ставку" << endl;
		cout << "2. Пополнить баланс" << endl;
		cout << "3. Вывести средства" << endl;
		cout << "0. Выход из учётной записи" << endl;
		switch (_getch()) {
		case '1':
			us.PlaceBet();
			break;
		case '2':
			system("cls");
			us.AddBalance(); //+- 
			break;
		case '3':
			us.Out();
			break;
		case '0':
			system("cls");
			return 0;
		default:
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			break;
		}
	}
	return 0;
}

int menu_a(Administrator& adm) {
	while (true) {
		system("cls");
		cout << "Добро пожаловать," << adm.name << " " << adm.patronymic << "!";
		cout << "Выберите нужное Вам действие:\n";
		cout << "1. Создать ставку" << endl;
		cout << "2. Просмотр информации о ставках и пользователях" << endl;
		cout << "3. Удаление" << endl;
		cout << "4. Редактирование" << endl;
		cout << "0. Выход из учётной записи" << endl;
		switch (_getch()) {
		case '1':
			adm.SetBet();
			break;
		case '2':
			adm.Show();
			break;
		case '3':
			adm.Del();
			break;
		case '4':
			adm.Edit();
			break;
		case '0':
			system("cls");
			return 0;
		default:
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			break;
		}
	}
	return 0;
}

int Game() {
	system("cls");
	for (int i = 10; i >= 1; i--) {
		system("cls");
		cout << "Команды играют" << endl;
		cout << "До конца матча осталось " << i << " сек." << endl;
		Sleep(1000);
	}
	srand(time(NULL));
	int random = 1 + rand() % 2;
	return random;
}

int m_sort(User* us, int k) {
	while (true) {
		User user;
		cout << "Выберите тип сортировки: " << endl;
		cout << "1. Сортировать по имени" << endl;
		cout << "2. Сортировать по фамилиии" << endl;
		cout << "3. Сортировать по отчеству" << endl;
		cout << "0. Отменить" << endl;
		switch (_getch()) {
		case '1': {
			system("cls");
			int j = 0;
			int i;
			while (j < k) {
				i = 0;
				while ((j + i) < k) {
					if (us[j].name.compare(us[j + i].name) > 0) {
						user = us[j];
						us[j] = us[j + i];
						us[j + i] = user;
					}
					i++;
				}
				j++;
			}
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			i = 0;
			while (i < k) {
				cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
				printf("********************************************************************************\n");
				i++;
			}
			system("pause");
		}
				break;
		case '2': {
			system("cls");
			int j = 0;
			int i;
			while (j < k) {
				i = 0;
				while ((j + i) < k) {
					if (us[j].surname.compare(us[j + i].surname) > 0) {
						user = us[j];
						us[j] = us[j + i];
						us[j + i] = user;
					}
					i++;
				}
				j++;
			}
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			i = 0;
			while (i < k) {
				cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
				printf("********************************************************************************\n");
				i++;
			}
			system("pause");
		}
				break;
		case '3': {
			system("cls");
			int j = 0;
			int i;
			while (j < k) {
				i = 0;
				while ((j + i) < k) {
					if (us[j].patronymic.compare(us[j + i].patronymic) > 0) {
						user = us[j];
						us[j] = us[j + i];
						us[j + i] = user;
					}
					i++;
				}
				j++;
			}
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			i = 0;
			while (i < k) {
				cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
				printf("********************************************************************************\n");
				i++;
			}
			system("pause");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int m_filtr(User* us, int k) {
	while (true) {
		cout << "Фильтрация будет осуществлена по личному счёту пользователей" << endl;
		cout << "1. Выполнить фильтрацию" << endl;
		cout << "0. Отменить" << endl;
		switch (_getch()) {
		case '1': {
			float min, max;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите нижний порог счёта" << endl;
				cin >> min;
				cout << "Введите верхний порог счёта" << endl;
				cin >> max;
				system("cls");
			} while (min == max || max < min || max < 0 || min < 0 || isalpha(min) || isalpha(max) || !cin.good());
			int flag = 0;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (us[i].balance >= min && us[i].balance <= max) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\nНе найдено пользователей с таким параметром!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int m_find(User* us, int k) {
	while (true) {
		cout << "Выберите нужный параметр поиска:" << endl;
		cout << "1. Поиск по логину" << endl;
		cout << "2. Поиск по имени" << endl;
		cout << "3. Поиск по фамилии" << endl;
		cout << "4. Поиск по отчеству" << endl;
		cout << "0. Отменить" << endl;
		switch (_getch()) {
		case '1': {
			system("cls");
			string log;
			int flag = 0;
			cout << "Введите логин" << endl;
			cin >> log;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (log.compare(us[i].login) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\nНе найдено пользователей с таким параметром!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '2': {
			system("cls");
			string name;
			int flag = 0;
			cout << "Введите имя" << endl;
			cin >> name;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (name.compare(us[i].name) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\nНе найдено пользователей с таким параметром!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '3': {
			system("cls");
			string fam;
			int flag = 0;
			cout << "Введите фамилию пользователя" << endl;
			cin >> fam;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (fam.compare(us[i].surname) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\nНе найдено пользователей с таким параметром!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '4': {
			system("cls");
			string patr;
			int flag = 0;
			cout << "Введите отчество" << endl;
			cin >> patr;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (patr.compare(us[i].patronymic) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\nНе найдено пользователей с таким параметром!" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}

int s_sort(Bets* bets, int k) {
	while (true) {
		Bets bet;
		cout << "Выберите тип сортировки: " << endl;
		cout << "1. Сортировать по алфавиту 1 команды" << endl;
		cout << "2. Сортировать по алфавиту 2 команды" << endl;
		cout << "3. Сортировать по коэффициентам 1 команды" << endl;
		cout << "3. Сортировать по коэффициентам 2 команды" << endl;
		cout << "0. Отменить" << endl;
		switch (_getch()) {
		case '1': {
			system("cls");
			int j = 0;
			int i;
			while (j < k) {
				i = 0;
				while ((j + i) < k) {
					if (bets[j].command_1.compare(bets[j + i].command_1) > 0) {
						bet = bets[j];
						bets[j] = bets[j + i];
						bets[j + i] = bet;
					}
					i++;
				}
				j++;
			}
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			i = 0;
			while (i < k) {
				cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
				printf("****************************************************************************\n");
				i++;
			}
			system("pause");
		}
				break;
		case '2': {
			system("cls");
			int j = 0;
			int i;
			while (j < k) {
				i = 0;
				while ((j + i) < k) {
					if (bets[j].command_2.compare(bets[j + i].command_2) > 0) {
						bet = bets[j];
						bets[j] = bets[j + i];
						bets[j + i] = bet;
					}
					i++;
				}
				j++;
			}
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			i = 0;
			while (i < k) {
				cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
				printf("****************************************************************************\n");
				i++;
			}
			system("pause");
		}
				break;
		case '3': {
			system("cls");
			int j = 0;
			int i;
			while (j < k) {
				i = 0;
				while ((j + i) < k) {
					if (bets[j].koef1 < bets[j + i].koef1) {
						bet = bets[j];
						bets[j] = bets[j + i];
						bets[j + i] = bet;
					}
					i++;
				}
				j++;
			}
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			i = 0;
			while (i < k) {
				cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
				printf("****************************************************************************\n");
				i++;
			}
			system("pause");
		}
				break;
		case '4': {
			system("cls");
			int j = 0;
			int i;
			while (j < k) {
				i = 0;
				while ((j + i) < k) {
					if (bets[j].koef2 < bets[j + i].koef2) {
						bet = bets[j];
						bets[j] = bets[j + i];
						bets[j + i] = bet;
					}
					i++;
				}
				j++;
			}
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			i = 0;
			while (i < k) {
				cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
				printf("****************************************************************************\n");
				i++;
			}
			system("pause");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int s_find(Bets* bets, int k) {
	while (true) {
		Bets bet;
		cout << "Выберите параметр поиска: " << endl;
		cout << "1. Поиск 1 команды" << endl;
		cout << "2. Поиск 2 команды" << endl;
		cout << "0. Отменить" << endl;
		switch (_getch()) {
		case '1': {
			system("cls");
			string com;
			int flag = 0;
			cout << "Введите название команды: " << endl;
			cin >> com;
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			int i = 0;
			while (i < k) {
				if (com.compare(bets[i].command_1) == 0) {
					cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
					printf("****************************************************************************\n");
					flag++;
				}
				i++;
			}
			if (flag == 0) cout << "Такой команды нет(\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '2': {
			system("cls");
			string com;
			int flag = 0;
			cout << "Введите название команды: " << endl;
			cin >> com;
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			int i = 0;
			while (i < k) {
				if (com.compare(bets[i].command_2) == 0) {
					cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
					printf("****************************************************************************\n");
					flag++;
				}
				i++;
			}
			if (flag == 0) cout << "Такой команды нет(\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int s_filtr(Bets* bets, int k) {
	while (true) {
		cout << "Выберите параметр фильтрации:" << endl;
		cout << "1. Коэффициенты первых команд" << endl;
		cout << "2. Коэффициенты вторых команд" << endl;
		switch (_getch()) {
		case '1': {
			float min, max;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите нижний порог коэффициентов" << endl;
				cin >> min;
				cout << "Введите верхний порог коэффициентов" << endl;
				cin >> max;
				system("cls");
			} while (min == max || max < min || max < 0 || min < 0 || isalpha(min) || isalpha(max) || !cin.good());
			int flag = 0;
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			int i = 0;
			while (i < k) {
				if (bets[i].koef1 >= min && bets[i].koef1 <= max) {
					cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
					printf("****************************************************************************\n");
					flag++;
				}
				i++;
			}
			if (flag == 0) cout << "Нет коэффициентов попадающих под диапазон\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '2': {
			float min, max;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите нижний порог коэффициентов" << endl;
				cin >> min;
				cout << "Введите верхний порог коэффициентов" << endl;
				cin >> max;
				system("cls");
			} while (min == max || max < min || max < 0 || min < 0 || isalpha(min) || isalpha(max) || !cin.good());
			int flag = 0;
			printf("****************************************************************************\n");
			printf("|    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("****************************************************************************\n");
			int i = 0;
			while (i < k) {
				if (bets[i].koef1 >= min && bets[i].koef1 <= max) {
					cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
					printf("****************************************************************************\n");
					flag++;
				}
				i++;
			}
			if (flag == 0) cout << "Такой команды нет(\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
		}
	}
	return 0;
}

int DelUser() {
	system("cls");
	ifstream nu("n_u.txt");
	int k;
	int i = 0;
	ifstream us("Users.txt");
	if (!nu.is_open()) {
		cout << "В системе не зарегестрировано ни одного пользователя" << endl;
		system("pause");
		system("cls");
		return 0;
	}
	else nu >> k;
	User* user = new User[k];
	while (i < k) {
		us >> user[i].login;
		us >> user[i].password;
		us >> user[i].name;
		us >> user[i].surname;
		us >> user[i].patronymic;
		us >> user[i].balance;
		i++;
	}
	us.close();
	printf("*************************************************************************************\n");
	printf("| №  |  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
	printf("*************************************************************************************\n");
	i = 0;
	while (i < k) {
		cout << "|" << setw(4) << i << "|" << setw(10) << user[i].login << "|" << setw(11) << user[i].name << "|" << setw(21) << user[i].surname << "|" << setw(20) << user[i].patronymic << "|" << setw(12) << user[i].balance << "|" << endl;
		printf("*************************************************************************************\n");
		i++;
	}
	int num;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Выберите номер пользователя, которого хотите удалить" << endl;
		cin >> num;
		system("cls");
	} while (num >= k || num < 0 || isalpha(num));
	ofstream fink;
	fink.open("Users.txt");
	for (int i = 0; i < k; i++) {
		if (i != num) {
			fink << user[i].login << "\n";
			fink << user[i].password << "\n";
			fink << user[i].name << "\n";
			fink << user[i].surname << "\n";
			fink << user[i].patronymic << "\n";
			fink << user[i].balance << "\n";
		}
	}
	k--;
	ofstream bald("n_u.txt");
	bald << k;
	fink.close();
	delete[] user;
	return 0;
}

int DelStav() {
	ifstream bet("Bets.txt");
	ifstream fin("n_s.txt");
	if (!fin.is_open()) {
		cout << "На данный момент в системе нет ни одной ставки!" << endl;
		system("pause");
		system("cls");
		return 0;
	}
	int k; //переменная для количества ставок
	fin >> k;
	fin.close();
	Bets* bets = new Bets[k];
	for (int i = 0; i < k; i++) {
		bet >> bets[i].command_1;
		bet >> bets[i].command_2;
		bet >> bets[i].koef1;
		bet >> bets[i].koef2;
		bet >> bets[i].timeH;
		bet >> bets[i].timeM;
		bet >> bets[i].goals_1;
		bet >> bets[i].goals_2;
	}
	bet.close();
	printf("**********************************************************************************\n");
	printf("|  №  |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
	printf("**********************************************************************************\n");
	for (int i = 0; i < k; i++) {
		cout << "|" << setw(5) << i << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
		printf("****************************************************************************\n");
	}
	int num;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Выберите номер ставки, которую хотите удалить" << endl;
		cin >> num;
		system("cls");
	} while (num >= k || num < 0 || isalpha(num));
	ofstream bot("Bets.txt");
	for (int i = 0; i < k; i++) {
		if (i != num) {
			bot << bets[i].command_1;
			bot << bets[i].command_2;
			bot << bets[i].koef1;
			bot << bets[i].koef2;
			bot << bets[i].timeH;
			bot << bets[i].timeM;
			bot << bets[i].goals_1;
			bot << bets[i].goals_2;
		}
	}
	bot.close();
	k--;
	ofstream kuk("n_s.txt");
	kuk << k;
	kuk.close();
	delete[] bets;
	return 0;
}

int EditUser() {
	system("cls");
	ifstream nu("n_u.txt");
	int k;
	int i = 0;
	ifstream us("Users.txt");
	if (!nu.is_open()) {
		cout << "В системе не зарегестрировано ни одного пользователя" << endl;
		system("pause");
		system("cls");
		return 0;
	}
	else nu >> k;
	nu.close();
	User* user = new User[k];
	while (i < k) {
		us >> user[i].login;
		us >> user[i].password;
		us >> user[i].name;
		us >> user[i].surname;
		us >> user[i].patronymic;
		us >> user[i].balance;
		i++;
	}
	us.close();
us1:
	printf("*************************************************************************************\n");
	printf("| №  |  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
	printf("*************************************************************************************\n");
	i = 0;
	while (i < k) {
		cout << "|" << setw(4) << i << "|" << setw(10) << user[i].login << "|" << setw(11) << user[i].name << "|" << setw(21) << user[i].surname << "|" << setw(20) << user[i].patronymic << "|" << setw(12) << user[i].balance << "|" << endl;
		printf("*************************************************************************************\n");
		i++;
	}
	int num;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Выберите номер пользователя, параметры которого вы хотите отредактировать" << endl;
		cin >> num;
		system("cls");
	} while (num >= k || num < 0 || isalpha(num) || !cin.good());
	while (true) {
		system("cls");
		cout << "Выберите нужный параметр редактирования:" << endl;
		cout << "1. Редактировать имя" << endl;
		cout << "2. Редактировать фамилию" << endl;
		cout << "3. Редактировать отчество" << endl;
		cout << "4. Редактировать баланс" << endl;
		cout << "5. Выбрать другого пользователя" << endl;
		cout << "0. Выход" << endl;
		switch (_getch()) {
		case '1': {
			string name;
			printf("*************************************************************************************\n");
			printf("| №  |  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			cout << "Введите новое имя пользователя" << endl;
			cin >> name;
			user[num].name = name;
		}
				break;
		case '2': {
			string sname;
			printf("*************************************************************************************\n");
			printf("| №  |  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			cout << "Введите новую фамилию пользователя" << endl;
			cin >> sname;
			user[num].surname = sname;
		}
				break;
		case '3': {
			string pname;
			printf("*************************************************************************************\n");
			printf("| №  |  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			cout << "Введите новое отчество пользователя" << endl;
			cin >> pname;
			user[num].patronymic = pname;
		}
				break;
		case '4': {
			float bal;
			printf("*************************************************************************************\n");
			printf("| №  |  Логин   |    Имя    |       Фамилия       |      Отчество      |   Баланс   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите откорректированный баланс пользователя" << endl;
				cin >> bal;
			} while (bal < 0 || isalpha(bal) || !cin.good());
			user[num].balance = bal;
		}
				break;
		case '5': {
			system("cls");
			ofstream fink;
			fink.open("Users.txt");
			for (int i = 0; i < k; i++) {
				fink << user[i].login << "\n";
				fink << user[i].password << "\n";
				fink << user[i].name << "\n";
				fink << user[i].surname << "\n";
				fink << user[i].patronymic << "\n";
				fink << user[i].balance << "\n";
			}
			fink.close();
		}
				goto us1;
		case '0': {
			ofstream funk;
			funk.open("Users.txt");
			for (int i = 0; i < k; i++) {
				funk << user[i].login << "\n";
				funk << user[i].password << "\n";
				funk << user[i].name << "\n";
				funk << user[i].surname << "\n";
				funk << user[i].patronymic << "\n";
				funk << user[i].balance << "\n";
			}
			funk.close();
		}
				delete[] user;
				system("cls");
				return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
		}
	}
	return 0;
}

int EditBet() {
	ifstream bet("Bets.txt");
	ifstream fin("n_s.txt");
	if (!fin.is_open()) {
		cout << "На данный момент в системе нет ни одной ставки!" << endl;
		system("pause");
		system("cls");
		return 0;
	}
	int k; //переменная для количества ставок
	fin >> k;
	fin.close();
	Bets* bets = new Bets[k];
	for (int i = 0; i < k; i++) {
		bet >> bets[i].command_1;
		bet >> bets[i].command_2;
		bet >> bets[i].koef1;
		bet >> bets[i].koef2;
		bet >> bets[i].timeH;
		bet >> bets[i].timeM;
		bet >> bets[i].goals_1;
		bet >> bets[i].goals_2;
	}
	bet.close();
st1:
	printf("**********************************************************************************\n");
	printf("|  №  |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
	printf("**********************************************************************************\n");
	for (int i = 0; i < k; i++) {
		cout << "|" << setw(5) << i << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
		printf("****************************************************************************\n");
	}
	int num;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Выберите номер ставки, которую хотите отредактировать" << endl;
		cin >> num;
		system("cls");
	} while (num >= k || num < 0 || isalpha(num) || !cin.good());
	while (true) {
		cout << "Выберите параметр, который хотите отредактировать" << endl;
		cout << "1. Редактировать название первой комнады" << endl;
		cout << "2. Редактировать название второй комнады" << endl;
		cout << "3. Редактировать коэффициент первой комнады" << endl;
		cout << "4. Редактировать коэффициент второй комнады" << endl;
		cout << "5. Редактировать время начала игры" << endl;
		cout << "6. Выбрать другую ставку для редактирования" << endl;
		cout << "0. Выход" << endl;
		switch (_getch()) {
		case '1': {
			string command1;
			printf("**********************************************************************************\n");
			printf("|  №  |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			cout << "Введите новое название первой команды" << endl;
			cin >> command1;
			bets[num].command_1 = command1;
		}
				break;
		case '2': {
			string command2;
			printf("**********************************************************************************\n");
			printf("|  №  |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			cout << "Введите новое название второй команды" << endl;
			cin >> command2;
			bets[num].command_2 = command2;
		}
				break;
		case '3': {
			float koef;
			printf("**********************************************************************************\n");
			printf("|  №  |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите новый коэффициент первой команды" << endl;
				cin >> koef;
			} while (koef < 0 || !cin.good() || isalpha(koef));
			bets[num].koef1 = koef;
		}
				break;
		case '4': {
			float koef;
			printf("**********************************************************************************\n");
			printf("|  №  |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите новый коэффициент второй команды" << endl;
				cin >> koef;
			} while (koef < 0 || !cin.good() || isalpha(koef));
			bets[num].koef2 = koef;
		}
				break;
		case '5': {
			int hours;
			int min;
			printf("**********************************************************************************\n");
			printf("|  №  |    Команда 1    |    Команда 2   | Коэф. 1 | Коэф. 2 | Счёт | Время игры |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите новое время начала (в часах)" << endl;
				cin >> hours;
			} while (hours < 0 || hours > 24 || !cin.good() || isalpha(hours));
			bets[num].timeH = hours;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введите новое время начала (в минутах)" << endl;
				cin >> min;
			} while (min < 1 || min > 59 || !cin.good() || isalpha(min));
			bets[num].timeM = min;
		}
				break;
		case '6': {
			system("cls");
			ofstream bot("Bets.txt");
			for (int i = 0; i < k; i++) {
				bot << bets[i].command_1;
				bot << bets[i].command_2;
				bot << bets[i].koef1;
				bot << bets[i].koef2;
				bot << bets[i].timeH;
				bot << bets[i].timeM;
				bot << bets[i].goals_1;
				bot << bets[i].goals_2;
			}
			bot.close();
			goto st1;
		}
				break;
		case '0': {
			system("cls");
			ofstream bit("Bets.txt");
			for (int i = 0; i < k; i++) {
				bit << bets[i].command_1;
				bit << bets[i].command_2;
				bit << bets[i].koef1;
				bit << bets[i].koef2;
				bit << bets[i].timeH;
				bit << bets[i].timeM;
				bit << bets[i].goals_1;
				bit << bets[i].goals_2;
			}
			bit.close();
			delete[] bets;
		}
				return 0;
		default:
			system("cls");
			cout << "Такой команды не существует, выберите другой пункт!" << endl;
			system("pause");
		}
	}
	return 0;
}
