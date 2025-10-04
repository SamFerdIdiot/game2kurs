cmake_minimum_required(VERSION 3.10)
project(Game2kurs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/Game/Game.cpp
    src/UI/MainMenu.cpp
)

# Включаем папки
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

message(STATUS "Project structure configured successfully")