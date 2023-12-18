#include "Enemy.h"


Enemy::Enemy(const std::string _Idle_String, const std::string _walkRight_String, const std::string _walkLeft_String, const std::string _upWalk_String, const std::string _downWalk_String,
	std::string _TakeDamage_Right_String, std::string _TakeDamage_Left_String, std::string _TakeDamage_Up_String, std::string _TakeDamage_Down_String, std::string _Death_String,
	std::string _righ_attack_String, std::string _left_attack_String, std::string _up_attack_String, std::string _down_attack_String, int X, int Y, float _speed, int _health) :
	Idle_String(_Idle_String), walkRight_String(_walkRight_String), walkLeft_String(_walkLeft_String), upWalk_String(_upWalk_String),
	downWalk_String(_downWalk_String), TakeDamage_Right_String(_TakeDamage_Right_String), TakeDamage_Left_String(_TakeDamage_Left_String),
	TakeDamage_Up_String(_TakeDamage_Up_String), TakeDamage_Down_String(_TakeDamage_Down_String), Death_String(_Death_String), righ_attack_String(_righ_attack_String),
	left_attack_String(_left_attack_String), up_attack_String(_up_attack_String), down_attack_String(_down_attack_String), x(X), y(Y), speed(_speed), health(_health)
{
	Idle_Image.loadFromFile(Idle_String);
	walkRight_Image.loadFromFile(walkRight_String);
	walkLeft_Image.loadFromFile(walkLeft_String);
	upWalk_Image.loadFromFile(upWalk_String);
	downWalk_Image.loadFromFile(downWalk_String);

	TakeDamage_Right_Image.loadFromFile(TakeDamage_Right_String);
	TakeDamage_Left_Image.loadFromFile(TakeDamage_Left_String);
	TakeDamage_Up_Image.loadFromFile(TakeDamage_Up_String);
	TakeDamage_Down_Image.loadFromFile(TakeDamage_Down_String);

	TakeDamage_Right_Texture.loadFromImage(TakeDamage_Right_Image);
	TakeDamage_Left_Texture.loadFromImage(TakeDamage_Left_Image);
	TakeDamage_Up_Texture.loadFromImage(TakeDamage_Up_Image);
	TakeDamage_Down_Texture.loadFromImage(TakeDamage_Down_Image);

	Death_Image.loadFromFile(Death_String);
	Death_Texture.loadFromImage(Death_Image);

	down_attack_Image.loadFromFile(down_attack_String);
	up_attack_Image.loadFromFile(up_attack_String);
	left_attack_Image.loadFromFile(left_attack_String);
	righ_attack_Image.loadFromFile(righ_attack_String);

	down_attack_Texture.loadFromImage(down_attack_Image);
	up_attack_Texture.loadFromImage(up_attack_Image);
	left_attack_Texture.loadFromImage(left_attack_Image);
	righ_attack_Texture.loadFromImage(righ_attack_Image);


	Idle_Texture.loadFromImage(Idle_Image);
	walkRight_Texture.loadFromImage(walkRight_Image);
	walkLeft_Texture.loadFromImage(walkLeft_Image);
	upWalk_Texture.loadFromImage(upWalk_Image);
	downWalk_Texture.loadFromImage(downWalk_Image);

	Enemy_Sprite.setTexture(Idle_Texture);
	Enemy_Sprite.setScale(1.9, 1.9);

	Enemy_Sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
	Enemy_Sprite.setPosition(x, y);
}

void Enemy::EnemyUpdate(float time, Player& player) {
	sf::Vector2f EnemyPosition = Enemy_Sprite.getPosition();
	sf::Vector2f HeroPosition = player.Hero_Sprite.getPosition();

	direction = HeroPosition - EnemyPosition;

	float distance = std::sqrt(std::pow(HeroPosition.x - EnemyPosition.x, 2) + std::pow(HeroPosition.y - EnemyPosition.y, 2));
	if (distance <= 75)
	{
		startAttack = true;
	}
	else
	{
		startAttack = false;

	}

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 0)
	{
		direction.x /= length;
		direction.y /= length;
	}

	sf::Vector2f newPosition = EnemyPosition + direction * speed * time;
	Enemy_Sprite.setPosition(newPosition);

}

void Enemy::EnemyAnimation(float CurentFrame, float time) {
	int framesInTexture = 6;
	if(!isDead){
		if (direction.x > 0) {
			Enemy_Sprite.setTexture(walkRight_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.x < 0) {
			Enemy_Sprite.setTexture(walkLeft_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.y > 0) {
			Enemy_Sprite.setTexture(downWalk_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.y < 0) {
			Enemy_Sprite.setTexture(upWalk_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
	}
	else if(isDead)
	{
		Enemy_Sprite.setTexture(Death_Texture);
	}
}

void Enemy::TakeDamageAnimation(float CurentFrame, float time) {
	if (TakeDamage && !isDead) {
		int framesInTexture = 4;
		if (direction.x > 0) {
			Enemy_Sprite.setTexture(TakeDamage_Right_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.x < 0) {
			Enemy_Sprite.setTexture(TakeDamage_Left_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.y > 0) {
			Enemy_Sprite.setTexture(TakeDamage_Up_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.y < 0) {
			Enemy_Sprite.setTexture(TakeDamage_Down_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
	}
	else if (isDead)
	{
		Enemy_Sprite.setTexture(Death_Texture);
	}
}

void Enemy::DeathAnimation(float CurentFrame, float time)
{
	const int framesInTexture = 8;

	if (isDead && !deathAnimationFinished)
	{
		speed = 0;
		Enemy_Sprite.setTexture(Death_Texture);
		
		if (CurentFrame >= framesInTexture)
		{
			CurentFrame = framesInTexture - 0.01; // Незначний зсув для коректного виведення останнього кадру
			deathAnimationFinished = true;
		}
		else {
			deathAnimationFinished = false;
		}

		const int frameIndex = static_cast<int>(CurentFrame);
		Enemy_Sprite.setTextureRect(sf::IntRect(48 * frameIndex, 0, 48, 48));
	}
}

void Enemy::EnemyTakeDamage()
{
	TakeDamage = true;
	health -= 4;
}

void Enemy::AttackAnimation(float CurentFrame, Player& p1)
{
	if (startAttack)
	{
		int framesInTexture = 8;
		if (direction.x > 0) {
			Enemy_Sprite.setTexture(righ_attack_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; p1.health -= 4; p1.TakeDamage = true;}
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.x < 0) {
			Enemy_Sprite.setTexture(left_attack_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; p1.health -= 4; p1.TakeDamage = true; }
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.y > 0) {
			
			Enemy_Sprite.setTexture(up_attack_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; p1.health -= 4;  p1.TakeDamage = true;}
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
		else if (direction.y < 0) {
		
			Enemy_Sprite.setTexture(down_attack_Texture); 
			if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; p1.health -= 4; p1.TakeDamage = true;}
			Enemy_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
		}
	}
}