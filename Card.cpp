#include "Card.h"

char colors[] = { 'p','t','s','k' };
char figures[] = { '2','3','4','5','6','7','8','9','T','J','Q','K','A' };

Card::Card(int _figure, int _color)
	 :figure(figures[_figure])
	, color(colors[_color])
{
	if (_figure < 8)
		value = _figure + 2;
	else if (_figure == 12)
		value = 11;
	else
		value = 10;
};

char Card::get_figure() const
{
	return figure;
}
char Card::get_color() const
{
	return color;
}
int Card::get_value() const
{
	return value;
}