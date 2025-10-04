#include "TextHelper.h"

sf::Text TextHelper::createText(sf::Font& font, const std::string& text, unsigned int size,
                               sf::Vector2f position, sf::Color color) {
    sf::Text textObj(font, text, size);
    textObj.setFillColor(color);
    textObj.setPosition(position);
    return textObj;
}
