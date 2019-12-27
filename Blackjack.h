#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Card.h"
#include "Bot.h"
#include "Player.h"

using std::vector;
using std::default_random_engine;
using std::swap;

class Blackjack
{
	vector<Card> cards;
	vector<Bot*> players;

public:
	Blackjack();
	~Blackjack();

	void shuffle_cards();
	Card* give_card();
	bool is_card_used(const Card* _card) const;
	void start_new_game();
	int ask_players() const;
	void who_won();

	void start();
	void clear();
};

