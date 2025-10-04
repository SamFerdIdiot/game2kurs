#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({640, 360}), "Road Fury");
    
    // Используем шрифт из папки build/assets
    sf::Font font;
    if (!font.openFromFile("assets/fonts/PressStart2P.ttf")) {
        std::cout << "PressStart2P font not loaded" << std::endl;
        return 1;
    }
    
    // Пиксельный стиль с PressStart2P
    sf::Text title(font, "ROAD TRIP", 16);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition({160, 60});
    
    sf::Text subtitle(font, "ROAD MOVIE RPG", 10);
    subtitle.setFillColor(sf::Color::Cyan);
    subtitle.setPosition({240, 90});
    
    sf::Text newGame(font, "> START NEW TRIP", 10);
    newGame.setFillColor(sf::Color::Green);
    newGame.setPosition({220, 150});
    
    sf::Text continueGame(font, "> CONTINUE TRIP", 10);
    continueGame.setFillColor(sf::Color::White);
    continueGame.setPosition({220, 180});
    
    sf::Text music(font, "> SOUNDTRACK", 10);
    music.setFillColor(sf::Color::White);
    music.setPosition({220, 210});
    
    sf::Text exit(font, "> EXIT GARAGE", 10);
    exit.setFillColor(sf::Color::Red);
    exit.setPosition({220, 240});
    
    sf::RectangleShape line(sf::Vector2f(400, 2));
    line.setFillColor(sf::Color(100, 100, 150));
    line.setPosition({120, 130});
    
    while (window.isOpen()) {
        if (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }
        
        window.clear(sf::Color(20, 20, 40));
        window.draw(title);
        window.draw(subtitle);
        window.draw(line);
        window.draw(newGame);
        window.draw(continueGame);
        window.draw(music);
        window.draw(exit);
        window.display();
    }
    
    return 0;
}
