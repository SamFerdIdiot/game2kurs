
#include "States/VehicleSelection.h"
#include <iostream>


VehicleSelection::VehicleSelection(sf::Font& font) 
    : font(font)
    , selector(font, ">>", 24)
    , title(font, "SELECT YOUR JOURNEY", 48)
    , vehicleTitle(font, "CHOOSE VEHICLE:", 32)
    , destinationTitle(font, "CHOOSE DESTINATION:", 32)

{
    setupSelection();
    updateSelector();
}

void VehicleSelection::SetupSelection() {
    
    title.setFillColor(sf::Color::Yellow);
    title.setPosition({100, 100});
    
    vehicleTitle.setFillColor(sf::Color::Cyan);
    vehicleTitle.setPosition({100, 200});
    
    vehicleOptions.clear();
    
    sf::Text sedan(font, "SEDAN 4 seats, not very large trunk, poor reliability ", 28);
    sedan.setFillColor(sf::Color::Green);
    sedan.setPosition({150, 280});
    vehicleOptions.push_back(sedan);
    
    sf::Text jeep(font, "renault espace: a minivan with the rear seats removed, for use in delivery", 28);
    jeep.setFillColor(sf::Color::White);
    jeep.setPosition({150, 350});
    vehicleOptions.push_back(jeep);
    
    sf::Text sports(font, "BMW 328i COUPE - King of the road, 3 doors small trunk, big engine", 28);
    sports.setFillColor(sf::Color::White)
    sports.setPosition({150, 420});
    vehicleOptions.push_back(sports);
    
    destinationTitle.setFillColor(sf::Color::Cyan);
        destinationTitle.setPosition({100, 520});
        
        destinationOptions.clear();
        
        sf::Text coast(font, "transportation of father's important cargo to Moscow", 28);
    //не стоило бросать университет в москве. Безделие надоело твоему отцу, он решил, что ты будешь работать на него доставщиком, не позволит он своему ребенку быть бездельником и сидеть на его шее. Также в твоем инвентаре имеется личное пись ректору от товего отца. в письме: "просьба востановить тебя в университе" опциональная возможность если ты передумаешь тратить свою жизнь на развлечения.
        coast.setFillColor(sf::Color::White);
        coast.setPosition({150, 600});
        destinationOptions.push_back(coast);
    
        sf::Text mountains(font, "The call of adventure, your friends from the university, invite you to the festival in Moscow", 28);
    //твои друзья слышали про то что ты получил права и все лето хотел провести дома, в этом году на летний фестиваль приезжает крутая американская группа. ты обязан туда попасть
        mountains.setFillColor(sf::Color::White);
        mountains.setPosition({150, 670});
        destinationOptions.push_back(mountains);
       
        sf::Text desert(font, "Business Carrier. Working at the port, you were able to get luxury items and you are heading to resell them as dearly as possible.", 28);
    //Ты молод, в школе тебя учили быть правильным, родители не очень богатые, но честные люди. у них не получилось отправить тебя на учебу, и ты уехал на заработки в рейсы на корабле. В один из дней твои товарищи смогли расстащить контейнер одного недобросовестного заказчика, так ты и получил пару коробок с невероятно хорошими костюмами и пиджаками. теперь ты не матрос а спекулянт перепродажник, Цель заработать как можно больше до того момента пока не доедешь до Москвы
        desert.setFillColor(sf::Color::White);
        desert.setPosition({150, 740});
        destinationOptions.push_back(desert);
       
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
        
        if (keyEvent->code == sf::Keyboard::Key::Down) {
            if (selectingVehicle) {
                selectedVehicle = (selectedVehicle + 1) % vehicleOptions.size();
            } else {
                selectedDestination = (selectedDestination + 1) % destinationOptions.size();
            }
        }
        else if (keyEvent->code == sf::Keyboard::Key::Up) {
            if (selectingVehicle) {
                selectedVehicle = (selectedVehicle - 1 + vehicleOptions.size()) % vehicleOptions.size();
            } else {
                selectedDestination = (selectedDestination - 1 + destinationOptions.size()) % destinationOptions.size();
            }
            else if (keyEvent->code == sf::Keyboard::Key::Enter) {
                if (selectingVehicle) {
                    selectingVehicle = false; // Переходим к выбору цели
                } else {
                    selectionComplete = true; // Завершаем выбор
                }
            }
            else if (keyEvent->code == sf::Keyboard::Key::Escape) {
                if (!selectingVehicle) {
                    selectingVehicle = true; // Возвращаемся к выбору машины
                }
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
        hint.setPosition({100, 900});
        window.draw(hint);
    }
