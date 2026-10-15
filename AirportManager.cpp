#include "AirportManager.h"    // Include the header for AirportManager
#include "Colors.h"            // Include the header for color definitions
#include "GeoCalculator.h"     // Include the header for geographic calculations
#include "FileHandler.h"       // Include the header for file handling fucntions
#include "SearchManager.h"     // Include the header for search-related features
#include "AnalysisManager.h"   // Include the header for analysis-related features
#include "DataManager.h"       // Include the header for data management features
#include "AnalysisManager.h"   // Include the header for analysis-related features     
#include <cstdlib>             // Include cstdlib for system calls
#include <thread>              // Include thread for sleep functionality
#include <chrono>              // Include chrono for time durations
#include <iostream>            // Include iostream for console I/O operations

using namespace std;

// Clears terminal screen depending on operating system
void AirportManager::clearScreen() {
#ifdef _WIN32
    system("cls");     // Windows
#else
    system("clear");   // Mac/Linux
#endif
}

// Shows animated loading screen properly
void AirportManager::loadingEffect(const string& message) {
    this_thread::sleep_for(chrono::milliseconds(500));
    for (int i = 1; i <= 3; i++) {
        clearScreen();

        cout  <<message;
        for (int j = 0; j < i; j++) {
            cout << ".";
        }
        cout << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    clearScreen();
}

// Pauses the screen until user presses Enter
void AirportManager::pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

// Displays main menu
void AirportManager::showMenu() {
    loadingEffect("Loading menu");
    cout << BOLD << CYAN;
    cout << "=========================================\n";
    cout << "      Nottingham SkyRoute Explorer\n";
    cout << "=========================================\n";
    cout <<RESET;

    cout << YELLOW<<"\n--- Search ---\n"<<RESET;
    cout << GREEN<<"1. Search by country\n";
    cout << "2. Search by name\n";
    cout << "3. Search by IATA\n"<<RESET;

    cout << YELLOW<<"\n--- Core ---\n";
    cout <<  GREEN<<"4. Count airports by type\n";
    cout << "5. Add airport\n";
    cout << "6. Save changes\n"<<RESET;

    cout << YELLOW<<"\n--- Geographic ---\n"<<RESET;
    cout <<  GREEN<< "7. Distance between airports\n";
    cout << "8. Nearest airport\n";
    cout << "9. Airports within radius\n"<<RESET;

    cout <<YELLOW<< "\n--- Analysis ---\n"<<RESET;
    cout <<  GREEN<<"10. Highest & lowest elevation\n";
    cout << "11. Missing IATA\n";
    cout << "12. Group by municipality\n"<<RESET;

    cout << RED << "\n--- System ---\n";
    cout << "13. Exit\n"<< RESET;

    
}

// Starts program flow
void AirportManager::start() {
    // Show loading animation first
    loadingEffect("Loading airport data");

    // Load airport data
    FileHandler::loadAirports("airports.csv", airports);

    // Keep loaded message visible
    pauseScreen();

    int choice;

    do {
        this_thread::sleep_for(chrono::milliseconds(500));
        clearScreen();
        showMenu();
        

        
    // Get user choice with validation
    while (true) {
       cout << "\nEnter choice: ";
       cin >> choice;
       
        // Validation input
        if (!cin.fail() && choice >= 1 && choice <= 13) {
            this_thread::sleep_for(chrono::milliseconds(500));
            loadingEffect("Processing");
           break; // valid input → exit loop
        }

        // Invalid input
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "❌ Invalid input. Please enter a number between 1 and 13.\n";
        loadingEffect("Redirecting");
}

        clearScreen();
        
        // Handle user choice
        switch (choice) {
            case 1:
                SearchManager::searchByCountry(airports);
                pauseScreen();
                loadingEffect("Rediecting");
                break;

            case 2:
                SearchManager::searchByName(airports);
                pauseScreen();
                loadingEffect("Redirecting");
                break;

            case 3:
                SearchManager::searchByIATA(airports);
                pauseScreen();
                loadingEffect("Redirecting");
                break;

            case 4:
                AnalysisManager::countByType(airports);
                pauseScreen();
                pauseScreen();
                break;

            case 5:
                DataManager::addAirport(airports);
                pauseScreen();
                break;

            case 6:
                DataManager::confirmAndSave("airports.csv", airports);
                pauseScreen();
                break;

            case 7:
                GeoCalculator::distanceBetweenAirports(airports);
                pauseScreen();
                break;

            case 8:
                GeoCalculator::findNearestAirport(airports);
                pauseScreen();
                break;

            case 9:
                GeoCalculator::airportsWithinRadius(airports);
                pauseScreen();
                break;

            case 10:
                AnalysisManager::showElevationAnalysis(airports);
                pauseScreen();
                break;

            case 11:
                AnalysisManager::showMissingIATA(airports);
                pauseScreen();
                break;

            case 12:
                AnalysisManager::groupByMunicipality(airports);
                pauseScreen();
                break;
            
            case 13:
                loadingEffect("Exiting");
                break;

            default:
                cout << "Invalid choice\n";
                pauseScreen();
        }

    } while (choice != 13);
}
