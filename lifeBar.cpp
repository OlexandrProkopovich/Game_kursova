#include "lifeBar.h"



lifeBar::lifeBar(float _x_pos, float _y_pos, std::string _life_bar) : x_pos(_x_pos), y_pos(_y_pos), life_bar(_life_bar)
{
	life_bar_image.loadFromFile(life_bar);
	life_bar_texture.loadFromImage(life_bar_image);

	LifeBar.setTexture(life_bar_texture); LifeBar.setScale(3, 3);
	LifeBar.setPosition(x_pos, y_pos);
}

void lifeBar::Update_LifeBar(const Player& p1)
{
	if (p1.health > 15)
	{
		
		LifeBar.setTextureRect(sf::IntRect(156, 0, 64, 12));
	}
	else if (p1.health > 10 && p1.health <= 15)
	{
		
		LifeBar.setTextureRect(sf::IntRect(156, 79, 64, 12));
	}
	else if (p1.health > 5 && p1.health <= 10)
	{
		
		LifeBar.setTextureRect(sf::IntRect(156, 158, 64, 12));
	}
	else if (p1.health >= 1 && p1.health <= 5)
	{
		
		LifeBar.setTextureRect(sf::IntRect(156, 237, 64, 12));
	}
	else if (p1.health <= 0)
	{

		LifeBar.setTextureRect(sf::IntRect(156, 316, 64, 12));
	}
}