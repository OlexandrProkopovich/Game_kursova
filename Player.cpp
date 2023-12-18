#include "Player.h"


Player::Player(std::string Idle_String, std::string walkRight_String, std::string walkLeft_String, std::string upWalk_String, std::string downWalk_String, float _speed,
    int X, int Y, float W, float H, int _health, sf::RenderWindow& Play, std::string _down_attack, std::string _up_attack, std::string _left_attack, std::string _righ_attack, std::string _TakeDamage_Right_String,
    std::string _TakeDamage_Left_String, std::string _TakeDamage_Up_String, std::string _TakeDamage_Down_String, std::string _Death_String) : Play(Play),
    Idle_String(Idle_String), walkRight_String(walkRight_String), walkLeft_String(walkLeft_String), upWalk_String(upWalk_String),
    downWalk_String(downWalk_String), speed(_speed), x(X), y(Y), w(W), h(H), down_attack_String(_down_attack), up_attack_String(_up_attack), left_attack_String(_left_attack),
    righ_attack_String(_righ_attack), TakeDamage_Right_String(_TakeDamage_Right_String), TakeDamage_Left_String(_TakeDamage_Left_String),
    TakeDamage_Up_String(_TakeDamage_Up_String), TakeDamage_Down_String(_TakeDamage_Down_String), Death_String(_Death_String), health(_health)
{
    Death_Image.loadFromFile(Death_String);
    Death_Texture.loadFromImage(Death_Image);

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

    Hero_Sprite.setScale(1.8, 1.8);
    Hero_Sprite.setPosition(x, y);
}

void Player::Update(float time)
{
    if(!isDead){
	if (dir == 0) //right
	{ 
		dx = speed; dy = 0;
	}
	else
	if (dir == 1) // left
	{
		 dx = -speed; dy = 0;	
	}
	else
	if (dir == 2) // down
	{
		dx = 0; dy = speed;
	}
	else
	if (dir == 3) //up
	{
		 dx = 0; dy = -speed;
	}
	else
    if (dir == 4) //idle
	{
		dx = 0; dy = 0;				
	}

	float new_x = x + dx * time;
	float new_y = y + dy * time;


	if (new_x < -48)
		new_x = Play.getSize().x;
	else if (new_x > Play.getSize().x)
		new_x = -48;

	if (new_y < -48)
		new_y = Play.getSize().y;
	else if (new_y > Play.getSize().y)
		new_y = -48;

	x = new_x;
	y = new_y;

	Hero_Sprite.setPosition(x, y);
    }
}

void Player::Animation(float time, float CurentFrame)
{
    if(!isDead){
    int framesInTexture = 6;  // Замініть це значення на реальну кількість кадрів у вашій текстурі анімації
    if (dir == 0) {
        Hero_Sprite.setTexture(walkRight_Texture); 
        if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
        Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
    }
    else if (dir == 1) {
        Hero_Sprite.setTexture(walkLeft_Texture);
        if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
        Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
    }
    else if (dir == 2) {
        Hero_Sprite.setTexture(downWalk_Texture);
        if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
        Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
    }
    else if (dir == 3) {
        Hero_Sprite.setTexture(upWalk_Texture);
        if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
        Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
    }
    else if (dir == 4) {
        Hero_Sprite.setTexture(Idle_Texture); Hero_Sprite.setScale(1.8, 1.8);
        if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
        Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
    }
    }
}


void Player::AttackAnimation(float time, float CurentFrame) {
    if (isShooting && !isDead)
    {
        int framesInTexture = 5;  // Замініть це значення на реальну кількість кадрів у вашій текстурі анімації
        if (dir == 0) {
            Hero_Sprite.setTexture(righ_attack_Texture); 
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 1) {
            Hero_Sprite.setTexture(left_attack_Texture);  
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 2) {
            Hero_Sprite.setTexture(down_attack_Texture);  
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 3) {
            Hero_Sprite.setTexture(up_attack_Texture);  
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 4) {
            Hero_Sprite.setTexture(down_attack_Texture); 
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
    }
}


void Player::TakeDamageAnimation(float CurentFrame, float time) {
    if (TakeDamage && !isDead) {
        int framesInTexture = 4;
        if (dir == 0) {
            Hero_Sprite.setTexture(TakeDamage_Right_Texture); 
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false; }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 1) {
            Hero_Sprite.setTexture(TakeDamage_Left_Texture); 
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false;
            }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 3) {
            Hero_Sprite.setTexture(TakeDamage_Up_Texture);
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false;
            }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 2) {
            Hero_Sprite.setTexture(TakeDamage_Down_Texture);
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false;
            }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
        else if (dir == 4) {
            Hero_Sprite.setTexture(TakeDamage_Down_Texture); 
            if (CurentFrame >= framesInTexture) { CurentFrame -= framesInTexture; TakeDamage = false;
            }
            Hero_Sprite.setTextureRect(sf::IntRect(48 * static_cast<int>(CurentFrame), 0, 48, 48));
        }
    }
    else if (isDead)
    {
        Hero_Sprite.setTexture(Death_Texture);
    }
}

void Player::DeathAnimation(float CurentFrame) {
    const int framesInTexture = 8;

    if (isDead && !deathAnimationFinished)
    {
        speed = 0;
        Hero_Sprite.setTexture(Death_Texture);

        if (CurentFrame >= framesInTexture)
        {
            CurentFrame = framesInTexture - 0.01; // Незначний зсув для коректного виведення останнього кадру
            deathAnimationFinished = true;
        }

        const int frameIndex = static_cast<int>(CurentFrame);
        Hero_Sprite.setTextureRect(sf::IntRect(48 * frameIndex, 0, 48, 48));
    }
}

void Player::startAttack() {
	isShooting = true;
}

void Player::stopAttack() {
	isShooting = false;
}