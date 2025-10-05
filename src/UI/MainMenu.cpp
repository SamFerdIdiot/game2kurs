#include "UI/MainMenu.h"
#include <iostream>

constexpr unsigned int MainMenu::WINDOW_WIDTH;
constexpr unsigned int MainMenu::WINDOW_HEIGHT;

MainMenu::MainMenu(sf::Font& font)
    : font(font)
    , selector(font, ">>", 14)
    , title(font, "ROAD TRIP ROSTOV => MOSCOW", 18)
    , subtitle(font, "ROAD MOVIE RPG", 14)
    , line(sf::Vector2f(800, 3))
{
    // Все позиции смещены влево
    title.setFillColor(sf::Color::Yellow);
    title.setPosition({100, 150});  // Максимально влево
    
    subtitle.setFillColor(sf::Color::Cyan);
    subtitle.setPosition({100, 200});
    
    line.setFillColor(sf::Color(100, 100, 150));
    line.setPosition({100, 230});
    
    selector.setFillColor(sf::Color::Yellow);
    
    setupMenuItems();
    updateSelector();
}

void MainMenu::setupMenuItems() {
    menuItems.clear();
    
    // Все пункты меню смещены влево
    sf::Text newGame(font, "START NEW TRIP", 22);
    newGame.setFillColor(sf::Color::Green);
    newGame.setPosition({150, 280});
    menuItems.push_back(newGame);
    
    sf::Text continueGame(font, "CONTINUE TRIP", 22);
    continueGame.setFillColor(sf::Color::White);
    continueGame.setPosition({150, 310});
    menuItems.push_back(continueGame);
    
    sf::Text music(font, "SOUNDTRACK", 22);
    music.setFillColor(sf::Color::White);
    music.setPosition({150, 340});
    menuItems.push_back(music);
    
    sf::Text exit(font, "EXIT GARAGE", 22);
    exit.setFillColor(sf::Color::White);
    exit.setPosition({150, 380});
    menuItems.push_back(exit);
}

void MainMenu::updateSelector() {
    selector.setPosition({
        menuItems[selectedIndex].getPosition().x - 60,
        menuItems[selectedIndex].getPosition().y
    });
}

void MainMenu::handleInput(sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto keyEvent = event.getIf<sf::Event::KeyPressed>();
        
        if (keyEvent->code == sf::Keyboard::Key::Down) {
            selectedIndex = (selectedIndex + 1) % menuItems.size();
        }
        else if (keyEvent->code == sf::Keyboard::Key::Up) {
            selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
        }
        else if (keyEvent->code == sf::Keyboard::Key::Enter) {
            optionSelected = true;
        }
    }
}

void MainMenu::update() {
    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedIndex) {
            menuItems[i].setFillColor(sf::Color::Yellow);
        } else if (i == 0) {
            menuItems[i].setFillColor(sf::Color::Green);
        } else if (i == 3) {
            menuItems[i].setFillColor(sf::Color::Red);
        } else {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }
    updateSelector();
}

void MainMenu::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(subtitle);
    window.draw(line);
    window.draw(selector);
    
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}
