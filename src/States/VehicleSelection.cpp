#include "States/VehicleSelection.h"
#include <iostream>


VehicleSelection::VehicleSelection(sf::Font& font)
    : font(font)
    , selector(font, ">>", 10)
    , title(font, "SELECT YOUR JOURNEY", 18)
    , vehicleTitle(font, "CHOOSE VEHICLE:", 18)
    , destinationTitle(font, "CHOOSE DESTINATION:", 18)

{
    setupSelection();
    updateSelector();
}

void VehicleSelection::setupSelection() {

    title.setFillColor(sf::Color::Yellow);
    title.setPosition({50, 50});

    vehicleTitle.setFillColor(sf::Color::Cyan);
    vehicleTitle.setPosition({50, 100});

    vehicleOptions.clear();

    sf::Text sedan(font, "7 - 4 seats, not very large trunk, poor reliability ", 14);
    sedan.setFillColor(sf::Color::Green);
    sedan.setPosition({100, 130});
    vehicleOptions.push_back(sedan);

    sf::Text minivan(font, "renault espace - a minivan with the rear seats removed, for use in delivery", 14);
    minivan.setFillColor(sf::Color::White);
    minivan.setPosition({100, 155});
    vehicleOptions.push_back(minivan);

    sf::Text sports(font, "BMW 328i COUPE - King of the road, 3 doors small trunk, big engine", 14);
    sports.setFillColor(sf::Color::White);
    sports.setPosition({100, 185});
    vehicleOptions.push_back(sports);

    destinationTitle.setFillColor(sf::Color::Cyan);
        destinationTitle.setPosition({50, 230});

        destinationOptions.clear();

        sf::Text easy(font, "transportation of father's important cargo to Moscow", 12);
    //не стоило бросать университет в москве. Безделие надоело твоему отцу, он решил, что ты будешь работать на него доставщиком, не позволит он своему ребенку быть бездельником     и сидеть на его шее. Также в твоем инвентаре имеется личное пись ректору от товего отца. в письме: "просьба востановить тебя в университе" опциональная возможность если ты пере    думаешь тратить свою жизнь на развлечения.
        easy.setFillColor(sf::Color::White);
        easy.setPosition({100, 260});
        destinationOptions.push_back(easy);

        sf::Text normal(font, "The call of adventure, your friends from the university, invite you to the festival in Moscow", 12);
    //твои друзья слышали про то что ты получил права и все лето хотел провести дома, в этом году на летний фестиваль приезжает крутая американская группа. ты обязан туда попаст    ь
        normal.setFillColor(sf::Color::White);
        normal.setPosition({100, 290});
        destinationOptions.push_back(normal);

        sf::Text hard(font, "Business Carrier. Working at the port, you were able to get luxury  items and you are heading \nto resell them as dearly as possible.", 12);
    //Ты молод, в школе тебя учили быть правильным, родители не очень богатые, но честные люди. у них не получилось отправить тебя на учебу, и ты уехал на заработки в рейсы на к    орабле. В один из дней твои товарищи смогли расстащить контейнер одного недобросовестного заказчика, так ты и получил пару коробок с невероятно хорошими костюмами и пиджаками. т    еперь ты не матрос а спекулянт перепродажник, Цель заработать как можно больше до того момента пока не доедешь до Москвы
        hard.setFillColor(sf::Color::White);
        hard.setPosition({100, 320});
        destinationOptions.push_back(hard);

       selector.setFillColor(sf::Color::Yellow);
   }
    void VehicleSelection::updateSelector() {
        if (selectingVehicle) {
            selector.setPosition({
                vehicleOptions[selectedVehicle].getPosition().x - 60,
                vehicleOptions[selectedVehicle].getPosition().y
            });
        } else {
            selector.setPosition({
                destinationOptions[selectedDestination].getPosition().x - 60,
                destinationOptions[selectedDestination].getPosition().y
            });
        }
 }
void VehicleSelection::handleInput(sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto keyEvent = event.getIf<sf::Event::KeyPressed>();
        
        switch (keyEvent->scancode) {
            case sf::Keyboard::Scancode::Down:
                if (selectingVehicle) {
                    selectedVehicle = (selectedVehicle + 1) % vehicleOptions.size();
                } else {
                    selectedDestination = (selectedDestination + 1) % destinationOptions.size();
                }
                break;

            case sf::Keyboard::Scancode::Up:
                if (selectingVehicle) {
                    selectedVehicle = (selectedVehicle - 1 + vehicleOptions.size()) % vehicleOptions.size();
                } else {
                    selectedDestination = (selectedDestination - 1 + destinationOptions.size()) % destinationOptions.size();
                }
                break;

            case sf::Keyboard::Scancode::Enter:
                if (selectingVehicle) {
                    selectingVehicle = false; // Переходим к выбору цели
                } else {
                    selectionComplete = true; // Завершаем выбор
                }
                break;

            case sf::Keyboard::Scancode::Escape:
                if (!selectingVehicle) {
                    selectingVehicle = true; // Возвращаемся к выбору машины
                }
                break;

            default:
                break;
        }
        updateSelector();
    }
}


    void VehicleSelection::update() {
        for (int i = 0; i < vehicleOptions.size(); ++i) {
            vehicleOptions[i].setFillColor(i == selectedVehicle ? sf::Color::Yellow : sf::Color::White);
        }

        for (int i = 0; i < destinationOptions.size(); ++i) {
            destinationOptions[i].setFillColor(i == selectedDestination ? sf::Color::Yellow : sf::Color::White);
        }

        vehicleTitle.setFillColor(selectingVehicle ? sf::Color::Green : sf::Color::Cyan);
        destinationTitle.setFillColor(!selectingVehicle ? sf::Color::Green : sf::Color::Cyan);
    }

    void VehicleSelection::render(sf::RenderWindow& window) {
        window.draw(title);
        window.draw(vehicleTitle);
        window.draw(destinationTitle);
        window.draw(selector);

        for (const auto& vehicle : vehicleOptions) {
            window.draw(vehicle);
        }

        for (const auto& destination : destinationOptions) {
            window.draw(destination);
        }

        sf::Text hint(font, selectingVehicle ? "Press ENTER to select vehicle" : "Press ENTER to confirm destination, ESC to go back", 20);
        hint.setFillColor(sf::Color(150, 150, 150));
        hint.setPosition({100, 600});
        window.draw(hint);
    }
