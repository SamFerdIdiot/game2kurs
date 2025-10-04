#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "UI/MainMenu.h"

class Game {
public:
    Game();
    void run();
    
private:
    void processEvents();
    void update();
    void render();
    
    sf::RenderWindow window;
    sf::Font font;
    MainMenu mainMenu;
    
    enum class GameState {
        MainMenu,
        Playing,
        Paused
    };
    
    GameState currentState = GameState::MainMenu;
};

#endif
