#ifndef FILEHANDLER_H   
#define FILEHANDLER_H   

#include <vector>            // Include vector for using vector data structure
#include <string>            // Include string for using data type string
#include "Airport.h"         // Include the header for airport struct defination
using namespace std;


// Handles file operation like loading and saving airport data
class FileHandler {          
public:
    static vector<string> splitCSV(const string& line);                                 // Helper function to split csv line into fields
    static void loadAirports(const string& filename, vector<Airport>& airports);        // Loads airport data from a csv file into a vector of Airport structs
    static void saveAirports(const string& filename, const vector<Airport>& airports);  // Saves airport data from a vector of Airport structs into a csv file
};

#endif
