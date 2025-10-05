#include "Game/Game.h"
#include <iostream>

constexpr unsigned int Game::WINDOW_WIDTH;
constexpr unsigned int Game::WINDOW_HEIGHT;

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Road Fury")
    , backgroundSprite(backgroundTexture)
    , mainMenu(font)
{
    if (!font.openFromFile("assets/fonts/PressStart2P.ttf")) {
        std::cout << "PressStart2P font not loaded" << std::endl;
    }
    
    if (!loadTextures()) {
        std::cout << "Failed to load textures" << std::endl;
    }
}

bool Game::loadTextures() {
    if (!backgroundTexture.loadFromFile("assets/textures/background.jpg")) {
        std::cout << "Background JPG not found, using solid color background." << std::endl;
        return true;
    } else {
        std::cout << "JPG background loaded successfully!" << std::endl;
    }
    
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = {WINDOW_WIDTH, WINDOW_HEIGHT};
    
    if (textureSize != windowSize) {
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite.setScale({scaleX, scaleY});
        std::cout << "Scaled background from " << textureSize.x << "x" << textureSize.y
                  << " to window size " << windowSize.x << "x" << windowSize.y << std::endl;
    }
    
    return true;
}

void Game::run() {
    std::cout << "Game started successfully!" << std::endl;
    std::cout << "Window size: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;
    std::cout << "Controls: UP/DOWN arrows to navigate, ENTER to select" << std::endl;
    
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
            
            switch (selected) {
                case 0: std::cout << "Starting new game..." << std::endl; break;
                case 1: std::cout << "Continuing game..." << std::endl; break;
                case 2: std::cout << "Opening soundtrack menu..." << std::endl; break;
                case 3: std::cout << "Exiting game..." << std::endl; window.close(); break;
            }
            
            mainMenu.resetSelection();
        }
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 40));
    
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
        window.draw(backgroundSprite);
    }
    
    if (currentState == GameState::MainMenu) {
        mainMenu.render(window);
    }
    
    window.display();
}
