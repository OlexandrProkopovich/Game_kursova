#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class button
{
public:
	float _width, _height;
	int _x_pos, _y_pos;
	int _text_size;
	std::string _font_string;
	std::string _button_text;

	sf::Color _color_button;
	sf::Color _color_text;
	sf::Font _font;

	sf::Text text;
	sf::RectangleShape _button;

	button(float width, float height, int x_pos, int y_pos, sf::Color color_button, sf::Color color_text, std::string font, std::string button_text, int text_size);
};

