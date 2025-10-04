#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
    std::cout << "SFML 3.0.2 Apple Silicon Test - Running!" << std::endl;
    
    // Создаем окно - используем Vector2u для размера
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML 3.0.2 Test");
    
    // Создаем фигуры
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(sf::Vector2f(350, 250)); // Используем Vector2f для позиции
    
    sf::RectangleShape rectangle(sf::Vector2f(120.f, 60.f));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(sf::Vector2f(340, 150));
    
    // Основной цикл
    while (window.isOpen()) {
        // Обработка событий через std::optional
        while (std::optional event = window.pollEvent()) {
            // Проверяем тип события через is()
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // Закрытие по клавише Escape
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }
        
        // Отрисовка
        window.clear(sf::Color::Black);
        window.draw(rectangle);
        window.draw(circle);
        window.display();
    }
    
    std::cout << "Application finished successfully!" << std::endl;
    return 0;
}
