#include "Game/Game.h"
#include <iostream>

constexpr unsigned int Game::WINDOW_WIDTH;
constexpr unsigned int Game::WINDOW_HEIGHT;

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Road Fury")
    , backgroundSprite(backgroundTexture)
    , mainMenu(font)
    , vehicleSelection(font)
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
        
        switch (currentState) {
            case GameState::MainMenu:
                mainMenu.handleInput(*event);
                break;
            case GameState::VehicleSelection:
                vehicleSelection.handleInput(*event);
                break;
            case GameState::Playing:
                break;
            case GameState::Paused:
                break;
        }
    }
}

void Game::update() {
    switch (currentState) {
        case GameState::MainMenu:
            mainMenu.update();
            
            if (mainMenu.isOptionSelected()) {
                int selected = mainMenu.getSelectedOption();
                std::cout << "Menu option selected: " << selected << std::endl;
                
                switch (selected) {
                    case 0: // START NEW TRIP
                        std::cout << "START NEW TRIP." << std::endl;
                        currentState = GameState::VehicleSelection;
                        break;
                    case 1: // CONTINUE TRIP
                        std::cout << "CONTINUE TRIP" << std::endl;
                        // TODO: загрузка сохранения
                        break;
                    case 2: // SOUNDTRACK
                        std::cout << "SOUNDTRACK" << std::endl;
                        // TODO: меню звука
                        break;
                    case 3: // EXIT GARAGE
                        std::cout << "EXIT GARAGE" << std::endl;
                        window.close();
                        break;
                }
                
                mainMenu.resetSelection();
            }
            break;
            
        case GameState::VehicleSelection:
            vehicleSelection.update();
            
            if (vehicleSelection.isSelectionComplete()) {
                std::cout << "Vehicle selection complete!" << std::endl;
                std::cout << "Selected vehicle: " << vehicleSelection.getSelectedVehicle() << std::endl;
                std::cout << "Selected destination: " << vehicleSelection.getSelectedDestination() << std::endl;
                
                // TODO: переход к игровому процессу
                currentState = GameState::Playing;
            }
            break;
            
        case GameState::Playing:
            // TODO: игровая логика
            break;
            
        case GameState::Paused:
            // TODO: логика паузы
            break;
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 40));
    
    // Рисуем фон
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
        window.draw(backgroundSprite);
    }
    
    // Рисуем текущее состояние
    switch (currentState) {
        case GameState::MainMenu:
            mainMenu.render(window);
            break;
        case GameState::VehicleSelection:
            vehicleSelection.render(window);
            break;
        case GameState::Playing:
            // TODO: рендеринг игры
            break;
        case GameState::Paused:
            // TODO: рендеринг паузы
            break;
    }
    
    window.display();
}
