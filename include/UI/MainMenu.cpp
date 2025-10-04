#include "UI/MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::Font& font)
    : font(font)
    , selector(font, ">>", 10)
    , title(font, "ROAD TRIP", 16)
    , subtitle(font, "ROAD MOVIE RPG", 10)
    , line(sf::Vector2f(400, 2))
{
    // Настройка заголовка
    title.setFillColor(sf::Color::Yellow);
    title.setPosition({160, 60});
    
    // Настройка подзаголовка
    subtitle.setFillColor(sf::Color::Cyan);
    subtitle.setPosition({240, 90});
    
    // Настройка разделительной линии
    line.setFillColor(sf::Color(100, 100, 150));
    line.setPosition({120, 130});
    
    // Настройка индикатора выбора
    selector.setFillColor(sf::Color::Yellow);
    
    setupMenuItems();
    updateSelector();
}

void MainMenu::setupMenuItems() {
    menuItems.clear();
    
    sf::Text newGame(font, "START NEW TRIP", 10);
    newGame.setFillColor(sf::Color::Green);
    newGame.setPosition({240, 150});
    menuItems.push_back(newGame);
    
    sf::Text continueGame(font, "CONTINUE TRIP", 10);
    continueGame.setFillColor(sf::Color::White);
    continueGame.setPosition({240, 180});
    menuItems.push_back(continueGame);
    
    sf::Text music(font, "SOUNDTRACK", 10);
    music.setFillColor(sf::Color::White);
    music.setPosition({240, 210});
    menuItems.push_back(music);
    
    sf::Text exit(font, "EXIT GARAGE", 10);
    exit.setFillColor(sf::Color::White);
    exit.setPosition({240, 240});
    menuItems.push_back(exit);
}

void MainMenu::updateSelector() {
    selector.setPosition({
        menuItems[selectedIndex].getPosition().x - 30,
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
    // Обновление цветов пунктов меню
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
