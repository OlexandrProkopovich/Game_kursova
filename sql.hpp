#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <vector>
#include <iostream>
#include <memory>

struct player_result
{
    int attemp;
    int time;
    int killed_enemy;
};

class player_result_DAO
{
public:
    virtual ~player_result_DAO() = default;
    virtual void add_result(player_result result) = 0;
    virtual std::vector<player_result> dispaly_results_by_time() = 0;
    virtual std::vector<player_result> dispaly_results_by_killed_enemy() = 0;
};


class player_result_SQL : public player_result_DAO
{
private:
    std::unique_ptr<sql::mysql::MySQL_Driver> driver;
    std::unique_ptr<sql::Connection> con;
public:
    player_result_SQL(const std::string& host, const std::string& user, const std::string& password, const std::string& db_name);
    ~player_result_SQL() override;
    void add_result(player_result result) override;
    std::vector<player_result> dispaly_results_by_time() override;
    std::vector<player_result> dispaly_results_by_killed_enemy() override;
};



player_result_SQL::player_result_SQL(const std::string& host, const std::string& user, const std::string& password, const std::string& db_name)
{
    try
    {
        driver = std::make_unique<sql::mysql::MySQL_Driver>();
        con = std::unique_ptr<sql::Connection>(driver->connect(host, user, password));
        con->setSchema(db_name);
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}


player_result_SQL::~player_result_SQL() {}

void player_result_SQL::add_result(player_result result)
{
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("INSERT INTO player_results(time, killed_enemy) VALUES ('" + std::to_string(result.time) + "', '" + std::to_string(result.killed_enemy) + "')");
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}


std::vector<player_result> player_result_SQL::dispaly_results_by_time()
{
    std::vector<player_result> result_array;
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM player_results ORDER BY time DESC"));

        while (res->next())
        {
            player_result result;
            result.attemp = res->getInt("id");
            result.time = res->getInt("time");
            result.killed_enemy = res->getInt("killed_enemy");
            result_array.push_back(result);
        }
        return result_array;
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}


std::vector<player_result> player_result_SQL::dispaly_results_by_killed_enemy()
{
    std::vector<player_result> result_array;
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM player_results ORDER BY killed_enemy DESC"));

        while (res->next())
        {
            player_result result;
            result.attemp = res->getInt("id");
            result.time = res->getInt("time");
            result.killed_enemy = res->getInt("killed_enemy");
            result_array.push_back(result);
        }
        return result_array;
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}