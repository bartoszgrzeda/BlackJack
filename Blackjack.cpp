#include "Blackjack.h"

Blackjack::Blackjack()
{
	// Wygenerowanie talii kart
	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Card temp_card(i, j);
			cards.push_back(temp_card);
		}
	}
	
	// Dodanie botow i graczy
	cout << "Ile BOTOW chcesz dodac (1-5)? Twoj wybor: ";
	int choice;
	while (1)
	{
		cin >> choice;
		if (!cin.fail() && choice > 0 && choice < 6)
			break;
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Zly wybor! Wybierz jeszcze raz: ";
	}

	for (int i = 0; i < choice; ++i)
	{
		Bot* bot = new Bot;
		players.push_back(bot);
	}

	Player* player = new Player;
	players.push_back(player);
}
Blackjack::~Blackjack()
{
	for (int i = 0; i < players.size(); ++i)
		delete players[i];
}

void Blackjack::shuffle_cards()
{
	shuffle(cards.begin(), cards.end(), default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}
Card* Blackjack::give_card()
{
	for (int i = 0; i < cards.size(); ++i)
	{
		if (!is_card_used(&cards[i]))
			return &cards[i];
	}
}
bool Blackjack::is_card_used(const Card* _card) const
{
	for (int i = 0; i < players.size(); ++i)
	{
		for (int j = 0; j < players[i]->get_cards().size(); ++j)
		{
			if (_card == players[i]->get_cards()[j])
				return true;
		}
	}
	return false;
}
void Blackjack::start_new_game()
{
	shuffle_cards();
	// Rozdanie graczom po dwie karty
	for (int i = 0; i < players.size(); ++i)
	{
		players[i]->take_card(give_card());
		players[i]->take_card(give_card());
	}
	// Petla, dzialajaca do czasu az gracz ma >21 lub nie chce dobierac
	while (1)
	{
		// Wydrukowanie kart graczy
		system("cls");
		for (int i = 0; i < players.size(); ++i)
			players[i]->print();
		// Zapytanie o decyzje
		if (ask_players() == 0)
			break;
		// Rozdanie kart grajacym graczom i ustawienie decyzji na false jesli wartosc kart >= 21
		for (int i = 0; i < players.size(); ++i)
		{
			if (players[i]->get_decision() == true)
			{
				players[i]->take_card(give_card());
				if (players[i]->get_score() >= 21)
					players[i]->set_decision(false);
			}
		}
	}

	who_won();
}
int Blackjack::ask_players() const
{
	// Pyta graczyy i zwraca liczbe grajacych graczy
	int count_of_playing_players = 0;
	for (int i = 0; i < players.size(); ++i)
	{
		if (players[i]->get_decision() == true)
		{
			if (players[i]->make_decision() == true)
				++count_of_playing_players;
		}
	}
	return count_of_playing_players;
}
void Blackjack::who_won()
{
	cout << endl;
	// Stworzenie struktury: para gracz-wynik
	struct Pair
	{
		string name;
		int score;
		Pair(string _name, int _score) : name(_name), score(_score) {};
	};
	
	// Pobranie wszystkich wynikow do jednego wektora
	vector<Pair> pairs;
	for (int i = 0; i < players.size(); ++i)
	{
		Pair temp_pair(players[i]->get_name(), players[i]->get_score());
		pairs.push_back(temp_pair);
	}

	// Sortowanie rosnąco po wyniku
	for (int i = 0; i < pairs.size(); ++i)
	{
		for (int j = 1; j < pairs.size() - i; ++j)
		{
			if (pairs[j - 1].score > pairs[j].score)
				swap(pairs[j - 1], pairs[j]);
		}
	}

	// Usuniecie wynikow wiekszych niz 21
	int p;
	for (p = 0; p < pairs.size(); ++p)
	{
		if (pairs[p].score > 21)
			break;
	}
	pairs.erase(pairs.begin() + p, pairs.end());

	// Jesli wszyscy mieli powyzej 21 to return i remis wszystkich
	if (pairs.size() == 0)
	{
		cout << "Kazdy z graczy mial ponad 21 punktow" << endl;
		cout << "Nikt nie wygral" << endl;
		return;
	}

	// Usuniecie wszystkich wynikow ktore sa ponizej najwyzszego
	for (p = 0; p < pairs.size(); ++p)
	{
		if (pairs[p].score == pairs[pairs.size() - 1].score)
			break;
	}
	if (p != 0)
	{
		pairs.erase(pairs.begin(), pairs.begin() + p);
	}

	// Wypisanie zwyciezcow/zwyciezcy
	cout << "Gratulacje dla zwyciezcow! Oto oni:" << endl;
	for (int i = 0; i < pairs.size(); ++i)
	{
		cout << "Gracz " << pairs[i].name << " z wynikiem: " << pairs[i].score << " punktow!" << endl;
	}
	cout << endl;
}

void Blackjack::start()
{
	while (1)
	{
		start_new_game();
		cout << "Czy chcesz grac kolejna gre? Y/N: ";
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
		if (choice == 'n' || choice == 'N')
			break;
		else
			clear();
	}
}
void Blackjack::clear()
{
	for (int i = 0; i < players.size(); ++i)
	{
		players[i]->set_decision(true);
		players[i]->clear();
	}
}