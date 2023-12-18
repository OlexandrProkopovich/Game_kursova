#include "PlayerDAO.hpp"

game_results_SQL::game_results_SQL(const std::string& host, const std::string& user, const std::string& password, const std::string& db_name)
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


game_results_SQL::~game_results_SQL() {}
void game_results_SQL::add_result(game_results result)
{
    try
    {
        // Перевірте, чи гравець вже існує в базі даних
        std::unique_ptr<sql::PreparedStatement> stmtCheck(con->prepareStatement("SELECT * FROM game_results WHERE player_id = ?"));
        stmtCheck->setInt(1, result.player_id);

        std::unique_ptr<sql::ResultSet> resCheck(stmtCheck->executeQuery());

        if (resCheck->next()) {

            int currentAttempts = resCheck->getInt("attempt");
            result.attempt = currentAttempts + 1;

            // Гравець вже існує, вставте новий запис
            std::unique_ptr<sql::PreparedStatement> stmtInsert(con->prepareStatement("INSERT INTO game_results(player_id, attempt, enemies_killed, game_time) VALUES (?, ?, ?, ?)"));
            stmtInsert->setInt(1, result.player_id);
            stmtInsert->setInt(2, result.attempt);  // Тут вже використовується result.attempt, оновлене значення
            stmtInsert->setInt(3, result.enemies_killed);
            stmtInsert->setInt(4, result.game_time);
            stmtInsert->execute();
        }
        else {
            // Гравець не існує, вставте новий запис
            result.attempt = 1;

            std::unique_ptr<sql::PreparedStatement> stmtInsert(con->prepareStatement("INSERT INTO game_results(player_id, attempt, enemies_killed, game_time) VALUES (?, ?, ?, ?)"));
            stmtInsert->setInt(1, result.player_id);
            stmtInsert->setInt(2, result.attempt);  // Тут вже використовується result.attempt, стартове значення
            stmtInsert->setInt(3, result.enemies_killed);
            stmtInsert->setInt(4, result.game_time);
            stmtInsert->execute();
        }
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}


std::vector<game_results> game_results_SQL::dispaly_results_by_time()
{
    std::vector<game_results> result_array;
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM game_results ORDER BY game_time DESC"));

        while (res->next())
        {
            game_results result;
            result.result_id = res->getInt("result_id");
            result.player_id = res->getInt("player_id");
            result.attempt = res->getInt("attempt");
            result.enemies_killed = res->getInt("enemies_killed");
            result.game_time = res->getInt("game_time");
            result_array.push_back(result);
        }
        return result_array;
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}


std::vector<game_results> game_results_SQL::dispaly_results_by_killed_enemy()
{
    std::vector<game_results> result_array;
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM game_results ORDER BY enemies_killed DESC"));

        while (res->next())
        {
            game_results result;
            result.result_id = res->getInt("result_id");
            result.player_id = res->getInt("player_id");
            result.attempt = res->getInt("attempt");
            result.enemies_killed = res->getInt("enemies_killed");
            result.game_time = res->getInt("game_time");
            result_array.push_back(result);
        }
        return result_array;
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}