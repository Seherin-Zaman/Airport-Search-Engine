#include "DataManager.h"             // Include the header for data management features
#include "FileHandler.h"             // Include the header for file handling functions
#include <iostream>                  // Include iostream for console I/O operations
#include <fstream>                   // Include fstream for file I/Ooperations
#include <cctype>                    // Include cctype for character handling functions

using namespace std;

// Option 5: Add a new airport
void DataManager::addAirport(vector<Airport>& airports) {
    Airport newAirport;              // Create a new Airport struct to hold user input data

    cin.ignore(1000, '\n');

    
    cout << "===== Add New Airport =====\n";
    // Prompt user for each field of the Airport struct with input validation where necessary
    cout << "Enter airport ident: ";
    getline(cin, newAirport.ident);

    cout << "Enter airport type: ";
    getline(cin, newAirport.type);

    cout << "Enter airport name: ";
    getline(cin, newAirport.name);

    cout << "Enter elevation (ft): ";
    while (!(cin >> newAirport.elevation_ft)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a number for elevation: ";
    }
    cin.ignore(1000, '\n');

    cout << "Enter continent: ";
    getline(cin, newAirport.continent);

    cout << "Enter country code: ";
    getline(cin, newAirport.iso_country);

    cout << "Enter region code: ";
    getline(cin, newAirport.iso_region);

    cout << "Enter municipality: ";
    getline(cin, newAirport.municipality);

    cout << "Enter ICAO code: ";
    getline(cin, newAirport.icao_code);

    cout << "Enter IATA code: ";
    getline(cin, newAirport.iata_code);

    cout << "Enter GPS code: ";
    getline(cin, newAirport.gps_code);

    cout << "Enter local code: ";
    getline(cin, newAirport.local_code);

    cout << "Enter latitude: ";
    while (!(cin >> newAirport.latitude)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a valid latitude: ";
    }

    cout << "Enter longitude: ";
    while (!(cin >> newAirport.longitude)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a valid longitude: ";
    }

    airports.push_back(newAirport); // Add thw new airport to the vector of airports

    cout << "\nAirport added successfully.\n";
    cout << "New total number of airports: " << airports.size() << endl;
}

// Option 6: Save current airport data to CSV
void DataManager::saveChanges(const string& filename, const vector<Airport>& airports) {
    ofstream outFile(filename);      // Open the file for wiritng 
    // Check if file opened successfully
    if (!outFile.is_open()) {
        cerr << "Unable to open file for saving: " << filename << endl;
        return;
    }

    
    outFile << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao_code,iata_code,gps_code,local_code,latitude,longitude\n";

    // Write each airport's data to the file in CSV format
    for (const auto& airport : airports) {
        outFile << airport.ident << ','
                << airport.type << ','
                << airport.name << ','
                << airport.elevation_ft << ','
                << airport.continent << ','
                << airport.iso_country << ','
                << airport.iso_region << ','
                << airport.municipality << ','
                << airport.icao_code << ','
                << airport.iata_code << ','
                << airport.gps_code << ','
                << airport.local_code << ','
                << airport.latitude << ','
                << airport.longitude
                << '\n';
    }
}

// Option 6: Ask user before saving
bool DataManager::confirmAndSave(const string& filename, const vector<Airport>& airports) {
    char confirm;

    // Ask user to confirm saving changes with input validation
    while (true) {
        cout << "Do you want to save changes? (y/n): ";
        cin >> confirm;

        confirm = tolower(confirm);

        if (confirm == 'y') {
            saveChanges(filename, airports);
            cout << "\nChanges saved successfully.\n";
            return true;
        }
        else if (confirm == 'n') {
            cout << "\nSave cancelled.\n";
            return false;
        }
        else {
            cout << "Invalid input. Please enter y or n.\n";
        }
    }
}
