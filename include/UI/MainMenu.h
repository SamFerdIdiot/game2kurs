#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu {
public:
    MainMenu(sf::Font& font);
    void handleInput(sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);
    
    int getSelectedIndex() const { return selectedIndex; }
    bool isOptionSelected() const { return optionSelected; }
    int getSelectedOption() const { return selectedIndex; }
    void resetSelection() { optionSelected = false; }
    
private:
    void updateSelector();
    void setupMenuItems();
    
    static constexpr unsigned int WINDOW_WIDTH = 2560;
    static constexpr unsigned int WINDOW_HEIGHT = 1600;
    
    sf::Font& font;
    std::vector<sf::Text> menuItems;
    sf::Text selector;
    sf::Text title;
    sf::Text subtitle;
    sf::RectangleShape line;
    
    int selectedIndex = 0;
    bool optionSelected = false;
};

#endif
