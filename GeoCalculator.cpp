#include "GeoCalculator.h"          // Include the header for geographic calcuations 
#include "SearchManager.h"          // Include the header for search-related features
#include "Colors.h"                 // Include the header for color definations
#include <iostream>                 // Include iostream for console I/O operations
#include <cmath>                    // Include cmath for mathematical functions
#include <algorithm>                // Include algorithm for transforming strings
#include <limits>                   // Include limits for numeric limits 

using namespace std;

// Constants for Earth's radius and pi used in Haversine formula
const double EARTH_RADIUS_KM = 6371.0;
const double PI = 3.14159265358979323846;

// Common function: clear input buffer safely
static void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Common function: get valid choice between 1 and 2
static int getChoiceOneOrTwo(const string& option1, const string& option2) {
    int choice;

    while (true) {
        cout << option1 << "\n";
        cout << option2 << "\n";
        cout << "Choose option: ";
        cin >> choice;

        if (!cin.fail() && (choice == 1 || choice == 2)) {
            clearInputBuffer();
            return choice;
        }

        clearInputBuffer();
        cout << "Invalid input. Please enter 1 or 2.\n";
    }
}

// Common function: get valid double input
static double getValidatedDoubleInput(const string& prompt, const string& errorMessage) {
    double value;

    while (true) {
        cout << prompt;
        cin >> value;

        if (!cin.fail()) {
            clearInputBuffer();
            return value;
        }

        clearInputBuffer();
        cout << errorMessage;
    }
}

// Common function: get valid non-negative double input
static double getValidatedNonNegativeDoubleInput(const string& prompt, const string& errorMessage) {
    double value;

    while (true) {
        cout << prompt;
        cin >> value;

        if (!cin.fail() && value >= 0) {
            clearInputBuffer();
            return value;
        }

        clearInputBuffer();
        cout << errorMessage;
    }
}

// Common function: convert string to uppercase
static string toUpperCase(string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}

// Common function: convert string to lowercase
static string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

// Common function: find airport by IATA code
static const Airport* findAirportByIATA(const vector<Airport>& airports, const string& inputCode) {
    string targetCode = toUpperCase(inputCode);

    for (const Airport& airport : airports) {
        if (airport.iata_code.empty()) continue;

        string code = toUpperCase(airport.iata_code);

        if (code == targetCode) {
            return &airport;
        }
    }

    return nullptr;
}

// Common function: find airport by exact name (case-insensitive)
static const Airport* findAirportByName(const vector<Airport>& airports, const string& inputName) {
    string targetName = toLowerCase(inputName);

    for (const Airport& airport : airports) {
        string airportName = toLowerCase(airport.name);

        if (airportName == targetName) {
            return &airport;
        }
    }

    return nullptr;
}

// Common function: display airports with distance in groups of 20
static bool displayAirportsWithDistanceInPages(const vector<pair<const Airport*, double>>& airportList) {
    int shownCount = 0;

    for (const auto& entry : airportList) {
        SearchManager::displayAirport(*entry.first);
        cout << "Distance: " << entry.second << " km\n\n";
        shownCount++;

        if (shownCount % 20 == 0 && shownCount < static_cast<int>(airportList.size())) {
            int action = getChoiceOneOrTwo("1. Show next 20", "2. Go back to menu");
            if (action == 2) {
                return false;
            }
        }
    }

    return true;
}

// Calculates distance between two coordinates using Haversine formula
double GeoCalculator::haversine(double lat1, double lon1, double lat2, double lon2) {
    lat1 = lat1 * PI / 180.0;
    lon1 = lon1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;
    lon2 = lon2 * PI / 180.0;

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    // Haversine formula to calculate distance between two points on the Earth's surface
    double a = pow(sin(dLat / 2), 2) +
               cos(lat1) * cos(lat2) * pow(sin(dLon / 2), 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}

// Option 7: Calculate distance between two airports
void GeoCalculator::distanceBetweenAirports(const vector<Airport>& airports) {
    int mode;

    cout << "===== Distance Between Airports =====\n";
    mode = getChoiceOneOrTwo("1. Use IATA codes", "2. Use airport names");

    const Airport* airport1 = nullptr;
    const Airport* airport2 = nullptr;

    // Option 1: use IATA codes
    if (mode == 1) {
        string code1, code2;

        cout << "Enter first airport IATA code: ";
        getline(cin, code1);

        cout << "Enter second airport IATA code: ";
        getline(cin, code2);

        airport1 = findAirportByIATA(airports, code1);
        airport2 = findAirportByIATA(airports, code2);

        // Check if both airports were found
        if (!airport1 || !airport2) {
            cout << "One or both IATA codes were not found.\n";
            return;
        }
    }

    // Option 2: use airport names
    else {
        string name1, name2;

        cout << "Enter first airport name: ";
        getline(cin, name1);

        cout << "Enter second airport name: ";
        getline(cin, name2);

        airport1 = findAirportByName(airports, name1);
        airport2 = findAirportByName(airports, name2);

        // Check if both airports were found
        if (!airport1 || !airport2) {
            cout << "One or both airport names were not found.\n";
            return;
        }
    }

    // Calculate distance using Haversine formula
    double distance = haversine(
        airport1->latitude, airport1->longitude,
        airport2->latitude, airport2->longitude
    );

    // Display results
    cout << "\nFirst airport:\n";
    SearchManager::displayAirport(*airport1);

    cout << "\nSecond airport:\n";
    SearchManager::displayAirport(*airport2);

    cout << "\nDistance between airports: " << distance << " km\n";
}

// Option 8: Find nearest airport to given coordinates
void GeoCalculator::findNearestAirport(const vector<Airport>& airports) {
    double userLat, userLon;
    double minDistance = numeric_limits<double>::max();
    const Airport* nearestAirport = nullptr;

    cout << "===== Find Nearest Airport =====\n";

    userLat = getValidatedDoubleInput("Enter latitude: ", "Invalid input. Enter a valid latitude: ");
    userLon = getValidatedDoubleInput("Enter longitude: ", "Invalid input. Enter a valid longitude: ");

    // Iterate through all airports to find the nearest one based on Haversine distance
    for (const Airport& airport : airports) {
        double distance = haversine(userLat, userLon, airport.latitude, airport.longitude);

        // Update nearest airport if a closer one is found
        if (distance < minDistance) {
            minDistance = distance;
            nearestAirport = &airport;
        }
    }

    // Check if any airport data is available
    if (nearestAirport == nullptr) {
        cout << "No airport data available.\n";
        return;
    }

    cout << "\nNearest airport:\n";
    SearchManager::displayAirport(*nearestAirport);
    cout << "Distance: " << minDistance << " km\n";
}

// Option 9: List airports within a certain radius of given coordinates
void GeoCalculator::airportsWithinRadius(const vector<Airport>& airports) {
    double userLat, userLon, radius;

    cout << "===== Airports Within Radius =====\n";

    userLat = getValidatedDoubleInput("Enter latitude: ", "Invalid input. Enter a valid latitude: ");
    userLon = getValidatedDoubleInput("Enter longitude: ", "Invalid input. Enter a valid longitude: ");
    radius = getValidatedNonNegativeDoubleInput("Enter radius in km: ", "Invalid input. Enter a valid radius: ");

    vector<pair<const Airport*, double>> airportsInRange;

    cout << "\nAirports within " << radius << " km:\n";

    // Iterate through all airports to find those within the specified radius
    for (const Airport& airport : airports) {
        double distance = haversine(userLat, userLon, airport.latitude, airport.longitude);

        if (distance <= radius) {
            airportsInRange.push_back({&airport, distance});
        }
    }

    // Display total count of airports found within the radius
    if (airportsInRange.empty()) {
        cout << "No airports found within the specified radius.\n";
        return;
    }

    if (!displayAirportsWithDistanceInPages(airportsInRange)) {
        return;
    }

    cout << "Total airports found: " << airportsInRange.size() << endl;
}
