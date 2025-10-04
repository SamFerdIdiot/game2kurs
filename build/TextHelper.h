#ifndef TEXTHELPER_H
#define TEXTHELPER_H

#include <SFML/Graphics.hpp>
#include <string>

class TextHelper {
public:
    static sf::Text createText(sf::Font& font, const std::string& text, unsigned int size, 
                              sf::Vector2f position, sf::Color color = sf::Color::White);
};

#endif
