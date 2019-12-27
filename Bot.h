#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Card.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::wcout;

class Bot
{
protected:
	vector<Card*> cards;
	string name;
	bool decision;

public:
	Bot();

	vector<Card*>& get_cards();
	bool get_decision() const;
	int get_score() const;
	string get_name();
	void set_decision(bool _decision);

	void print();
	void take_card(Card* _card);
	virtual bool make_decision();

	void clear();
};

