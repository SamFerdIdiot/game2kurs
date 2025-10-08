#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "UI/MainMenu.h"
#include "States/VehicleSelection.h"

class Game {
public:
    Game();
    void run();
    
private:
    void processEvents();
    void update();
    void render();
    bool loadTextures();
    
    static constexpr unsigned int WINDOW_WIDTH = 2560;
    static constexpr unsigned int WINDOW_HEIGHT = 1600;
    
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    MainMenu mainMenu;
    VehicleSelection vehicleSelection;
    
    enum class GameState {
        MainMenu,
        VehicleSelection,
        Playing,
        Paused
    };
    
    GameState currentState = GameState::MainMenu;
};

#endif
