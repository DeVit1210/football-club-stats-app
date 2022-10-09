#include<iostream>
#include<windows.h>
#include<conio.h>
#include"Authorization.h"
#include"Player.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true)
	{
		switch (menu())
		{
		case 1:
		{
			Main* ptr;
			Administrator admin;
			ptr = &admin;
			int i = ptr->Enter();
			if (i == 0)
				admin_menu();
			break;
		}
		case 2:
		{
			Main* ptr;
			Administrator admin;
			ptr = &admin;
			ptr->registration();
			break;
		}
		case 3:
		{
			Main* ptr;
			User user;
			ptr = &user;
			ptr->Enter();

		}
		case 4:
		{
			return 0;
			break;
		}
		default: cout << "Упс... Произошла ошибка ввода" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			push_and_clear_page();
		}
	}


	return 0;
}