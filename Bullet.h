#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class Bullet {
public:
    float speed = 0;
    float x, y;

    sf::Vector2f direction;

    std::string bullet_Right;
    std::string bullet_Left;
    std::string bullet_Up;
    std::string bullet_Down;

    sf::Image bulletRight_image;
    sf::Image bulletLeft_image;
    sf::Image bulletUp_image;
    sf::Image bulletDown_image;

    sf::Texture bulletRight_Texture;
    sf::Texture bulletLeft_Texture;
    sf::Texture bulletUp_Texture;
    sf::Texture bulletDown_Texture;

    sf::Sprite Bullet_Sprite;

    Bullet(std::string _bullet_Right, std::string _bullet_Left, std::string _bullet_Up, std::string _bullet_Down, float _speed);

    void SetBulletPosition(const Player& player);

    void BulletUpdate_array(float time, const std::vector<Enemy>& enemies);

    float getDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);

    void BulletAnimation(float time, float CurentFrame);
};