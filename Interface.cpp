#include "Interface.h"

Interface::Interface(sf::String _BackGround_String, int _width, int _height) :BackGround_String(_BackGround_String),
width(_width), height(_height)
{
	background.setSize(sf::Vector2f(width, height));

	BackGround_Image.loadFromFile(BackGround_String);
	BackGround_Texture.loadFromImage(BackGround_Image);
	background.setTexture(&BackGround_Texture);
	background.setScale(1.2, 1.2);
	
}

void Interface::WorkText(sf::String _Font_String, sf::Text& _text, float _xpos, float _ypos, sf::String _str, int _size_font, sf::Color _menu_text_color, int _bord, sf::Color _border_color)
{
	font.loadFromFile(_Font_String);
	_text.setFont(font);
	_text.setCharacterSize(_size_font);
	_text.setPosition(_xpos, _ypos);
	_text.setString(_str);
	_text.setFillColor(_menu_text_color);
	_text.setOutlineThickness(_bord);
	_text.setOutlineColor(_border_color);
}