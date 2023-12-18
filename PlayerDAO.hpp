#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <vector>
#include <iostream>
#include <memory>


struct game_results
{
    int result_id;
    int player_id;
    int attempt;
    int enemies_killed;
    int game_time;
    
};

class game_results_DAO
{
public:
    virtual ~game_results_DAO() = default;
    virtual void add_result(game_results result) = 0;
    virtual std::vector<game_results> dispaly_results_by_time() = 0;
    virtual std::vector<game_results> dispaly_results_by_killed_enemy() = 0;
};


class game_results_SQL : public game_results_DAO
{
private:
    std::unique_ptr<sql::mysql::MySQL_Driver> driver;
    std::unique_ptr<sql::Connection> con;
public:
    game_results_SQL(const std::string& host, const std::string& user, const std::string& password, const std::string& db_name);
    ~game_results_SQL() override;
    void add_result(game_results result) override;
    std::vector<game_results> dispaly_results_by_time() override;
    std::vector<game_results> dispaly_results_by_killed_enemy() override;
};