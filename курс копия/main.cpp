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
	Administrator admin;
	User user;
	while (true)
	{
		switch (menu())
		{
		case 1:
		{
			if (admin.Enter() == SUCCESS)
				admin_menu();
			break;
		}
		case 2:
		{
			system("cls");
			admin.registration();
			break;
		}
		case 3:
		{
			if (user.Enter() == SUCCESS)
				user_module();
			break;
		}
		case 4:
		{
			return 0;
			break;
		}
		default: cout << "  " << INPUT_ERROR << endl;
			clear_bufer();
			push_and_clear_page();
		}
	}
	return 0;
}