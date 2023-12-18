#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Bullet.h"
#include "Bonus.hpp"
#include <random>
#include "PlayerDAO.hpp"
#include "players.hpp"
#include "C:/Users/sasha/Desktop/Нова папка (3)/cpp-httplib/httplib.h"

void enemy_spawn_skeleton(float elapsedTime, const sf::RenderWindow& window, const Enemy& enemy, std::vector<Enemy>& enemies, sf::Clock& enemySpawnTimer) {
	int minSpawnInterval = 2000000;
	
	if (elapsedTime > minSpawnInterval)
	{
		int x = std::rand() % window.getSize().x;
		int y = std::rand() % window.getSize().y;


		Enemy newEnemy(enemy);
		newEnemy.Enemy_Sprite.setPosition(x, y);
		enemies.push_back(newEnemy);
		enemySpawnTimer.restart();
	}
}

void enemy_spawn_goblin(float elapsedTime, const sf::RenderWindow& window, const Enemy& enemy, std::vector<Enemy>& enemies, sf::Clock& enemySpawnTimer) {
	int minSpawnInterval = 3000000;

	if (elapsedTime > minSpawnInterval)
	{
		int x = std::rand() % window.getSize().x;
		int y = std::rand() % window.getSize().y;


		Enemy newEnemy(enemy);
		newEnemy.Enemy_Sprite.setPosition(x, y);
		enemies.push_back(newEnemy);
		enemySpawnTimer.restart();
	}
}


void enemy_spawn_Big_skeleton(float elapsedTime, const sf::RenderWindow& window, const Enemy& enemy, std::vector<Enemy>& enemies, sf::Clock& enemySpawnTimer) {
	int minSpawnInterval = 20000000;

	if (elapsedTime > minSpawnInterval)
	{
		int x = std::rand() % window.getSize().x;
		int y = std::rand() % window.getSize().y;


		Enemy newEnemy(enemy);
		newEnemy.Enemy_Sprite.setPosition(x, y);
		enemies.push_back(newEnemy);
		enemySpawnTimer.restart();
	}
}


void limit_player_hp(Player& p1)
{
	if (p1.health > 20)
	{
		p1.health = 20;
	}
}

void enemy_update(std::vector<Enemy>& enemies, float time, Player& p1, float CurentFrame)
{
	for (auto& enemy : enemies)
	{
		enemy.EnemyUpdate(time, p1);
		enemy.EnemyAnimation(CurentFrame, time);
		enemy.TakeDamageAnimation(CurentFrame, time);
		enemy.DeathAnimation(CurentFrame, time);
		enemy.AttackAnimation(CurentFrame, p1);
	}
}

void enemy_draw(sf::RenderWindow& window, const std::vector<Enemy>& enemies)
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{
		window.draw(it->Enemy_Sprite);
	}
}

void bullet_spawn(const Bullet& bullet, std::vector <Bullet>& bullets, float elapsedTime1, sf::Clock& attackcoldown_clocl, const Player& p1)
{
	int AttackColdown = 500000;
	if (elapsedTime1 > AttackColdown) {
		Bullet newBullet(bullet);
		bullets.push_back(newBullet);
		attackcoldown_clocl.restart();
	}
}

void bullet_update_array(float time, float CurentFrame, std::vector<Bullet>& bullets, const std::vector<Enemy>& enemies)
{
	for(auto& bullet : bullets)
	{
		bullet.BulletUpdate_array(time, enemies);
		bullet.BulletAnimation(time, CurentFrame);
	}

}

void buller_draw(sf::RenderWindow& window, std::vector<Bullet>& bullets)
{
	for (size_t i = 0; i < bullets.size(); ++i) {
		window.draw(bullets[i].Bullet_Sprite);
	}
}

bool CheckCollision_array(const sf::Sprite& bulletSprite, std::vector<Enemy>& enemies)
{
	for (auto& enemy : enemies)
	{
		sf::FloatRect bulletBounds = bulletSprite.getGlobalBounds();
		sf::FloatRect enemyBounds = enemy.Enemy_Sprite.getGlobalBounds();

		enemyBounds.top += 28;
		enemyBounds.left += 39;
		enemyBounds.height = 25;
		enemyBounds.width = 8;

		if (bulletBounds.intersects(enemyBounds))
		{
			enemy.EnemyTakeDamage();
			return true;
		}
	}

	// No collision detected with any enemy
	return false;

}

void CheckCollision(std::vector<Bullet>& bullets, std::vector<Enemy>& enemies)
{
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		if (CheckCollision_array(it->Bullet_Sprite, enemies))
		{
			it = bullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}
bool CheckCollision_bonus(const sf::Sprite& player_sprite, sf::Sprite bonus_sprite)
{
	sf::FloatRect Player_Bounds = player_sprite.getGlobalBounds();
	sf::FloatRect Bonus_Bounds = bonus_sprite.getGlobalBounds();

	if (Player_Bounds.intersects(Bonus_Bounds))
	{
		return true;
	}
	return false;

}





void checkEnemy_for_Life(std::vector<Enemy>& enemies)
{
	for (auto& enemy : enemies) {
		if (enemy.health <= 0)
		{
			enemy.isDead = true;
			enemy.deleteEnemy = true;
		}
	}
}

void CheckHero_forLife(Player& p1)
{
	if (p1.health <= 0)
	{
		p1.isDead = true;
	}
}

/*void Add_result(player_result_SQL& result_info, player_result& player_result, int time, int killedEnemy)
{
	player_result.time = time;
	player_result.killed_enemy = killedEnemy;
	result_info.add_result(player_result);
}

void displayResult(player_result_SQL& result_info)
{
	std::vector<player_result> result = result_info.dispaly_results_by_time();
	for (const auto& res : result)
	{
		std::cout << "Attemp: " << res.attemp << ", time: " << res.time <<
			", killed Enemy: " << res.killed_enemy << std::endl;
	}
}
*/

void Add_result(game_results_SQL& result_info, game_results& game_results, int player_id, int attempt, int killedEnemy, int game_time)
{
	game_results.player_id = player_id;
	game_results.attempt = attempt;
	game_results.enemies_killed = killedEnemy;
	game_results.game_time = game_time;

	result_info.add_result(game_results);
}

void Add_players(players_SQL& result_info, players& players, std::string name)
{
	players.player_name = name;
	result_info.add_player(players);
}

void add_res(players& p)
{
	const char* server_address = "http://localhost:3000";

	std::string playerName = p.player_name;

	httplib::Client client(server_address);

	httplib::Params params;
	params.emplace("playerName", playerName);

	auto res = client.Post("/addPlayer", params);

	if (res && res->status == 200) {
		std::cout << "Успішно: " << res->body << std::endl;
	}
	else {
		std::cerr << "Помилка при відправці запиту: ";
		if (res) {
			std::cerr << "HTTP статус " << res->status;
		}
		else {
			std::cerr << "Немає відповіді від сервера";
		}
		std::cerr << std::endl;
	}
}

void displayResult(game_results_SQL& result_info)
{
	std::vector<game_results> result = result_info.dispaly_results_by_time();
	for (const auto& res : result)
	{
		std::cout << "result_id: " << res.result_id << ", player_id: " << res.player_id <<
			", attempt: " << res.attempt << ", enemies_killed" <<  res.enemies_killed 
			<< ", game time" << res.game_time <<  std::endl;
	}
}

void displayResult(players_SQL& result_info, std::string name)
{
	std::vector<players> result = result_info.dispaly_results();
	for (const auto& res : result)
	{
		if (res.player_name == name)
		{
			std::cout << "not created" << std::endl;
		}
		else
		{
			std::cout << "created" << std::endl;
		}
	}
}

void spawnBonus_attack_speed(const Bonus& bonus, std::vector<Bonus>& bonus_array, sf::RenderWindow& window, float elapsedTime, sf::Clock& Timer)
{
	int minSpawnInterval = 22000000;

	if (elapsedTime > minSpawnInterval)
	{
		int x = std::rand() % window.getSize().x;
		int y = std::rand() % window.getSize().y;

		Bonus newBonus(bonus);
		newBonus.bonus_sprite.setPosition(x, y);
		newBonus.active = true; // Встановлення активності бонуса
		newBonus.duration_timer.restart(); // Запуск таймера тривалості
		bonus_array.push_back(newBonus);
		Timer.restart();
	}
}

void spawnBonus_attack_health(const Bonus& bonus, std::vector<Bonus>& bonus_array_health, sf::RenderWindow& window, float elapsedTime, sf::Clock& Timer)
{
	int minSpawnInterval = 11000000;

	if (elapsedTime > minSpawnInterval)
	{
		int x = std::rand() % window.getSize().x;
		int y = std::rand() % window.getSize().y;

		Bonus newBonus(bonus);
		newBonus.bonus_sprite.setPosition(x, y);
		newBonus.active = true; // Встановлення активності бонуса
		newBonus.duration_timer.restart(); // Запуск таймера тривалості
		bonus_array_health.push_back(newBonus);
		Timer.restart();
	}
}

void CheckColision_attack_speed_bonus(sf::FloatRect& playerBounds, std::vector<Bonus>& bonus_array_attack_speed, Bullet& bullet)
{
	for (size_t i = 0; i < bonus_array_attack_speed.size(); i++)
	{
		if (bonus_array_attack_speed[i].bonus_sprite.getGlobalBounds().intersects(playerBounds))
		{
			bullet.speed += 0.5;
			bonus_array_attack_speed.erase(bonus_array_attack_speed.begin() + i);
		}
	}
}


void CheckColision_attack_speed_healt(sf::FloatRect& playerBounds, std::vector<Bonus>& bonus_array_health, Player& player)
{
	for (size_t i = 0; i < bonus_array_health.size(); i++)
	{
		if (bonus_array_health[i].bonus_sprite.getGlobalBounds().intersects(playerBounds))
		{
			player.health += 5;
			bonus_array_health.erase(bonus_array_health.begin() + i);
		}
	}
}

void draw_bonus(const std::vector<Bonus> vector, sf::RenderWindow& window)
{
	for (auto& bonus : vector)
	{
		window.draw(bonus.bonus_sprite);
	}
}