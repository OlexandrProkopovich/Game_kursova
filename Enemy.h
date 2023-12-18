#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Enemy {
public:
	float x, y, speed;
	bool isAttacking = false;
	bool TakeDamage = false;
	bool isDead= false;
	bool deathAnimationFinished = false;
	bool deleteEnemy = false;
	bool startAttack = false;
	int health;

	sf::Vector2f direction;

	std::string Idle_String;
	std::string walkRight_String;
	std::string walkLeft_String;
	std::string upWalk_String;
	std::string downWalk_String;

	std::string TakeDamage_Right_String;
	std::string TakeDamage_Left_String;
	std::string TakeDamage_Up_String;
	std::string TakeDamage_Down_String;

	sf::Image TakeDamage_Right_Image;
	sf::Image TakeDamage_Left_Image;
	sf::Image TakeDamage_Up_Image;
	sf::Image TakeDamage_Down_Image;

	sf::Texture TakeDamage_Right_Texture;
	sf::Texture TakeDamage_Left_Texture;
	sf::Texture TakeDamage_Up_Texture;
	sf::Texture TakeDamage_Down_Texture;

	std::string Death_String;
	sf::Image Death_Image;
	sf::Texture Death_Texture;

	std::string down_attack_String;
	std::string up_attack_String;
	std::string left_attack_String;
	std::string righ_attack_String;

	sf::Image down_attack_Image;
	sf::Image up_attack_Image;
	sf::Image left_attack_Image;
	sf::Image righ_attack_Image;

	sf::Texture down_attack_Texture;
	sf::Texture up_attack_Texture;
	sf::Texture left_attack_Texture;
	sf::Texture righ_attack_Texture;
	

	sf::Image Idle_Image;
	sf::Image walkRight_Image;
	sf::Image walkLeft_Image;
	sf::Image upWalk_Image;
	sf::Image downWalk_Image;

	sf::Texture Idle_Texture;
	sf::Texture walkRight_Texture;
	sf::Texture walkLeft_Texture;
	sf::Texture upWalk_Texture;
	sf::Texture downWalk_Texture;

	sf::Sprite Enemy_Sprite;
	Enemy(const std::string _Idle_String, const std::string _walkRight_String, const std::string _walkLeft_String, const std::string _upWalk_String, const std::string _downWalk_String,
		std::string _TakeDamage_Right_String, std::string _TakeDamage_Left_String, std::string _TakeDamage_Up_String, std::string _TakeDamage_Down_String, std::string _Death_String,
		std::string _righ_attack_String, std::string _left_attack_String, std::string _up_attack_String, std::string _down_attack_String, int X, int Y, float _speed, int _health);

	void EnemyUpdate(float time, Player& player);

	void EnemyTakeDamage();

	void EnemyAnimation(float CurentFrame, float time);

	void TakeDamageAnimation(float CurentFrame, float time);

	void DeathAnimation(float CurentFrame, float time);

	void AttackAnimation(float CurentFrame, Player& p1);
};