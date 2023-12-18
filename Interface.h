#pragma once
#include <SFML/Graphics.hpp>
class Interface
{
public:
	int width, height;
	sf::String BackGround_String;

	sf::Image BackGround_Image;

	sf::Texture BackGround_Texture;

	sf::RectangleShape background;

	sf::Font font;
	sf::Text text;

	Interface(sf::String _BackGround_String, int _width, int _height);

	void WorkText(sf::String _Font_String, sf::Text& _text, float _xpos, float _ypos, sf::String _str, int _size_font, sf::Color _menu_text_color, int _bord, sf::Color _border_color);

};