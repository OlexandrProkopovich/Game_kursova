cmake_minimum_required(VERSION 3.25)

project(TopDownGame)

add_executable(TopDownGame_exe main.cpp
    Player.cpp
    Enemy.cpp 
    Bullet.cpp 
    GameMenu.cpp 
    Interface.cpp 
    lifeBar.cpp
    Button.cpp
    PlayerDAO.cpp
    players.cpp
)



target_sources(TopDownGame_exe PRIVATE C:/Users/sasha/Desktop/TopDownShooter/Bullet.h 
C:/Users/sasha/Desktop/TopDownShooter/Enemy.h 
C:/Users/sasha/Desktop/TopDownShooter/GameMenu.h
C:/Users/sasha/Desktop/TopDownShooter/Interface.h
C:/Users/sasha/Desktop/TopDownShooter/lifeBar.h 
C:/Users/sasha/Desktop/TopDownShooter/Player.h 
C:/Users/sasha/Desktop/TopDownShooter/sql.hpp 
C:/Users/sasha/Desktop/TopDownShooter/func.h
C:/Users/sasha/Desktop/TopDownShooter/Bonus.hpp
C:/Users/sasha/Desktop/TopDownShooter/Button.hpp
C:/Users/sasha/Desktop/TopDownShooter/PlayerDAO.hpp
C:/Users/sasha/Desktop/TopDownShooter/players.hpp
)    

set(SFML_DIR "C:/Users/sasha/Desktop/TopDownShooter/SFML-2.6.1")
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "C:/Users/sasha/Desktop/project/mysql-connector-c++-8.0.30-winx64/mysql-connector-c++-8.0.30-winx64")

include_directories(${SFML_DIR}/include
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/jdbc
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/jdbc/cppconn
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/mysql
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/mysqlx
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/mysqlx/common 
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/mysqlx/devapi
)

link_directories(
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14
)

link_directories(
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64
)

link_directories(
    ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/bin
)

target_link_libraries(TopDownGame_exe ${SFML_DIR}/lib/sfml-graphics.lib
${SFML_DIR}/lib/sfml-window.lib
${SFML_DIR}/lib/sfml-audio.lib
${SFML_DIR}/lib/sfml-system.lib
${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14/mysqlcppconn8.lib
${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14/libcrypto.lib
${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14/libssl.lib
${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14/mysqlcppconn.lib
${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14/mysqlcppconn8-static.lib
${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14/mysqlcppconn-static.lib
)

set_property(TARGET TopDownGame_exe PROPERTY CXX_STANDARD 14)

set_property(TARGET TopDownGame_exe PROPERTY CXX_STANDARD_REQUIRED ON)