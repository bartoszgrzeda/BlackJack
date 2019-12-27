#pragma once

class Card
{
	char figure;
	char color;
	int value;

public:
	Card(int _figure, int _color);
	
	char get_figure() const;
	char get_color() const;
	int get_value() const;
};

