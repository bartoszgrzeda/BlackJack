#include "Bot.h"

Bot::Bot()
	: decision(true)
	, name("BOT")
{
}

vector<Card*>& Bot::get_cards()
{
	return cards;
}
bool Bot::get_decision() const
{
	return decision;
}
int Bot::get_score() const
{
	int total_score = 0;
	for (int i = 0; i < cards.size(); ++i)
	{
		total_score += cards[i]->get_value();
	}
	return total_score;
}
string Bot::get_name()
{
	return name;
}
void Bot::set_decision(bool _decision)
{
	decision = _decision;
}

void Bot::print()
{
	cout << "Nazwa gracza: " << name << endl;
	cout << "Wartosc kart gracza: " << get_score() << endl;
	cout << "Karty gracza: ";
	if (cards.size() == 0)
		cout << "BRAK";
	else
	{
		for (int i = 0; i < cards.size(); ++i)
		{
			cout << cards[i]->get_color() << cards[i]->get_figure() << " ";
		}
	}
	cout << endl << endl;
}
void Bot::take_card(Card* _card)
{
	if(cards.size()<10)
		cards.push_back(_card);
}
bool Bot::make_decision()
{
	if (get_score() < 17)
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

void Bot::clear()
{
	cards.clear();
}