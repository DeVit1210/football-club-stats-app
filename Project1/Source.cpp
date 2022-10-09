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

int menu_a(Administrator& adm); //���� �������������� �� ����� �������������
int menu(); //�������� ����, �������, � ������� ���������� ����������
int menu_u(User& us); //���� ������������ �� ����� �����������
int admin(); //����������� ��������������
int admin_enter(); //���� �������������� 
int m_sort(User* us, int k); //���������� ���������� �������������
int m_filtr(User* us, int k); //���������� ���������� �������������
int m_find(User* us, int k); //����� ������������� �� ����������
int s_sort(Bets* bets, int k);  //���������� ������� ���������� ������
int s_find(Bets* bets, int k); //����� ������ �� ����������
int s_filtr(Bets* bets, int k); //���������� ������ �� �������������
int user(); //����������� ������������
int user_enter(); //���� ������������
int Game(); //�������� ���� ������
int DelUser(); //�������� ������������
int DelStav(); //�������� ������
int EditUser(); //�������������� ���������� ������������
int EditBet(); //�������������� ���������� ������

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
	string command_1; //�������� 1 �������
	string command_2; //�������� 2 �������
	double koef1; //����������� 1 �������
	double koef2; //����������� 2 �������
	int timeH; //����� ������ ���� � �����
	int timeM; //����� ������ ���� � �������
	int goals_1; //���� 1 �������
	int goals_2; //���� 2 �������
public:
	Bets() {

	}
	Bets(string com1, string com2, double k, double k1, int t1, int t2, int g1, int g2) //����������� � �����������, ������ ����
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
	int Enter() { //���������� ������� ����������������� �����
		cout << "����� ���������� � ���� ������������ ������� \" �� ��� ������ \"" << endl;
		return user_enter();
	}

	int Register() { //���������� ������� ����������� ������������
		ifstream fin("Users.txt");
		cout << "������� ������� �����!" << endl;
		cout << "������� �����������!" << endl;
		user();
		return 0;
	}

	int AddBalance() { //������� ���������� ������� �����������
		ifstream fonk;
		ifstream cifra;
		int k;
		int b = 0;
		string card1; //����� �����
		int card2_m = 0; //����� �����
		int card2_y = 0; //��� �����
		string card3; //CVV-���
		string tel; //��������� �������
		double sum; //����� ��� ������
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
			cout << "�������� ��� ������:" << endl;
			cout << "1. ������" << endl;
			cout << "2. ��������� �������" << endl;
			cout << "0. �������� ��������" << endl;
			switch (_getch()) {
			case '1':
				do {
					cout << "������� 16 ���� � ������� ������� �����" << endl;
					cin >> card1;
					system("cls");
				} while (card1.length() < 16 || card1.length() > 16);
				do {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "������� ���� �������� ����� � �������: �� ��" << endl;
					scanf_s("%d%d", &card2_m, &card2_y);
					system("cls");
				} while (card2_y > 2021 || card2_y < 2017 || card2_m >12 || card2_m < 1 || isalpha(card2_m) || isalpha(card2_y));
				do {
					cout << "������� �������� ��� (CVV) � ��������� ������� �����" << endl;
					cin >> card3;
					system("cls");
				} while (card3.length() < 3 || card3.length() > 3);
			l1:
				cout << "������� ����� ��� ���������� (��� - 1 000, ���� - 100 000)" << endl;
				cin >> sum;
				if (sum < 1000 || sum > 100000) {
					cout << "������, ������������ �����" << endl;
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
					cout << "������� ����� ���������� �������� (+375...)" << endl;
					cin >> tel;
					system("cls");
				} while (tel.length() < 12 && tel[0] != '+' && tel[1] != '3' && tel[2] != '7' && tel[3] != '5');
			l3:
				cout << "������� ����� ��� ���������� (��� - 1 000, ���� - 100 000)" << endl;
				cin >> sum;
				if (sum < 1000 || sum > 100000 || sum > this->balance || isalpha(sum)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "������, ������������ �����" << endl;
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
				cout << "�������� �������, ��������� ��� ���!";
			}
		}
		return 0;
	}

	int Show() {
		return 0;
	}

	int Out() { //������� ������ ������� �������������
		ifstream fonk;
		ifstream cifra;
		int k;
		int b = 0;
		string card1; //����� �����
		int card2_m = 0; //����� �����
		int card2_y = 0; //��� �����
		string card3; //CVV-���
		string tel; //��������� �������
		double sum; //����� ��� ������
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
			cout << "�������� ������ ������:" << endl;
			cout << "1. �� �����" << endl;
			cout << "2. �� ��������� �������" << endl;
			cout << "0. �������� ��������" << endl;
			switch (_getch()) {
			case '1':
				do {
					cout << "������� 16 ���� � ������� ������� �����" << endl;
					cin >> card1;
					system("cls");
				} while (card1.length() < 16 || card1.length() > 16);
				do {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "������� ���� �������� ����� � �������: �� ��" << endl;
					scanf_s("%d%d", &card2_m, &card2_y);
					system("cls");
				} while (card2_y > 2021 || card2_y < 2017 || card2_m >12 || card2_m < 1 || isalpha(card2_m) || isalpha(card2_y));
				do {
					cout << "������� �������� ��� (CVV) � ��������� ������� �����" << endl;
					cin >> card3;
					system("cls");
				} while (card3.length() < 3 || card3.length() > 3);
			l1:
				cout << "������� ����� ��� ������ (��� - 10 000, ���� - 1 000 000)" << endl;
				cin >> sum;
				if (sum < 10000 || sum > 1000000 || sum > this->balance || isalpha(sum)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "������, ������������ �����" << endl;
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
					cout << "������� ����� ���������� �������� (+375...)" << endl;
					cin >> tel;
					system("cls");
				} while (tel.length() < 12 && tel[0] != '+' && tel[1] != '3' && tel[2] != '7' && tel[3] != '5');
			l2:
				cout << "������� ����� ��� ������ (��� - 10 000, ���� - 1 000 000)" << endl;
				cin >> sum;
				if (sum < 1000 || sum > 100000 || sum > this->balance || isalpha(sum)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "������, ������������ �����" << endl;
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
				cout << "�������� �������, ��������� ��� ���!";
			}
		}
		return 0;

	}

	int PlaceBet() {
		char o;
		ifstream fun("n_u.txt");
		int u; //���������� ��� �������� ���������� ������
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
		int z; //���������� ��� ����������� �����;
		while (i < u) {
			if (this->login == us[i].login && this->name == us[i].name && this->surname == us[i].surname) {
				z = i;
				break;
			}
		}
		double stavka; //���������� ��������, ������� �������� ������������
		fonk.close();
		while (true) {
			ifstream bet("Bets.txt");
			ifstream fin("n_s.txt");
			if (!fin.is_open()) {
				cout << "�� ������ ������ � ������� ��� �� ����� ������!" << endl;
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
			printf("| � |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
			printf("********************************************************************************\n");
			for (int i = 0; i < k; i++) {
				cout << "|" << setw(3) << i << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
				printf("********************************************************************************\n");
			}
			char g;
			int b;
			cout << "1. ������� ������" << endl;
			cout << "2. ��������" << endl;
			switch (_getch()) {
			case '1':
				cout << "�������� ����� ����, �� ������� ������ ������� ������:" << endl;
				g = _getch();
				b = g - '0';
				if (b >= k) {
					system("cls");
					cout << "����� ������ �� ����������!" << endl;
					system("pause");
					system("cls");
					break;
				}
			l2:
				system("cls");
				printf("****************************************************************************\n");
				printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
				printf("****************************************************************************\n");
				cout << "|" << setw(17) << bets[b].command_1 << "|" << setw(16) << bets[b].command_2 << "|" << setw(9) << bets[b].koef1 << "|" << setw(9) << bets[b].koef2 << "|" << setw(3) << bets[b].goals_1 << ":" << setw(2) << bets[b].goals_2 << "|" << setw(5) << bets[b].timeH << ":" << setw(6) << bets[b].timeM << "|" << endl;
				printf("****************************************************************************\n");
				cout << "�� ������� ������ ����?" << endl;
				cout << "1. ��" << endl;
				cout << "2. ���" << endl;
				o = _getch();
				if (o == '2')	break;
				else if (o != '1') {
					system("cls");
					cout << "����� ������� ���!" << endl;
					system("pause");
					goto l2;
				}
			r1:
				cout << "������� ����� ����� ������: ";
				cin >> stavka;
				if (stavka > this->balance || stavka < 0 || isalpha(stavka)) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "�� ����� ������������ ������" << endl;
					cout << "��� ������ ����� " << this->balance << endl;
					system("pause");
					system("cls");
					goto r1;
				}
				system("cls");
			ll:
				printf("****************************************************************************\n");
				printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
				printf("****************************************************************************\n");
				cout << "|" << setw(17) << bets[b].command_1 << "|" << setw(16) << bets[b].command_2 << "|" << setw(9) << bets[b].koef1 << "|" << setw(9) << bets[b].koef2 << "|" << setw(3) << bets[b].goals_1 << ":" << setw(2) << bets[b].goals_2 << "|" << setw(5) << bets[b].timeH << ":" << setw(6) << bets[b].timeM << "|" << endl;
				printf("****************************************************************************\n");
				cout << "�������� ����� �������, �� ������� ������ ���������";
				switch (_getch()) {
				case '1': {
					system("cls");
					this->balance -= stavka;
					if (Game() == 1) {
						cout << "�� ��������!" << endl;
						cout << "����� �������� ��������� " << stavka * bets[b].koef1 << endl;
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
						cout << "� ���������, �� ���������!" << endl;
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
						cout << "�� ��������!" << endl;
						cout << "����� �������� ��������� " << stavka * bets[b].koef2 << endl;
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
						cout << "� ���������, �� ���������!" << endl;
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
					cout << "����� ������� ���" << endl;
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
				cout << "����� ������� ���" << endl;
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

	int Show() { //������� ����������� ���� ������������� � ������
		while (true) {
			system("cls");
			cout << "�������� ������ �����:" << endl;
			cout << "1. ���������� ������ ������������������ �������������" << endl;
			cout << "2. ���������� ��� ������� ������" << endl;
			cout << "0. �����" << endl;
			switch (_getch()) {
			case '1': {
				system("cls");
				ifstream nu("n_u.txt");
				int k;
				int i = 0;
				ifstream us("Users.txt");
				if (!nu.is_open()) {
					cout << "� ������� �� ���������������� �� ������ ������������" << endl;
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
				printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
				printf("********************************************************************************\n");
				i = 0;
				while (i < k) {
					cout << "|" << setw(10) << user[i].login << "|" << setw(11) << user[i].name << "|" << setw(21) << user[i].surname << "|" << setw(20) << user[i].patronymic << "|" << setw(12) << user[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					i++;
				}
			r1:
				cout << "\n\n�������� ������ �����:" << endl;
				cout << "1. ���������� ������ �������������" << endl;
				cout << "2. ����� �������������" << endl;
				cout << "3. ���������� �������������" << endl;
				cout << "0. ��������" << endl;
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
					cout << "������ ������ ���" << endl;
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
					cout << "�� ������ ������ � ������� ��� �� ����� ������!" << endl;
					system("pause");
					system("cls");
					break;
				}
				int k; //���������� ��� ���������� ������
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
				printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
				printf("****************************************************************************\n");
				for (int i = 0; i < k; i++) {
					cout << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
					printf("****************************************************************************\n");
				}
				cout << "�������� ������ �����" << endl;
				cout << "1. ������������� ������" << endl;
				cout << "2. ����� �� ���������" << endl;
				cout << "3. ����������" << endl;
				cout << "0. �����" << endl;
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
					cout << "������ ������ ���" << endl;
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
				cout << "������ ������ ���" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		return 0;
	}


	int Enter() { //���������� ������� ����� ��������������
		return admin_enter();
	}

	int Register() { //���������� ������� ����������� ��������������
		ofstream fout("AdminCheck.txt");
		fout << "123456";
		fout.close();
		system("cls");
		cout << "������� ��������� ������ ��� ���������������" << endl;
		ifstream fin("AdminCheck.txt"); //��������� ����� � ����� ��������� �������
		string checking; //���������� ��� ����������� ��������� ���������� ������ � ���, ������� ����� � �����
		string checking_; //����������, � ������� �� ����� ��� ��������� ������
		fin >> checking_;
		if (!fin.is_open()) {
			cout << "��, � ������ ����..." << endl;
		}
	rep1:
		cin >> checking; //������ �������� �������������� ������ ������
		if (checking_ != checking) {
			system("cls");
			cout << "��� �, ��� ���� ���������� �������, ������� �������� ����� ��� ���?" << endl;
			cout << "1. ��" << endl;
			cout << "2. ���" << endl;
			switch (_getch()) {
			case '1':
				system("cls");
				cout << "������� ��������� ������ ��������������:" << endl;
				goto rep1;
				break;
			case '2':
				cout << "�� ��� � �����, ��� �� �� ��������� �������������" << endl << endl;
				system("pause");
				system("cls");
				break;
			default:
				system("pause");
				cout << "����� ��������, �� � ��� ��� ������� ������ =)" << endl << endl;
				cout << "������� ��������� ������ ��������������:" << endl;
			}
		}
		else {
			system("cls");
			cout << "��� �� �� �������..." << endl;
			Sleep(1500);
			system("cls");
			cout << "���������, �� �����, ��� �� ��� ������� �������������" << endl << endl;
			cout << "������ ��� ��� ������� ������������ ������ � ������ ��� �����" << endl << endl;
			admin();

		}
		return 0;
	}

	int Del() { //�������� ������ � �������������
		system("cls");
		while (true) {
			cout << "�������� ������ �����" << endl;
			cout << "1. �������� ������" << endl;
			cout << "2. �������� ������������" << endl;
			cout << "0. ��������" << endl;
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
				cout << "����� ������� �� ����������, ��������� ����!" << endl;
			}
		}
		return 0;
	}

	int Edit() {
		while (true) {
			system("cls");
			cout << "�������� ������ �����" << endl;
			cout << "1. �������������� ������������" << endl;
			cout << "2. �������������� ������" << endl;
			cout << "0. ������" << endl;
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
				cout << "����� ������� �� ����������, ��������� ����!" << endl;
				system("pause");
			}
		}
		return 0;
	}

	int SetBet() { //"�������" ����
		string command;
		string command1;
		double koef;
		double koef1;
		int time1;
		int time2;
		cout << "������� �������� ������ �������" << endl;
		cin >> command;
		system("cls");
		cout << "������� �������� ������ �������" << endl;
		cin >> command1;
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			system("cls");
			cout << "������� ����������� ��� ������� ������ (�� ������ �������)" << endl;
			cin >> koef;
		} while (koef < 0 || koef > 10 || isalpha(koef) || !cin.good());
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			system("cls");
			cout << "������� ����������� ��� ������� ������ (�� ������ �������)" << endl;
			cin >> koef1;
		} while (koef1 < 0 || koef1 > 10 || isalpha(koef1) || !cin.good());
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			system("cls");
			cout << "������� ����� ������ ���� (����)" << endl;
			cin >> time1;
		} while (time1 > 24 || time1 <= 0 || !cin.good());
		do {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "������� ����� ������ ���� (������)" << endl;
			cin >> time2;
			system("cls");
		} while (time2 > 59 || time2 < 1 || isalpha(time2) || !cin.good());
		Bets bet(command, command1, koef, koef1, time1, time2, 0, 0);
		cout << "���� ��������� �������!" << endl;
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

int menu() { //�������� �������, � ������� �������� ��� ���������
	while (true) {
		cout << "������������! ��� ������������ ������������ ������� \"�� ��� ������\"" << endl << endl;
		cout << "����������, �������� ����� �����/�����������" << endl;
		cout << "1. ����� ��� ������������" << endl;
		cout << "2. ����� ��� �������������" << endl;
		cout << "3. ������������������ ��� ������������" << endl;
		cout << "4. ������������������ ��� �������������" << endl;
		cout << "0. ����� �� �������" << endl;
		switch (_getch()) {
		case '1': {
			Imain* ptr;
			User user;
			ptr = &user;
			if (ptr->Enter() == 1) {
			} //�������� ����� "����" � �����

			break;
		}
		case '2': {
			Imain* ptr;
			Administrator admin;
			ptr = &admin;
			if (ptr->Enter() == 1) {

			} //�������� ����� "����" � ������

			break;
		}
		case '3': {
			Imain* ptr;
			User user;
			ptr = &user;
			ptr->Register(); //�������� ����� "�����������" � �����

			break;
		}
		case '4': {
			Imain* ptr;
			Administrator admin;
			ptr = &admin;
			ptr->Register(); //�������� ����� "�����������" � ��������������

			break;
		}
		case '0':
			return 0;
			break;
		default:
			system("cls");
			cout << "����� ������� �� ����������, ��������� ����!" << endl << endl << endl;
		}
	}
	return 0;
}

int admin() { //����������� ��������������
	Administrator admin;
	ifstream fin("Shifr.txt");
	int sdvig;
	fin >> sdvig;
	fin.close();
	char m = '0';//���������� ��� ����������� ������� �������
	int i = 0; //����� �������
	int l = 1; //��������� ������� �������
	char pass[100];
	system("cls");
	cout << "���������� �����:" << endl;
res2:
	cin >> admin.login;
	if ((admin.login).length() > 21) {
		system("cls");
		cout << "���������� ������������ ���������� ��������! ������� �� ����� 20" << endl;
		Sleep(3000);
		system("cls");
		cout << "��������� ���� ������:" << endl;
		goto res2;
	}
	system("cls");
	cout << "���������� ������ (�� ����� 20 ��������):" << endl;
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
			cout << "���������� ������������ ���������� ��������" << endl;
			Sleep(1000);
			system("cls");
			cout << "��������� ���� ������:\n" << endl;
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
	cout << "������� ���� ���: " << endl;
	cin >> admin.name;
	system("cls");
	cout << "������� ���� �������: " << endl;
	cin >> admin.surname;
	system("cls");
	cout << "������� ���� ��������: " << endl;
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

int user() { //����������� ������������
	User us;
	ifstream fin("Shifr.txt");
	int sdvig;
	fin >> sdvig;
	fin.close();
	system("cls");
	char m = '0';//���������� ��� ����������� ������� �������
	int i = 0; //����� �������
	int l = 1; //��������� ������� �������
	char pass[100];
	cout << "���������� �����:" << endl;
res2:
	cin >> us.login;
	if ((us.login).length() > 21) {
		system("cls");
		cout << "���������� ������������ ���������� ��������! ������� �� ����� 20" << endl;
		Sleep(3000);
		system("cls");
		cout << "��������� ���� ������:" << endl;
		goto res2;
	}
	system("cls");
	cout << "���������� ������ (�� ����� 20 ��������):" << endl;
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
			cout << "���������� ������������ ���������� ��������" << endl;
			Sleep(1000);
			system("cls");
			cout << "��������� ���� ������:\n" << endl;
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
	cout << "������� ���� ���: " << endl;
	cin >> us.name;
	system("cls");
	cout << "������� ���� �������: " << endl;
	cin >> us.surname;
	system("cls");
	cout << "������� ���� ��������: " << endl;
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

int user_enter() { //���� ��� ������������
	ifstream fin("n_u.txt");
	int k; //���������� ��� �������� ���������� ������
	string user_l; //���������� ��� ����������� ��������� ������
	char userPass[100];
	string userPassword; //���������� ��� ����������� ��������� ������
	int l = 0; //������������� ������������ ����� ������/������
	int b; //��������� ��� ����������� ������ ������� �����
	char m;
	if (!fin.is_open()) {
		cout << "� ������� �� ���������������� �� ������ ������������!" << endl;
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
	cout << "������� ���� �����:\n";
r1:
	cin >> user_l;
	for (i = 0; i < k; i++) {
		if ((us[i].login).compare(user_l) == 0) {
			b = i;
			system("cls");
			cout << "�� ����� ������ �����!" << endl;
			l++;
		res3:
			cout << "������� ������: ";
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
					printf("���������� ������������ ���������� ��������\n");
					Sleep(1000);
					system("cls");
					printf("��������� ���� ������:\n");
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
				cout << "���� ���������� �������!" << endl;
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
				cout << "������ ����� �����������!" << endl;
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
		cout << "�� ����� �������� �����, ��������� ��� ���:" << endl;
		goto r1;
	}

	return 0;
}

int admin_enter() { //���� ��� ��������������
	ifstream fin("n_a.txt");
	int k; //���������� ��� �������� ���������� �������
	string admin_l; //���������� ��� ����������� ��������� ������
	char adminPass[100];
	string adminPassword; //���������� ��� ����������� ��������� ������
	int l = 0; //������������� ������������ ����� ������/������
	int b; //��������� ��� ����������� ������ ������� ������
	char m;
	system("cls");
	if (!fin.is_open()) {
		cout << "� ������� �� ���������������� �� ������ ��������������!" << endl;
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
	cout << "������� ���� �����:\n";
r1:
	cin >> admin_l;
	for (i = 0; i < k; i++) {
		if ((adm[i].login).compare(admin_l) == 0) {
			b = i;
			cout << "�� ����� ������ �����!" << endl;
			l++;
		res3:
			cout << "������� ������: ";
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
					printf("���������� ������������ ���������� ��������\n");
					Sleep(1000);
					system("cls");
					printf("��������� ���� ������:\n");
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
				cout << "������ ����� �����������!" << endl;
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
		cout << "�� ����� �������� �����, ��������� ��� ���:" << endl;
		goto r1;
	}

	return 0;
}

int menu_u(User& us) {
	system("cls");
	while (true) {
		cout << "����� ����������," << us.name << " " << us.patronymic << "!";
		cout << "\t\t������� ������:	 " << us.balance << endl << endl;
		cout << "�������� ������ ��� ��������:\n";
		cout << "1. ������� ������" << endl;
		cout << "2. ��������� ������" << endl;
		cout << "3. ������� ��������" << endl;
		cout << "0. ����� �� ������� ������" << endl;
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
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			break;
		}
	}
	return 0;
}

int menu_a(Administrator& adm) {
	while (true) {
		system("cls");
		cout << "����� ����������," << adm.name << " " << adm.patronymic << "!";
		cout << "�������� ������ ��� ��������:\n";
		cout << "1. ������� ������" << endl;
		cout << "2. �������� ���������� � ������� � �������������" << endl;
		cout << "3. ��������" << endl;
		cout << "4. ��������������" << endl;
		cout << "0. ����� �� ������� ������" << endl;
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
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			break;
		}
	}
	return 0;
}

int Game() {
	system("cls");
	for (int i = 10; i >= 1; i--) {
		system("cls");
		cout << "������� ������" << endl;
		cout << "�� ����� ����� �������� " << i << " ���." << endl;
		Sleep(1000);
	}
	srand(time(NULL));
	int random = 1 + rand() % 2;
	return random;
}

int m_sort(User* us, int k) {
	while (true) {
		User user;
		cout << "�������� ��� ����������: " << endl;
		cout << "1. ����������� �� �����" << endl;
		cout << "2. ����������� �� ��������" << endl;
		cout << "3. ����������� �� ��������" << endl;
		cout << "0. ��������" << endl;
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
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
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
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
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
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
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
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int m_filtr(User* us, int k) {
	while (true) {
		cout << "���������� ����� ������������ �� ������� ����� �������������" << endl;
		cout << "1. ��������� ����������" << endl;
		cout << "0. ��������" << endl;
		switch (_getch()) {
		case '1': {
			float min, max;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ������ ����� �����" << endl;
				cin >> min;
				cout << "������� ������� ����� �����" << endl;
				cin >> max;
				system("cls");
			} while (min == max || max < min || max < 0 || min < 0 || isalpha(min) || isalpha(max) || !cin.good());
			int flag = 0;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (us[i].balance >= min && us[i].balance <= max) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\n�� ������� ������������� � ����� ����������!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int m_find(User* us, int k) {
	while (true) {
		cout << "�������� ������ �������� ������:" << endl;
		cout << "1. ����� �� ������" << endl;
		cout << "2. ����� �� �����" << endl;
		cout << "3. ����� �� �������" << endl;
		cout << "4. ����� �� ��������" << endl;
		cout << "0. ��������" << endl;
		switch (_getch()) {
		case '1': {
			system("cls");
			string log;
			int flag = 0;
			cout << "������� �����" << endl;
			cin >> log;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (log.compare(us[i].login) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\n�� ������� ������������� � ����� ����������!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '2': {
			system("cls");
			string name;
			int flag = 0;
			cout << "������� ���" << endl;
			cin >> name;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (name.compare(us[i].name) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\n�� ������� ������������� � ����� ����������!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '3': {
			system("cls");
			string fam;
			int flag = 0;
			cout << "������� ������� ������������" << endl;
			cin >> fam;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (fam.compare(us[i].surname) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\n�� ������� ������������� � ����� ����������!" << endl;
		}
				system("pause");
				system("cls");
				break;
		case '4': {
			system("cls");
			string patr;
			int flag = 0;
			cout << "������� ��������" << endl;
			cin >> patr;
			int i = 0;
			printf("********************************************************************************\n");
			printf("|  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("********************************************************************************\n");
			for (i; i < k; i++) {
				if (patr.compare(us[i].patronymic) == 0) {
					cout << "|" << setw(10) << us[i].login << "|" << setw(11) << us[i].name << "|" << setw(21) << us[i].surname << "|" << setw(20) << us[i].patronymic << "|" << setw(12) << us[i].balance << "|" << endl;
					printf("********************************************************************************\n");
					flag++;
				}
			}
			if (flag == 0) cout << "\n�� ������� ������������� � ����� ����������!" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
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
		cout << "�������� ��� ����������: " << endl;
		cout << "1. ����������� �� �������� 1 �������" << endl;
		cout << "2. ����������� �� �������� 2 �������" << endl;
		cout << "3. ����������� �� ������������� 1 �������" << endl;
		cout << "3. ����������� �� ������������� 2 �������" << endl;
		cout << "0. ��������" << endl;
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
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int s_find(Bets* bets, int k) {
	while (true) {
		Bets bet;
		cout << "�������� �������� ������: " << endl;
		cout << "1. ����� 1 �������" << endl;
		cout << "2. ����� 2 �������" << endl;
		cout << "0. ��������" << endl;
		switch (_getch()) {
		case '1': {
			system("cls");
			string com;
			int flag = 0;
			cout << "������� �������� �������: " << endl;
			cin >> com;
			printf("****************************************************************************\n");
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			if (flag == 0) cout << "����� ������� ���(\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '2': {
			system("cls");
			string com;
			int flag = 0;
			cout << "������� �������� �������: " << endl;
			cin >> com;
			printf("****************************************************************************\n");
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			if (flag == 0) cout << "����� ������� ���(\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}

int s_filtr(Bets* bets, int k) {
	while (true) {
		cout << "�������� �������� ����������:" << endl;
		cout << "1. ������������ ������ ������" << endl;
		cout << "2. ������������ ������ ������" << endl;
		switch (_getch()) {
		case '1': {
			float min, max;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ������ ����� �������������" << endl;
				cin >> min;
				cout << "������� ������� ����� �������������" << endl;
				cin >> max;
				system("cls");
			} while (min == max || max < min || max < 0 || min < 0 || isalpha(min) || isalpha(max) || !cin.good());
			int flag = 0;
			printf("****************************************************************************\n");
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			if (flag == 0) cout << "��� ������������� ���������� ��� ��������\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '2': {
			float min, max;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ������ ����� �������������" << endl;
				cin >> min;
				cout << "������� ������� ����� �������������" << endl;
				cin >> max;
				system("cls");
			} while (min == max || max < min || max < 0 || min < 0 || isalpha(min) || isalpha(max) || !cin.good());
			int flag = 0;
			printf("****************************************************************************\n");
			printf("|    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
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
			if (flag == 0) cout << "����� ������� ���(\n" << endl;
			system("pause");
			system("cls");
		}
				break;
		case '0':
			return 0;
		default:
			system("cls");
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
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
		cout << "� ������� �� ���������������� �� ������ ������������" << endl;
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
	printf("| �  |  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
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
		cout << "�������� ����� ������������, �������� ������ �������" << endl;
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
		cout << "�� ������ ������ � ������� ��� �� ����� ������!" << endl;
		system("pause");
		system("cls");
		return 0;
	}
	int k; //���������� ��� ���������� ������
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
	printf("|  �  |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
	printf("**********************************************************************************\n");
	for (int i = 0; i < k; i++) {
		cout << "|" << setw(5) << i << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
		printf("****************************************************************************\n");
	}
	int num;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "�������� ����� ������, ������� ������ �������" << endl;
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
		cout << "� ������� �� ���������������� �� ������ ������������" << endl;
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
	printf("| �  |  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
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
		cout << "�������� ����� ������������, ��������� �������� �� ������ ���������������" << endl;
		cin >> num;
		system("cls");
	} while (num >= k || num < 0 || isalpha(num) || !cin.good());
	while (true) {
		system("cls");
		cout << "�������� ������ �������� ��������������:" << endl;
		cout << "1. ������������� ���" << endl;
		cout << "2. ������������� �������" << endl;
		cout << "3. ������������� ��������" << endl;
		cout << "4. ������������� ������" << endl;
		cout << "5. ������� ������� ������������" << endl;
		cout << "0. �����" << endl;
		switch (_getch()) {
		case '1': {
			string name;
			printf("*************************************************************************************\n");
			printf("| �  |  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			cout << "������� ����� ��� ������������" << endl;
			cin >> name;
			user[num].name = name;
		}
				break;
		case '2': {
			string sname;
			printf("*************************************************************************************\n");
			printf("| �  |  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			cout << "������� ����� ������� ������������" << endl;
			cin >> sname;
			user[num].surname = sname;
		}
				break;
		case '3': {
			string pname;
			printf("*************************************************************************************\n");
			printf("| �  |  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			cout << "������� ����� �������� ������������" << endl;
			cin >> pname;
			user[num].patronymic = pname;
		}
				break;
		case '4': {
			float bal;
			printf("*************************************************************************************\n");
			printf("| �  |  �����   |    ���    |       �������       |      ��������      |   ������   |\n");
			printf("*************************************************************************************\n");
			cout << "|" << setw(4) << num << "|" << setw(10) << user[num].login << "|" << setw(11) << user[num].name << "|" << setw(21) << user[num].surname << "|" << setw(20) << user[num].patronymic << "|" << setw(12) << user[num].balance << "|" << endl;
			printf("*************************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ������������������ ������ ������������" << endl;
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
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			system("pause");
		}
	}
	return 0;
}

int EditBet() {
	ifstream bet("Bets.txt");
	ifstream fin("n_s.txt");
	if (!fin.is_open()) {
		cout << "�� ������ ������ � ������� ��� �� ����� ������!" << endl;
		system("pause");
		system("cls");
		return 0;
	}
	int k; //���������� ��� ���������� ������
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
	printf("|  �  |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
	printf("**********************************************************************************\n");
	for (int i = 0; i < k; i++) {
		cout << "|" << setw(5) << i << "|" << setw(17) << bets[i].command_1 << "|" << setw(16) << bets[i].command_2 << "|" << setw(9) << bets[i].koef1 << "|" << setw(9) << bets[i].koef2 << "|" << setw(3) << bets[i].goals_1 << ":" << setw(2) << bets[i].goals_2 << "|" << setw(5) << bets[i].timeH << ":" << setw(6) << bets[i].timeM << "|" << endl;
		printf("****************************************************************************\n");
	}
	int num;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "�������� ����� ������, ������� ������ ���������������" << endl;
		cin >> num;
		system("cls");
	} while (num >= k || num < 0 || isalpha(num) || !cin.good());
	while (true) {
		cout << "�������� ��������, ������� ������ ���������������" << endl;
		cout << "1. ������������� �������� ������ �������" << endl;
		cout << "2. ������������� �������� ������ �������" << endl;
		cout << "3. ������������� ����������� ������ �������" << endl;
		cout << "4. ������������� ����������� ������ �������" << endl;
		cout << "5. ������������� ����� ������ ����" << endl;
		cout << "6. ������� ������ ������ ��� ��������������" << endl;
		cout << "0. �����" << endl;
		switch (_getch()) {
		case '1': {
			string command1;
			printf("**********************************************************************************\n");
			printf("|  �  |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			cout << "������� ����� �������� ������ �������" << endl;
			cin >> command1;
			bets[num].command_1 = command1;
		}
				break;
		case '2': {
			string command2;
			printf("**********************************************************************************\n");
			printf("|  �  |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			cout << "������� ����� �������� ������ �������" << endl;
			cin >> command2;
			bets[num].command_2 = command2;
		}
				break;
		case '3': {
			float koef;
			printf("**********************************************************************************\n");
			printf("|  �  |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ����� ����������� ������ �������" << endl;
				cin >> koef;
			} while (koef < 0 || !cin.good() || isalpha(koef));
			bets[num].koef1 = koef;
		}
				break;
		case '4': {
			float koef;
			printf("**********************************************************************************\n");
			printf("|  �  |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ����� ����������� ������ �������" << endl;
				cin >> koef;
			} while (koef < 0 || !cin.good() || isalpha(koef));
			bets[num].koef2 = koef;
		}
				break;
		case '5': {
			int hours;
			int min;
			printf("**********************************************************************************\n");
			printf("|  �  |    ������� 1    |    ������� 2   | ����. 1 | ����. 2 | ���� | ����� ���� |\n");
			printf("**********************************************************************************\n");
			cout << "|" << setw(5) << num << "|" << setw(17) << bets[num].command_1 << "|" << setw(16) << bets[num].command_2 << "|" << setw(9) << bets[num].koef1 << "|" << setw(9) << bets[num].koef2 << "|" << setw(3) << bets[num].goals_1 << ":" << setw(2) << bets[num].goals_2 << "|" << setw(5) << bets[num].timeH << ":" << setw(6) << bets[num].timeM << "|" << endl;
			printf("****************************************************************************\n\n\n");
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ����� ����� ������ (� �����)" << endl;
				cin >> hours;
			} while (hours < 0 || hours > 24 || !cin.good() || isalpha(hours));
			bets[num].timeH = hours;
			do {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������� ����� ����� ������ (� �������)" << endl;
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
			cout << "����� ������� �� ����������, �������� ������ �����!" << endl;
			system("pause");
		}
	}
	return 0;
}
