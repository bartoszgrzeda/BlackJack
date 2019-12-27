#include "Player.h"

Player::Player()
{
	string temp_name;
	cin.ignore(256, '\n');
	cout << "Ustaw nick gracza: ";
	getline(cin, temp_name);
	name = temp_name;
}

bool Player::make_decision()
{
	cout << "Czy chcesz dobrac karte? Y/N: ";
	char choice;
	while (1)
	{
		cin >> choice;
		if (!cin.fail() && (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n'))
			break;
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Zly wybor! Wybierz jeszcze raz: ";
	}
	if (choice == 'y' || choice == 'Y')
	{
		decision = true;
		return true;
	}
	else
	{
		decision = false;
		return false;
	}
}