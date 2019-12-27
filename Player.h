#pragma once
#include "Bot.h"

using std::getline;
using std::cin;

class Player :public Bot
{
public:
	Player();

	bool make_decision();
};

