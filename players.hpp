#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <vector>
#include <iostream>
#include <memory>


struct players
{
    int player_id;
    std::string player_name;
};

class players_DAO
{
public:
    virtual ~players_DAO() = default;
    virtual void add_player(players& player1) = 0;
    virtual std::vector<players> dispaly_results() = 0;
    virtual int getId(const players& player) = 0;
    virtual std::string getName(const players& player) = 0;
};


class players_SQL : public players_DAO
{
private:
    std::unique_ptr<sql::mysql::MySQL_Driver> driver;
    std::unique_ptr<sql::Connection> con;
public:
    players_SQL(const std::string& host, const std::string& user, const std::string& password, const std::string& db_name);
    ~players_SQL() override;
    void add_player(players& player1) override;
    std::vector<players> dispaly_results() override;
    int getId(const players& player) override;
    std::string getName(const players& player) override;
};
