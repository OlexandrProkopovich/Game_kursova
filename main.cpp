#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>  
#include <ctime>    
#include <locale>
#include <vector>
#include <list>
#include <sstream>
#include "Player.h"
#include "GameMenu.h"
#include "Interface.h"
#include "func.h"
#include "Enemy.h"
#include "lifeBar.h"
#include "Button.hpp"
#include "C:/Users/sasha/Desktop/Нова папка (3)/json/single_include/nlohmann/json.hpp"



std::string name;


void Statistic() {
	sf::RenderWindow stat(sf::VideoMode(1024, 1024), "Kursach");

	Interface background("images/background1.png", 1024, 1024);
	sf::Text Titul;
	background.WorkText("font/Maestroc.otf", Titul, 140, 50, L"PLAYER STATISTICS", 150, sf::Color(237, 147, 0), 0, sf::Color::Black);

	game_results_SQL result_info("localhost:3306", "root", "qwerty", "stat");
	players_SQL players_info("localhost:3306", "root", "qwerty", "stat");

	std::vector<game_results> results_time = result_info.dispaly_results_by_time();
	std::vector<game_results> results_killed_enemy = result_info.dispaly_results_by_killed_enemy();

	std::vector<sf::Text> text;
	sf::Font font;
	if (!font.loadFromFile("font/Maestroc.otf")) {
		std::cerr << "Failed to load font." << std::endl;
		return;
	}


	int recordsToDisplay = 10;
	int recordsDisplayed = 0;

	button SortByTime(150, 50, 50, 500, sf::Color::Black, sf::Color::White, "font/Maestroc.otf", "Sort by time", 20);
	button SortByKilledEnemy(150, 50, 50, 580, sf::Color::Black, sf::Color::White, "font/Maestroc.otf", "Sort by killed enemy", 20);

	while (stat.isOpen()) {
		sf::Event event_stat;
		while (stat.pollEvent(event_stat)) {
			if (event_stat.type == sf::Event::Closed) {
				stat.close();
			}
			if (event_stat.type == sf::Event::KeyPressed) {
				if (event_stat.key.code == sf::Keyboard::Escape) {
					stat.close();
				}
			}

			if (event_stat.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = stat.mapPixelToCoords(sf::Mouse::getPosition(stat));

				if (SortByTime._button.getGlobalBounds().contains(mousePos)) {
					httplib::Client client("http://localhost:3000");

					
					auto response = client.Get("/getTopResults");

					
					if (response && response->status == 200) {
					
						nlohmann::json jsonResults = nlohmann::json::parse(response->body);

						auto response = client.Get("/getTopResults");

						
						if (response && response->status == 200) {
						
							nlohmann::json jsonResults = nlohmann::json::parse(response->body);

							text.clear();
							recordsDisplayed = 0;
							int yOffset = 350;
							
							for (const auto& result : jsonResults) {
								if (recordsDisplayed >= recordsToDisplay) {
									break;
								}
								sf::Text resultText;
								resultText.setFont(font);
								resultText.setCharacterSize(30);
								resultText.setFillColor(sf::Color::Black);
								resultText.setPosition(230, yOffset);
								resultText.setString("Result ID: " + std::to_string(result["result_id"].get<int>()) +
									", Player ID: " + std::to_string(result["player_id"].get<int>()) +
									", Attempt: " + std::to_string(result["attempt"].get<int>()) +
									", Enemies Killed: " + std::to_string(result["enemies_killed"].get<int>()) +
									", Game Time: " + std::to_string(result["game_time"].get<int>()));

								text.push_back(resultText);
								yOffset += 50;
								recordsDisplayed++;
							}
						}
						else {
							std::cerr << "Error sending GET request" << std::endl;
							if (response) {
								std::cerr << "Status code: " << response->status << std::endl;
							}
						}	
					}
					else {
						std::cerr << "Error sending GET request" << std::endl;
						if (response) {
							std::cerr << "Status code: " << response->status << std::endl;
						}
					}
				}

				if (SortByKilledEnemy._button.getGlobalBounds().contains(mousePos)) {
					httplib::Client client("http://localhost:3000");

					// Відправка GET-запиту на '/getTopResults'
					auto response = client.Get("/getTopResults_killed_enemy");

					// Перевірка наявності помилок у відповіді
					if (response && response->status == 200) {

						nlohmann::json jsonResults = nlohmann::json::parse(response->body);


						
						if (response && response->status == 200) {
			
							nlohmann::json jsonResults = nlohmann::json::parse(response->body);

							text.clear();
							recordsDisplayed = 0;
							int yOffset = 350;

							for (const auto& result : jsonResults) {
								if (recordsDisplayed >= recordsToDisplay) {
									break;
								}
								sf::Text resultText;
								resultText.setFont(font);
								resultText.setCharacterSize(30);
								resultText.setFillColor(sf::Color::Black);
								resultText.setPosition(230, yOffset);
								resultText.setString("Result ID: " + std::to_string(result["result_id"].get<int>()) +
									", Player ID: " + std::to_string(result["player_id"].get<int>()) +
									", Attempt: " + std::to_string(result["attempt"].get<int>()) +
									", Enemies Killed: " + std::to_string(result["enemies_killed"].get<int>()) +
									", Game Time: " + std::to_string(result["game_time"].get<int>()));

								text.push_back(resultText);
								yOffset += 50;
								recordsDisplayed++;
							}
						}
						else {
							std::cerr << "Error sending GET request" << std::endl;
							if (response) {
								std::cerr << "Status code: " << response->status << std::endl;
							}
						}
					}
					else {
						std::cerr << "Error sending GET request" << std::endl;
						if (response) {
							std::cerr << "Status code: " << response->status << std::endl;
						}
					}
				}
			}
		}

		stat.clear();
		stat.draw(background.background);
		stat.draw(Titul);

		stat.draw(SortByTime._button);
		stat.draw(SortByTime.text);

		stat.draw(SortByKilledEnemy._button);
		stat.draw(SortByKilledEnemy.text);

		for (auto& tex : text) {
			stat.draw(tex);
		}
		stat.display();
	}
}

void GameStart(players& p)
{
	sf::RenderWindow Play(sf::VideoMode(1024, 1024), "Kursach");
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	sf::Music music;
	
	Player p1("images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Down/Png/Idle.png", "images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Right/Png/walk.png",
		"images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Left/Png/walk.png", "images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Up/Png/walk.png",
		"images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Down/Png/walk.png", 0.2,  900, 900, 48, 48, 20, Play, "images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Down/Png/down_attack.png",
		"images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Up/Png/up_attack.png", "images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Left/Png/left_attack.png",
		"images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Right/Png/right_attack.png", "images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Right/Png/hurt.png",
		"images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Left/Png/hurt.png", "images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Up/Png/hurt.png",
		"images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Down/Png/hurt.png",
		"images/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Foozle_2DC0011_Lucifer_Sorceress_Pixel_Art/Down/Png/Death.png");

	Enemy enemy1("images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Down/Png/Idle.png", "images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Right/Png/right_run.png",
		"images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Left/Png/left_run.png", "images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Up/Png/up_run.png",
		"images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Down/Png/down_run.png", "images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Right/Png/take_damage.png", 
		"images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Left/Png/take_damage.png", "images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Up/Png/take_damage.png", 
		"images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Down/Png/down_run.png", "images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Down/Png/Death.png",
		"images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Right/Png/attack.png", "images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Left/Png/attack.png", 
		"images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Up/Png/attack.png", "images/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Foozle_2DC0018_Lucifer_Skeleton_Grunt_Pixel_Art/Down/Png/attack.png", 400, 400, 0.1, 12);


	Enemy enemy2("images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Down/Png/Idle.png", "images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Right/Png/right_run.png",
		"images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Left/Png/left_run.png", "images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Up/Png/up_run.png",
		"images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Down/Png/down_run.png", "images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Right/Png/take_damage.png",
		"images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Left/Png/take_damage.png", "images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Up/Png/take_damage.png",
		"images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Down/Png/down_run.png", "images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Down/Png/Death.png",
		"images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Right/Png/attack.png", "images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Left/Png/attack.png",
		"images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Up/Png/attack.png", "images/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Foozle_2DC0015_Lucifer_Goblin_Berserker_Pixel_Art/Down/Png/attack.png", 400, 400, 0.1, 16);

	Enemy enemy3("images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Down/Png/Idle.png", "images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Right/Png/right_run.png",
		"images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Left/Png/left_run.png", "images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Up/Png/up_run.png",
		"images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Down/Png/down_run.png", "images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Right/Png/take_damage.png",
		"images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Left/Png/take_damage.png", "images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Up/Png/take_damage.png",
		"images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Down/Png/down_run.png", "images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Down/Png/Death.png",
		"images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Right/Png/attack.png", "images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Left/Png/attack.png",
		"images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Up/Png/attack.png", "images/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Foozle_2DC0021_Lucifer_Skeleton_King_Pixel_Art/Down/Png/attack.png", 400, 400, 0.1, 32);

	std::vector<Enemy> enemies;
	int enemiesKilled = 0;

	Bullet fireBall("images/fire/Right.png", "images/fire/Left.png", "images/fire/Up.png", "images/fire/Down.png", 1);
	std::vector<Bullet> bullets;

	Interface background("images/background2.png", 1024, 1024);

	sf::Text text;
	background.WorkText("font/Maestroc.otf", text, 17, 0, L"time in game: ", 50, sf::Color::Black, 0, sf::Color::Black);

	lifeBar life_bar (800, 25, "images/life_bar.png");

	Bonus speed_attack(0, 0, "images/battle.png");
	std::vector<Bonus> bonus_array_attack_speed;

	Bonus Health(0, 0, "images/heart.png");
	std::vector<Bonus> bonus_array_health;

	game_results_SQL game_info("localhost:3306", "root", "qwerty", "stat");
	game_results game_results;

	float CurentFrame = 0;           // ігровий час
	sf::Clock clock;

	sf::Clock gameTimeClock_in_second; // дисплейний час
	int gameTime_in_second = 0; 

	sf::Clock enemySpawnTimer_skeleton;    // кулдаун спавну ворогів (скелета)
	sf::Clock enemySpawnTimer_goblin;    // кулдаун спавну ворогів (гобліна)
	sf::Clock enemySpawnTimer_Big_skeleton;    // кулдаун спавну ворогів (Великого скелета)

	sf::Clock AttackColdown;    // кулдаун спавну кулі

	sf::Clock Bonus_health_Coldown;    // кулдаун спавну бонусу хп

	sf::Clock Bonus_attack_speed_Coldown;    // кулдаун спавну бонусу швидеості атаки

	while (Play.isOpen())
	{
		sf::sleep(sf::milliseconds(16));
		float time = clock.getElapsedTime().asMicroseconds();          //час гри
		clock.restart();
		time /= 800;

		life_bar.Update_LifeBar(p1);

		CurentFrame += time * 0.005;
		if (CurentFrame >= 8.1)
		{
			CurentFrame -= 8;
		}

		gameTime_in_second = gameTimeClock_in_second.getElapsedTime().asSeconds();  // час у грі(таймер)

		float elapsedTime_skeleton = enemySpawnTimer_skeleton.getElapsedTime().asMicroseconds(); // для часу спавну ворогів (скелета)

		float elapsed_Time_goblin = enemySpawnTimer_goblin.getElapsedTime().asMicroseconds();   // для часу спавну ворогів (гобліна)

		float elapsed_Time_Big_skeleton = enemySpawnTimer_Big_skeleton.getElapsedTime().asMicroseconds();   // для часу спавну ворогів (Великого скелета)

		float elapsedTime1 = AttackColdown.getElapsedTime().asMicroseconds();	// для кулдауна атаки

		float elapsedTime_bonus_health = Bonus_health_Coldown.getElapsedTime().asMicroseconds();

		float elapsedTime_bonus_attack_speed = Bonus_attack_speed_Coldown.getElapsedTime().asMicroseconds();

		sf::Event event_play;
		while (Play.pollEvent(event_play))
		{
			if (event_play.type == sf::Event::Closed) { Play.close(); }
			if (event_play.type == sf::Event::KeyPressed)
			{
				if (event_play.key.code == sf::Keyboard::Escape) {
					Play.close(); std::cout << gameTime_in_second << std::endl;

					std::cout << "You killed: " <<  enemiesKilled << " Enemies"<< std::endl;
					/*game_results.player_id = players1.player_id;
					game_results.game_time = gameTime_in_second;
					game_results.enemies_killed = enemiesKilled;
					game_info.add_result(game_results);*/
					
					const char* server_address = "http://localhost:3000";

					
					httplib::Client client(server_address);
					httplib::Params params;
					params.emplace("playerID", std::to_string(p.player_id)); 
					params.emplace("enemiesKilled", std::to_string(enemiesKilled)); 
					params.emplace("gameTime", std::to_string(gameTime_in_second));

					auto res = client.Post("/addGameResult", params);

					if (res && res->status == 200) {
						std::cout << "Server response: " << res->body << std::endl;
					}
					else {
						std::cerr << "Error connecting to the server" << std::endl;
						if (res) {
							std::cerr << "HTTP status code: " << res->status << std::endl;
						}
					}
					
				}
			}
		}

		p1.dir = 4;
		if (p1.dir == 4)
		{
			p1.Animation(time, CurentFrame);
			p1.AttackAnimation(time, CurentFrame);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
			p1.dir = 1; 
			p1.Animation(time, CurentFrame);
			p1.AttackAnimation(time, CurentFrame);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))))
		{
			p1.dir = 0; 
			p1.Animation(time, CurentFrame);
			p1.AttackAnimation(time, CurentFrame);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))))
		{
			p1.dir = 3; 
			p1.Animation(time, CurentFrame);
			p1.AttackAnimation(time, CurentFrame);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))))
		{
			p1.dir = 2; 
			p1.Animation(time, CurentFrame);
			p1.AttackAnimation(time, CurentFrame);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			p1.startAttack();
			fireBall.SetBulletPosition(p1);
			bullet_spawn(fireBall, bullets, elapsedTime1, AttackColdown, p1);
		}
		else {
			p1.stopAttack();
		}

		p1.Update(time);
		

		enemy_spawn_skeleton(elapsedTime_skeleton, Play, enemy1, enemies, enemySpawnTimer_skeleton);
		enemy_spawn_goblin(elapsed_Time_goblin, Play, enemy2, enemies, enemySpawnTimer_goblin);
		enemy_spawn_Big_skeleton(elapsed_Time_Big_skeleton, Play, enemy3, enemies, enemySpawnTimer_Big_skeleton);
		
		spawnBonus_attack_speed(speed_attack, bonus_array_attack_speed, Play, elapsedTime_bonus_attack_speed, Bonus_attack_speed_Coldown);
		spawnBonus_attack_health(Health, bonus_array_health, Play, elapsedTime_bonus_health, Bonus_health_Coldown);

		if (p1.isDead)
		{
			// Вивести повідомлення та розмиття фону
			sf::Text gameOverText;
			background.WorkText("font/Rusted Sabbath.otf", gameOverText, 170, 300, L"YOU DIIIEEE", 180, sf::Color::Red, 0, sf::Color::Black);

			sf::RectangleShape blurRect(sf::Vector2f(1024, 1024));
			blurRect.setFillColor(sf::Color(255, 255, 255, 200)); // Альфа-канал для розмиття

			while (Play.isOpen())
			{
				sf::Event event_game_over;
				while (Play.pollEvent(event_game_over))
				{
					if (event_game_over.type == sf::Event::Closed) { Play.close(); }
					if (event_game_over.type == sf::Event::KeyPressed)
					{
						if (event_game_over.key.code == sf::Keyboard::Escape) { Play.close(); }
					}
				}

				Play.clear();
				Play.draw(background.background);
				Play.draw(p1.Hero_Sprite);
				buller_draw(Play, bullets);
				enemy_draw(Play, enemies);
				Play.draw(life_bar.LifeBar);
				Play.draw(text);

				// Розмиття фону
				Play.draw(blurRect);

				// Виведення повідомлення
				Play.draw(gameOverText);

				Play.display();
			}
		}

		bullet_update_array(time, CurentFrame, bullets, enemies);

		CheckCollision(bullets, enemies);

		checkEnemy_for_Life(enemies);
		

		auto it = std::remove_if(enemies.begin(), enemies.end(), [&enemiesKilled](const Enemy& enemy) {
			if (enemy.deathAnimationFinished && enemy.isDead) {
				enemiesKilled++;
				return true; 
			}
			return false;  
			});

		enemies.erase(it, enemies.end());

		sf::FloatRect playerBounds = p1.Hero_Sprite.getGlobalBounds();
		CheckColision_attack_speed_bonus(playerBounds, bonus_array_attack_speed, fireBall);

		CheckColision_attack_speed_healt(playerBounds, bonus_array_health, p1);
		limit_player_hp(p1);
		
		enemy_update(enemies, time, p1, CurentFrame);

		p1.TakeDamageAnimation(CurentFrame, time);

		CheckHero_forLife(p1);

		p1.DeathAnimation(CurentFrame);
		
		std::ostringstream gameTimeStringInSecond;
		gameTimeStringInSecond << gameTime_in_second;
		text.setString("Time in game: " + gameTimeStringInSecond.str());
		text.setFillColor(sf::Color::White);

		Play.clear();
		Play.draw(background.background);
		draw_bonus(bonus_array_attack_speed, Play);
		draw_bonus(bonus_array_health, Play);
		Play.draw(p1.Hero_Sprite);
		buller_draw(Play, bullets);
		enemy_draw(Play, enemies);
		Play.draw(life_bar.LifeBar);
		Play.draw(text);
		Play.display();
	}
}



std::string GetPlayerName()
{
	sf::RenderWindow nameWindow(sf::VideoMode(400, 200), "Enter Your Name");
	sf::Font font;
	if (!font.loadFromFile("font/Maestroc.otf"))
	{
		std::cerr << "Failed to load font." << std::endl;
		return "";
	}

	sf::Text nameLabel;
	nameLabel.setFont(font);
	nameLabel.setCharacterSize(30);
	nameLabel.setFillColor(sf::Color::White);
	nameLabel.setPosition(50, 50);
	nameLabel.setString("Enter Your Name:");

	sf::Text inputText;
	inputText.setFont(font);
	inputText.setCharacterSize(30);
	inputText.setFillColor(sf::Color::White);
	inputText.setPosition(50, 100);

	std::string playerName;

	while (nameWindow.isOpen())
	{
		sf::Event event;
		while (nameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				nameWindow.close();
				playerName = "";
			}
			if (event.key.code == sf::Keyboard::Return)
			{
				if (event.key.code == sf::Keyboard::Enter) { 
					nameWindow.close();
					
				}
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128 && event.text.unicode != 8) 
				{
					playerName += static_cast<char>(event.text.unicode);
					inputText.setString(playerName);
				}
				else if (event.text.unicode == 8 && !playerName.empty()) 
				{
					playerName.pop_back();
					inputText.setString(playerName);
				}
			}
		}

		nameWindow.clear();
		nameWindow.draw(nameLabel);
		nameWindow.draw(inputText);
		nameWindow.display();
	}

	return playerName;
}



int main()
{
	std::locale::global(std::locale(""));
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "TestSFML");

	Interface background("images/background1.png", 1024, 1024);

	sf::Text Titul;
	background.WorkText("font/Maestroc.otf", Titul, 230, 100, L"SHOOT AND RUN", 130, sf::Color(240, 147, 0), 0, sf::Color::Black);

	std::vector<sf::String> name_button = { L"Нова гра", L"Результати", L"Вийти" };

	game::GameMenu mymenu(window, 500, 400, 100, 120, name_button);
	mymenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);
	mymenu.AlignMenu(2);



	players_SQL players_info("localhost:3306", "root", "qwerty", "stat");
	
	players players1;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { window.close(); }
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); }
				if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); }
				if (event.key.code == sf::Keyboard::Return)
				{
					switch (mymenu.getSelectedMenuNumber())
					{
					case 0:
						players1.player_name = GetPlayerName();
						//players_info.add_player(players1);
						add_res(players1);
						players1.player_id = players_info.getId(players1);
						std::cout << players1.player_id << std::endl;
						GameStart(players1);
						break;
					case 1: Statistic(); break;
					case 2: window.close(); break;
					}
				}
			}
		}

		window.clear();
		window.draw(background.background);
		window.draw(Titul);
		mymenu.draw();
		window.display();
	}

	return 0;
}
