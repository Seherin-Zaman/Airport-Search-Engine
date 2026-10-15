#include "AnalysisManager.h"        // Include the header for analysis-related features
#include "SearchManager.h"          // Include the header for search-related features
#include "Colors.h"                 // Include the header for color definations
#include <iostream>                 // Include iostream for console I/O operations
#include <set>                      // Include set for storing unique values
#include <vector>                   // Include vector for using vector data structure
#include <map>                      // Include map for key-value pair data structure
#include <algorithm>                // Include algorithm for sorting and transforming data
#include <cctype>                   // Include cctype for character handling functions
#include <limits>                   // Include limits for numeric_limits

using namespace std;

// Common function: clear input buffer safely
static void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Common function: get valid choice between 1 and 2
static int getChoiceOneOrTwo(const string& option1, const string& option2) {
    int choice;

    while (true) {
        cout << YELLOW << option1 << "\n";
        cout << option2 << RESET << "\n";
        cout << BLUE << "Choose option: " << RESET;
        cin >> choice;

        if (!cin.fail() && (choice == 1 || choice == 2)) {
            clearInputBuffer();
            return choice;
        }

        clearInputBuffer();
        cout << RED << "Please enter 1 or 2.\n" << RESET;
    }
}

// Common function: get valid choice between 1 and 3
static int getChoiceOneToThree(const string& option1, const string& option2, const string& option3) {
    int choice;

    while (true) {
        cout << YELLOW << option1 << "\n";
        cout << option2 << "\n";
        cout << option3 << RESET << "\n";
        cout << BLUE << "Choose option: " << RESET;
        cin >> choice;

        if (!cin.fail() && choice >= 1 && choice <= 3) {
            clearInputBuffer();
            return choice;
        }

        clearInputBuffer();
        cout << RED << "Please enter 1, 2 or 3.\n" << RESET;
    }
}

// Helper function for invalid input handling
static int handleInvalidInput() {
    cout << RED << "\nInvalid input.\n" << RESET;
    return getChoiceOneOrTwo("1. Try again", "2. Go back to menu");
}

// Common function: get validated menu choice within a range
static int getValidatedChoiceInRange(int minValue, int maxValue) {
    int choice;

    while (true) {
        cin >> choice;

        if (!cin.fail() && choice >= minValue && choice <= maxValue) {
            clearInputBuffer();
            return choice;
        }

        clearInputBuffer();

        int action = handleInvalidInput();
        if (action == 2) {
            return -1;
        }
    }
}

// Common function: get validated positive integer
static int getValidatedPositiveInteger() {
    int value;

    while (true) {
        cin >> value;

        if (!cin.fail() && value >= 1) {
            clearInputBuffer();
            return value;
        }

        clearInputBuffer();

        int action = handleInvalidInput();
        if (action == 2) {
            return -1;
        }
    }
}

// Common function: collect unique countries
static vector<string> getUniqueCountries(const vector<Airport>& airports) {
    set<string> uniqueCountries;

    for (const Airport& airport : airports) {
        if (!airport.iso_country.empty()) {
            uniqueCountries.insert(airport.iso_country);
        }
    }

    return vector<string>(uniqueCountries.begin(), uniqueCountries.end());
}

// Common function: collect unique types
static vector<string> getUniqueTypes(const vector<Airport>& airports) {
    set<string> uniqueTypes;

    for (const Airport& airport : airports) {
        if (!airport.type.empty()) {
            uniqueTypes.insert(airport.type);
        }
    }

    return vector<string>(uniqueTypes.begin(), uniqueTypes.end());
}

// Common function: display string list in groups of 20
static bool displayStringListInPages(const vector<string>& items, const string& title) {
    cout << CYAN << title << "\n" << RESET;

    for (int i = 0; i < static_cast<int>(items.size()); i++) {
        cout << YELLOW << i + 1 << ". " << items[i] << endl << RESET;

        if ((i + 1) % 20 == 0 && (i + 1) < static_cast<int>(items.size())) {
            int action = getChoiceOneOrTwo("1. Show next 20", "2. Go back to menu");
            if (action == 2) {
                return false;
            }
        }
    }

    return true;
}

// Common function: display municipality list in groups of 20
static bool displayMunicipalityListInPages(const vector<pair<string, int>>& items, const string& title) {
    cout << CYAN << title << "\n" << RESET;

    for (int i = 0; i < static_cast<int>(items.size()); i++) {
        cout << YELLOW << items[i].first << ": " << items[i].second << endl << RESET;

        if ((i + 1) % 20 == 0 && (i + 1) < static_cast<int>(items.size())) {
            int action = getChoiceOneOrTwo("1. Show next 20", "2. Go back to menu");
            if (action == 2) {
                return false;
            }
        }
    }

    return true;
}

// Common function: select one item from a long list shown 20 at a time
static int selectFromPagedList(const vector<string>& items, const string& title, const string& promptText) {
    if (items.empty()) {
        return -1;
    }

    int start = 0;
    const int pageSize = 20;

    while (start < static_cast<int>(items.size())) {
        cout << CYAN << "\n" << title << "\n" << RESET;

        int end = min(start + pageSize, static_cast<int>(items.size()));

        for (int i = start; i < end; i++) {
            cout << YELLOW << i + 1 << ". " << items[i] << endl << RESET;
        }

        if (end < static_cast<int>(items.size())) {
            int action = getChoiceOneToThree(
                "1. Show next 20",
                "2. Select from shown items",
                "3. Go back to menu"
            );

            if (action == 1) {
                start += pageSize;
                continue;
            }
            else if (action == 2) {
                cout << BLUE << promptText << RESET;
                int choice = getValidatedChoiceInRange(start + 1, end);

                if (choice == -1) {
                    return -1;
                }

                return choice - 1;
            }
            else {
                return -1;
            }
        }
        else {
            cout << BLUE << promptText << RESET;
            int choice = getValidatedChoiceInRange(start + 1, end);

            if (choice == -1) {
                return -1;
            }

            return choice - 1;
        }
    }

    return -1;
}

// Common function: display airports in groups of 20
static bool displayAirportsInPages(const vector<const Airport*>& airportList) {
    const int pageSize = 20;
    int shownCount = 0;

    for (const Airport* airportPtr : airportList) {
        SearchManager::displayAirport(*airportPtr);
        shownCount++;

        if (shownCount % pageSize == 0 && shownCount < static_cast<int>(airportList.size())) {
            int action = getChoiceOneOrTwo("1. Show next 20", "2. Go back to menu");
            if (action == 2) {
                return false;
            }
        }
    }

    return true;
}

// Option 4: count airports by selected type
void AnalysisManager::countByType(const vector<Airport>& airports) {
    vector<string> typeList = getUniqueTypes(airports);

    if (typeList.empty()) {
        cout << RED << "No airport types found.\n" << RESET;
        return;
    }

    if (!displayStringListInPages(typeList, "===== Airport Types =====")) {
        return;
    }

    cout << BLUE << "\nSelect an option: " << RESET;
    int choice = getValidatedChoiceInRange(1, static_cast<int>(typeList.size()));
    if (choice == -1) {
        return;
    }

    string selectedType = typeList[choice - 1];
    int count = 0;

    for (const Airport& airport : airports) {
        if (airport.type == selectedType) {
            count++;
        }
    }

    cout << BOLD << CYAN << "\nTotal " << selectedType << ": " << count << endl << RESET;
}

// Option 10: advanced elevation analysis
void AnalysisManager::showElevationAnalysis(const vector<Airport>& airports) {
    if (airports.empty()) {
        cout << RED << "No airport data available.\n" << RESET;
        return;
    }

    cout << CYAN << "===== Elevation Analysis =====\n" << RESET;
    cout << YELLOW << "1. Show highest & lowest elevation overall\n";
    cout << "2. Show highest & lowest elevation by country\n";
    cout << "3. Show highest & lowest elevation by airport type\n" << RESET;
    cout << BLUE << "Choose option: " << RESET;

    int mode = getValidatedChoiceInRange(1, 3);
    if (mode == -1) {
        return;
    }

    vector<const Airport*> filteredAirports;

    if (mode == 1) {
        for (const Airport& airport : airports) {
            filteredAirports.push_back(&airport);
        }
    }
    else if (mode == 2) {
        vector<string> countryList = getUniqueCountries(airports);

        if (countryList.empty()) {
            cout << RED << "No countries found.\n" << RESET;
            return;
        }

        int selectedIndex = selectFromPagedList(
            countryList,
            "===== Available Countries =====",
            "Select a country number from shown items: "
        );

        if (selectedIndex == -1) {
            return;
        }

        string selectedCountry = countryList[selectedIndex];

        for (const Airport& airport : airports) {
            if (airport.iso_country == selectedCountry) {
                filteredAirports.push_back(&airport);
            }
        }

        cout << GREEN << "\nShowing elevation analysis for country: "
             << selectedCountry << "\n" << RESET;
    }
    else if (mode == 3) {
        vector<string> typeList = getUniqueTypes(airports);

        if (typeList.empty()) {
            cout << RED << "No airport types found.\n" << RESET;
            return;
        }

        int selectedIndex = selectFromPagedList(
            typeList,
            "===== Available Airport Types =====",
            "Select an airport type number from shown items: "
        );

        if (selectedIndex == -1) {
            return;
        }

        string selectedType = typeList[selectedIndex];

        for (const Airport& airport : airports) {
            if (airport.type == selectedType) {
                filteredAirports.push_back(&airport);
            }
        }

        cout << GREEN << "\nShowing elevation analysis for airport type: "
             << selectedType << "\n" << RESET;
    }

    if (filteredAirports.empty()) {
        cout << RED << "No airports found for this selection.\n" << RESET;
        return;
    }

    const Airport* highest = filteredAirports[0];
    const Airport* lowest = filteredAirports[0];

    for (const Airport* airportPtr : filteredAirports) {
        if (airportPtr->elevation_ft > highest->elevation_ft) {
            highest = airportPtr;
        }

        if (airportPtr->elevation_ft < lowest->elevation_ft) {
            lowest = airportPtr;
        }
    }

    cout << CYAN << "\n===== Highest Elevation Airport =====\n" << RESET;
    SearchManager::displayAirport(*highest);

    cout << CYAN << "\n===== Lowest Elevation Airport =====\n" << RESET;
    SearchManager::displayAirport(*lowest);
}

// Option 12: group by municipality
void AnalysisManager::groupByMunicipality(const vector<Airport>& airports) {
    map<string, int> municipalityCounts;

    for (const Airport& airport : airports) {
        string municipality = airport.municipality.empty() ? "Unknown" : airport.municipality;
        municipalityCounts[municipality]++;
    }

    if (municipalityCounts.empty()) {
        cout << RED << "No municipality data available.\n" << RESET;
        return;
    }

    cout << CYAN << "===== Group by Municipality =====\n" << RESET;
    cout << YELLOW << "1. Show all municipalities\n";
    cout << "2. Search a specific municipality\n";
    cout << "3. Show top municipalities by airport count\n" << RESET;
    cout << BLUE << "Choose option: " << RESET;

    int choice = getValidatedChoiceInRange(1, 3);
    if (choice == -1) {
        return;
    }

    if (choice == 1) {
        vector<pair<string, int>> municipalityList(municipalityCounts.begin(), municipalityCounts.end());

        if (!displayMunicipalityListInPages(municipalityList, "\n===== All Municipalities =====")) {
            return;
        }
    }
    else if (choice == 2) {
        string userMunicipality;

        cout << BLUE << "Enter municipality name: " << RESET;
        getline(cin, userMunicipality);

        string lowerInput = userMunicipality;
        transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

        bool found = false;
        vector<pair<string, int>> matchingMunicipalities;

        for (const auto& pair : municipalityCounts) {
            string lowerMunicipality = pair.first;
            transform(lowerMunicipality.begin(), lowerMunicipality.end(), lowerMunicipality.begin(), ::tolower);

            if (lowerMunicipality.find(lowerInput) != string::npos) {
                matchingMunicipalities.push_back(pair);
                found = true;
            }
        }

        if (!found) {
            cout << RED << "No municipality found matching: "
                 << userMunicipality << endl << RESET;
            return;
        }

        if (!displayMunicipalityListInPages(matchingMunicipalities, "\n===== Matching Municipalities =====")) {
            return;
        }
    }
    else if (choice == 3) {
        vector<pair<string, int>> municipalityList(municipalityCounts.begin(), municipalityCounts.end());

        sort(municipalityList.begin(), municipalityList.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.second > b.second;
             });

        cout << BLUE << "How many top municipalities do you want to see? " << RESET;
        int limit = getValidatedPositiveInteger();
        if (limit == -1) {
            return;
        }

        if (limit > static_cast<int>(municipalityList.size())) {
            limit = static_cast<int>(municipalityList.size());
        }

        cout << CYAN << "\n===== Top Municipalities by Airport Count =====\n" << RESET;

        for (int i = 0; i < limit; i++) {
            cout << YELLOW << i + 1 << ". " << municipalityList[i].first
                 << ": " << municipalityList[i].second << endl << RESET;

            if ((i + 1) % 20 == 0 && (i + 1) < limit) {
                int action = getChoiceOneOrTwo("1. Show next 20", "2. Go back to menu");
                if (action == 2) {
                    return;
                }
            }
        }
    }
}

// Option 11: airports with missing IATA
void AnalysisManager::showMissingIATA(const vector<Airport>& airports) {
    cout << BLUE << "===== Airports with Missing IATA Codes =====\n" << RESET;
    cout << YELLOW << "1. Display all airports\n";
    cout << "2. Display only total count\n" << RESET;
    cout << BLUE << "Choose option: " << RESET;

    int choice = getValidatedChoiceInRange(1, 2);
    if (choice == -1) {
        return;
    }

    vector<const Airport*> missingIATAAirports;

    for (const Airport& airport : airports) {
        if (airport.iata_code.empty() ||
            airport.iata_code == "NULL" ||
            airport.iata_code == "N/A") {
            missingIATAAirports.push_back(&airport);
        }
    }

    if (missingIATAAirports.empty()) {
        cout << RED << "No airports with missing IATA codes were found.\n" << RESET;
        return;
    }

    if (choice == 1) {
        if (!displayAirportsInPages(missingIATAAirports)) {
            return;
        }
    }

    cout << BOLD << CYAN << "\nTotal airports with missing IATA codes: "
         << missingIATAAirports.size() << endl << RESET;
}
