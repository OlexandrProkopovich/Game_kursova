#include "players.hpp"

players_SQL::players_SQL(const std::string& host, const std::string& user, const std::string& password, const std::string& db_name)
{
	try
	{
		driver = std::make_unique<sql::mysql::MySQL_Driver>();
		con = std::unique_ptr<sql::Connection>(driver->connect(host, user, password));
		con->setSchema(db_name);
	}
	catch(sql::SQLException& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

players_SQL::~players_SQL(){}

void players_SQL::add_player(players& player1)
{
	try
	{
		std::unique_ptr<sql::Statement> stmt(con->createStatement());
		std::unique_ptr<sql::ResultSet> res1(stmt->executeQuery("SELECT * FROM players"));

		bool playerExists = false;

		while (res1->next())
		{
			std::string existingPlayerName = res1->getString("player_name");
			if (player1.player_name == existingPlayerName)
			{
				player1.player_id = res1->getInt("player_id");
				std::cout << "Player with the same name already exists." << std::endl;
				playerExists = true;
				break;
			}
		}

		if (!playerExists)
		{
			stmt->execute("INSERT INTO players (player_name) VALUES ('" + player1.player_name + "')");
			player1.player_id = res1->getInt("player_id");
			std::cout << "Successfully created player: " << player1.player_name << std::endl;
		}
		
	}
	catch (sql::SQLException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


int players_SQL::getId(const players& player)
{
	players res;
	try
	{
		std::unique_ptr<sql::Statement> stmt(con->createStatement());
		std::unique_ptr<sql::ResultSet> res1(stmt->executeQuery("SELECT player_id FROM players WHERE player_name = '" + player.player_name +"'"));
		while (res1->next())
		{
			res.player_id = res1->getInt("player_id");
		}
		return res.player_id;
	}
	catch(sql::SQLException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::string players_SQL::getName(const players& player)
{
	players res;
	try
	{
		std::unique_ptr<sql::Statement> stmt(con->createStatement());
		std::unique_ptr<sql::ResultSet> res1(stmt->executeQuery("SELECT player_name FROM players WHERE player_id = '" + std::to_string(player.player_id) + "'"));
		while (res1->next())
		{
			res.player_name = res1->getString("player_name");
		}
		return res.player_name;
	}
	catch (sql::SQLException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::vector<players> players_SQL::dispaly_results()
{
	std::vector<players> result_array;
	try
	{
		std::unique_ptr<sql::Statement> stmt(con->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM players"));

		while (res->next())
		{
			players result;
			result.player_id = res->getInt("player_id");
			result.player_name = res->getInt("player_name");
			result_array.push_back(result);
		}
		return result_array;
	}
	catch(sql::SQLException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}