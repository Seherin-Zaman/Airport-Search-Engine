#ifndef SEARCHMANAGER_H         // Include guard to prevent multiple inclusions of this header file
#define SEARCHMANAGER_H         // Include guard to prevent multiple inclusions of this header file

#include <vector>               // Include vector for using vector data structure
#include <string>              // Include string for using data type string
#include  "Airport.h"          // Include the header for airport struct defination
using namespace std;

// Handles search-related features like searching airports by country, name, or IATA code
class SearchManager {
    public:
    static void displayAirport(const Airport& airport);           // Helper function to display full details of one airport
    static void searchByCountry(const vector<Airport>& airports); // Search airports by country with options to select from available countries or enter country code manually, and display results with validation
    static void searchByName(const vector<Airport>& airports);    // Search airports by name with options to enter full/partial name or first letter to see available names, and display results with validation
    static void searchByIATA(const vector<Airport>& airports);    // Search airports by IATA code with options to select from available IATA codes or enter code manually, and display results with validation

};

#endif
