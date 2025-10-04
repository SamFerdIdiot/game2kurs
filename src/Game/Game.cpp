#include "Game/Game.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode({640, 360}), "Road Fury")
    , mainMenu(font)
{
    // Загрузка шрифта
    if (!font.openFromFile("assets/fonts/PressStart2P.ttf")) {
        std::cout << "PressStart2P font not loaded" << std::endl;
    }
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    if (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        
        if (currentState == GameState::MainMenu) {
            mainMenu.handleInput(*event);
        }
    }
}

void Game::update() {
    if (currentState == GameState::MainMenu) {
        mainMenu.update();
        
        if (mainMenu.isOptionSelected()) {
            int selected = mainMenu.getSelectedOption();
            std::cout << "Menu option selected: " << selected << std::endl;
            
            if (selected == 3) { // EXIT GARAGE
                window.close();
            }
            // Сбросим выбор для следующего раза
            mainMenu.resetSelection();
        }
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 40));
    
    if (currentState == GameState::MainMenu) {
        mainMenu.render(window);
    }
    
    window.display();
}
