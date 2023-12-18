#include "Bullet.h"
#include "Player.h"


Bullet::Bullet(std::string _bullet_Right, std::string _bullet_Left, std::string _bullet_Up, std::string _bullet_Down, float _speed) : bullet_Right(_bullet_Right), bullet_Left(_bullet_Left),
bullet_Up(_bullet_Up), bullet_Down(_bullet_Down), speed(_speed)
{
    bulletRight_image.loadFromFile(bullet_Right);
    bulletLeft_image.loadFromFile(bullet_Left);
    bulletUp_image.loadFromFile(bullet_Up);
    bulletDown_image.loadFromFile(bullet_Down);

    bulletRight_Texture.loadFromImage(bulletRight_image);
    bulletLeft_Texture.loadFromImage(bulletLeft_image);
    bulletUp_Texture.loadFromImage(bulletUp_image);
    bulletDown_Texture.loadFromImage(bulletDown_image);

    Bullet_Sprite.setTexture(bulletDown_Texture);
    Bullet_Sprite.setPosition(x, y);
}

void Bullet::SetBulletPosition(const Player& player) {
	Bullet_Sprite.setPosition(player.Hero_Sprite.getPosition().x + 24, player.Hero_Sprite.getPosition().y + 37);
}

float Bullet::getDistance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	return std::sqrt(dx * dx + dy * dy);
}

void Bullet::BulletUpdate_array(float time, const std::vector<Enemy>& enemies)
{
	if (enemies.empty())
	{
		return;
	}
    sf::Vector2f BulletPosition = Bullet_Sprite.getPosition();
    const Enemy* nearestEnemy = &enemies[0];
    float min_distance = std::numeric_limits<float>::max();

    for (auto& enemy : enemies)
    {
        float current_distance = getDistance(BulletPosition, enemy.Enemy_Sprite.getPosition());
        if (current_distance < min_distance)
        {
            nearestEnemy = &enemy;
            min_distance = current_distance;
        }
    }
    sf::Vector2f nearestEnemyPosition = nearestEnemy->Enemy_Sprite.getPosition();
	nearestEnemyPosition.x += 28;
	nearestEnemyPosition.y += 39;

    direction = nearestEnemyPosition - BulletPosition;
    sf::Vector2f normalizeDirection = direction / std::sqrt((direction.x * direction.x + direction.y * direction.y));

    float x = BulletPosition.x + time * speed * normalizeDirection.x;
    float y = BulletPosition.y + time * speed * normalizeDirection.y;

    Bullet_Sprite.setPosition(x, y);

}

void Bullet::BulletAnimation(float time, float CurentFrame) {
	if (direction.x > 0) {
		Bullet_Sprite.setTexture(bulletRight_Texture);
		CurentFrame += time * 0.005;
		if (CurentFrame >= 3) { CurentFrame -= 3; }
		Bullet_Sprite.setTextureRect(sf::IntRect(32 * (int)CurentFrame, 0, 32, 17));
	}
	else if (direction.x < 0) {
		Bullet_Sprite.setTexture(bulletLeft_Texture);
		CurentFrame += time * 0.005;
		if (CurentFrame >= 3) { CurentFrame -= 3; }
		Bullet_Sprite.setTextureRect(sf::IntRect(32 * (int)CurentFrame, 0, 32, 17));
	}
	else if (direction.y > 0) {
		Bullet_Sprite.setTexture(bulletDown_Texture);
		CurentFrame += time * 0.005;
		if (CurentFrame >= 3) { CurentFrame -= 3; }
		Bullet_Sprite.setTextureRect(sf::IntRect(0, 32 * (int)CurentFrame, 17, 32));
	}
	else if (direction.y < 0) {
		Bullet_Sprite.setTexture(bulletUp_Texture);
		CurentFrame += time * 0.005;
		if (CurentFrame >= 3) { CurentFrame -= 3; }
		Bullet_Sprite.setTextureRect(sf::IntRect(0, 32 * (int)CurentFrame, 17, 32));
	}
}