#ifndef VEHICLESELECTION_H
#define VEHICLESELECTION_H

#include <SFML/Graphics.hpp>
#include <vector>

class VehicleSelection {
    
public:
    
    VehicleSelection(sf::Font& font);
    void handleInput(sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);
    
    bool isSelectionComplete() const { return selectionComplete; }
    int getSelectedVehicle() const { return selectedVehicle; }
    int getSelectedDestination() const { return selectedDestination; }
    
private:
    sf::Font& font;
    std::vector<sf::Text> vehicleOptions;
    std::vector<sf::Text> destinationOptions;
    sf::Text title;
    sf::Text vehicleTitle;
    sf::Text destinationTitle;
    sf::Text selector;
    
    int selectedVehicle = 0;
    int selectedDestination = 0;
    bool selectingVehicle = true;
    bool selectionComplete = false;
    
    void setupSelection();
    void updateSelector();
}
