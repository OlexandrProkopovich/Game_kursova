#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"
class lifeBar
{
public:
	float x_pos, y_pos;
	std::string life_bar;
	sf::Image life_bar_image;
	sf::Texture life_bar_texture;

	sf::Sprite LifeBar;

	lifeBar(float _x_pos, float _y_pos, std::string _life_bar);

	void Update_LifeBar(const Player& p1);
};

