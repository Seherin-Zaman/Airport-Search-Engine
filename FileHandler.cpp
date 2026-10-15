#include "FileHandler.h"       // Include the header for file handling fucntions
#include <fstream>             // Include fstream for file I/0 operations
#include <iostream>            // Include iostream for console I/O operations



// Function to split a CSV line into fields
vector<string> FileHandler::splitCSV(const string& line) {
    vector<string> result;
    string value = "";
    bool inQuotes = false;

    // Loop through each character in the line
    for (char c : line) {

        // Toggle quote mode if quote is found
        if (c == '"') {
            inQuotes = !inQuotes;
        }

        // If comma is found outside quotes, split field
        else if (c == ',' && !inQuotes) {
            result.push_back(value);
            value = "";
        }

        // Otherwise, keep building the current value
        else {
            value += c;
        }
    }

    // Add the last value after loop ends
    result.push_back(value);

    return result;
}


// Function to load airport data from CSV file
void FileHandler::loadAirports(const string& filename, vector<Airport>& airports) {

    // Open file
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    string line;

    // Skip header row
    getline(file, line);

    // Read file line by line
    while (getline(file, line)) {

        // Split CSV row into fields
        vector<string> data = splitCSV(line);

        // Skip invalid or incomplete rows
        if (data.size() < 13) continue;

        Airport a;

        // Assign values from CSV columns
        a.ident = data[0];
        a.type = data[1];
        a.name = data[2];

        // Convert elevation safely
        try {
            a.elevation_ft = data[3].empty() ? 0 : stoi(data[3]);
        } catch (...) {
            a.elevation_ft = 0;
        }

        // Assign remaianing fields
        a.continent = data[4];
        a.iso_country = data[5];
        a.iso_region = data[6];
        a.municipality = data[7];
        a.icao_code = data[8];
        a.iata_code = data[9];
        a.gps_code = data[10];
        a.local_code = data[11];

        // Extract latitude and longitude from coordinates field
        try {
            string coords = data[12];
            size_t commaPos = coords.find(',');

            // Handle case where coordinates are present            
            if (commaPos != string::npos) {
                a.latitude = stod(coords.substr(0, commaPos));
                a.longitude = stod(coords.substr(commaPos + 1));
            } else {
                a.latitude = 0;
                a.longitude = 0;
            }
        } catch (...) {
            a.latitude = 0;
            a.longitude = 0;
        }

        // Add airport to vector
        airports.push_back(a);
    }

    file.close();

    // Display number of loaded airports
    cout << "Airports loaded successfully: " << airports.size() << endl;
}

// Saves airport data back to CSV
void FileHandler::saveAirports(const string& filename, const vector<Airport>& airports) {
    ofstream file(filename);

    // Check if file opened successfully
    if (!file.is_open()) {
        cout << "Error: Unable to save file.\n";
        return;
    }

    // Header row
    file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao_code,iata_code,gps_code,local_code,coordinates\n";

    // Data rows
    for (const Airport& airport : airports) {
        file << airport.ident << ","
             << airport.type << ","
             << airport.name << ","
             << airport.elevation_ft << ","
             << airport.continent << ","
             << airport.iso_country << ","
             << airport.iso_region << ","
             << airport.municipality << ","
             << airport.icao_code << ","
             << airport.iata_code << ","
             << airport.gps_code << ","
             << airport.local_code << ","
             << "\"" << airport.latitude << ", " << airport.longitude << "\"\n";
    }

    file.close();
}
