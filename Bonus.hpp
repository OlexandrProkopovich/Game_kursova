#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Bonus
{
public:
	float x, y;
	std::string bonus_string;
	sf::Image bonus_image;
	sf::Texture bonus_texture;
	sf::Clock duration_timer; 
	bool active; 

	sf::Sprite bonus_sprite;
	Bonus(float _x, float _y, std::string _bonus_string) : x(_x), y(_y), bonus_string(_bonus_string), active(false)
	{
		bonus_image.loadFromFile(bonus_string);
		bonus_texture.loadFromImage(bonus_image);
		bonus_sprite.setTexture(bonus_texture);
		bonus_sprite.setPosition(x, y);
	}
};