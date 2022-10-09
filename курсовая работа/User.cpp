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
	for (int i = 0; i < vec_of_users.size(); i++)
		if (m_password == vec_of_users.at(i).m_password)
			return false;

	return true;
}


void read_user_data(vector<User>& vec_of_users)
{
	ifstream fusers(USERS_DATA);
	int num_of_users = readAmount(USERS_AMOUNT);
	for(int i=0; i<num_of_users; i++)
	{
		User temp;
		fusers >> temp.m_login 
			>> temp.m_password
			>> temp.m_surname
			>> temp.m_name
			>> temp.m_patronymic;

		vec_of_users.push_back(temp);
	}
	fusers.close();
}

void User::change_login()
{
	system("cls");
	cout << "\n  Введите новый логин" ;
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
	cout << "Введите новый пароль" << endl;
	string newPassword;
	bool checker(false);
	while (!checker)
	{
		cin >> newPassword;
		if (registrationCheck(newPassword)) checker = true;
	}
	cout << "Пароль успешно изменен!" << endl;
}

void User::change_surname()
{
	system("cls");
	cout << "Введите новую фамилию" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_surname;
		if (check_string_for_wrong_symbols(m_surname)) checker = true;
	}
	cout << "Фамилия успешно изменена!" << endl;
}

void User::change_name()
{
	system("cls");
	cout << "Введите новое имя" << endl;
	string newName;
	bool checker(false);
	while (!checker)
	{
		cin >> m_name;
		if (registrationCheck(m_name)) checker = true;
	}
	cout << "Имя успешно изменено!" << endl;
}

void User::change_patronymic()
{
	system("cls");
	cout << "Введите новое отчество" << endl;
	bool checker(false);
	while (!checker)
	{
		cin >> m_patronymic;
		if (registrationCheck(m_patronymic)) checker = true;
	}
	cout << "Отчество успешно изменено!" << endl;
}

void write_user_data(vector<User>& vec_of_users)
{
	ofstream fusers(USERS_DATA);
	for (int i = 0; i < vec_of_users.size(); i++)
	{
		fusers << endl << vec_of_users.at(i).m_login << endl 
			<< vec_of_users.at(i).m_password << endl 
			<< vec_of_users.at(i).m_surname << endl
			<< vec_of_users.at(i).m_name << endl 
			<< vec_of_users.at(i).m_patronymic;
	}
	fusers.close();
}