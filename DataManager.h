#ifndef DATAMANAGER_H         // Include guard to prevent multiple inclusions of this header file
#define DATAMANAGER_H         // Include guard to prevent multiple inclusions of this header file

#include <vector>             // Include vector for using vector data structure 
#include <string>             // Include string for using data type string
#include "Airport.h"          // Include the header for airport struct defination
using namespace std;

// Handles data management features like adding new airports and saving changes to file
class DataManager {
public:
    static void addAirport(vector<Airport>& airports);                                 // Add a new airport to the vector from user input with validation
    static void saveChanges(const string& filename, const vector<Airport>& airports);  // Save current airport data to a CSV file
    static bool confirmAndSave(const string& filename, const vector<Airport>& airports);// Ask user to confirm saving changes with input validation and save if confrimed 
};

#endif
