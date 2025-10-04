cmake_minimum_required(VERSION 3.10)
project(Game2kurs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Используем SFML 3.0.2 с правильными названиями компонентов (с заглавной буквы!)
find_package(SFML 3.0 COMPONENTS Graphics Window System Audio Network REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

# Линковка через современный синтаксис
target_link_libraries(${PROJECT_NAME} 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio 
    SFML::Network
)

message(STATUS "SFML 3.0.2 configured successfully!")