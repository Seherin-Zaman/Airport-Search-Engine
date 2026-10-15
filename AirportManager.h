#ifndef AIRPORTMANAGER_H
#define AIRPORTMANAGER_H

#include <vector>         // Include vector for using vector data structure
#include <string>         // Include string for using data type string
#include "Airport.h"      // Include the header for airport struct defination


// Manages overall application flow, user interface, and interactions
class AirportManager {
private:
    std::vector<Airport> airports;                 // Vector to hold loaded airport data

    void clearScreen();                            // Clear terminal screen
    void pauseScreen();                            // Pause screen until user input
    void showMenu();                               //Display main menu options
    void loadingEffect(const std::string& message);// Show animated loading effect with custom message

public:                                            // Starts program floe
    void start();                                  // Initiate the application and handle user interactions
};

#endif
