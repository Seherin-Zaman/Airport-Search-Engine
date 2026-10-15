#include "SearchManager.h"       // Include the header for search-related features
#include "Colors.h"              // Include the header for color definations
#include <iostream>              // Include iostream for console I/O operations
#include <algorithm>             // Include algorithm for transforming strings
#include <set>                   // Include set for storing unique values
#include <vector>                // Include vector for using vector data structure
#include <cctype>                // Include cctype for character handling functions
#include <limits>                // Include limits for numeric_limits

using namespace std;

// Common function: clear input buffer safely
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Common function for asking user to choose 1 or 2 only
int getChoiceOneOrTwo(const string& option1, const string& option2) {
    int choice;

    while (true) {
        cout << YELLOW << option1 << "\n";
        cout << option2 << RESET << "\n";
        cout << "Choose option: ";
        cin >> choice;

        if (!cin.fail() && (choice == 1 || choice == 2)) {
            clearInputBuffer();
            return choice;
        }

        clearInputBuffer();
        cout << RED << "Please enter 1 or 2.\n" << RESET;
    }
}

// Common function: invalid input
int handleInvalidInput() {
    cout << RED << "\nInvalid input.\n" << RESET;
    return getChoiceOneOrTwo("1. Continue", "2. Go back to menu");
}

// Common function: after every 20 shown results
int handleTwentyResultsPrompt() {
    cout << CYAN << "\n20 results shown.\n" << RESET;
    return getChoiceOneOrTwo("1. Continue", "2. Go back to menu");
}

// Common function: when showing long option lists in groups of 20
int handleTwentyListPrompt() {
    cout << CYAN << "\n20 items shown.\n" << RESET;
    return getChoiceOneOrTwo("1. Show next 20", "2. Go back to menu");
}

// Common function: no results found
int handleNoResultsPrompt() {
    return getChoiceOneOrTwo("1. Continue", "2. Go back to menu");
}

// Common function: after successful search
int handleSearchAgainPrompt() {
    return getChoiceOneOrTwo("1. Search again", "2. Go back to menu");
}

// Common function: validates menu choice 1 or 2 and reprints menu each time
int getValidatedMenuChoice(const string& option1, const string& option2) {
    int choice;

    while (true) {
        cout << YELLOW << option1 << "\n";
        cout << option2 << RESET << "\n";
        cout << "Choose option: ";
        cin >> choice;

        if (!cin.fail() && (choice == 1 || choice == 2)) {
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

// Common function: validates numeric choice within a range and reprints selection prompt
int getValidatedIndexChoice(int maxValue, const string& promptText) {
    int choice;

    while (true) {
        cout << promptText;
        cin >> choice;

        if (!cin.fail() && choice >= 1 && choice <= maxValue) {
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

// Common function: continue showing search results every 20 items
bool continueDisplayingResults(int shownCount) {
    if (shownCount % 20 == 0) {
        int action = handleTwentyResultsPrompt();
        if (action == 2) {
            return false;
        }
    }
    return true;
}

// Common function: display a long list in groups of 20
bool displayListInPages(const vector<string>& items, const string& title) {
    cout << BOLD << CYAN << "\n" << title << "\n" << RESET;

    for (int i = 0; i < static_cast<int>(items.size()); i++) {
        cout << i + 1 << ". " << YELLOW << items[i] << RESET << endl;

        if ((i + 1) % 20 == 0 && (i + 1) < static_cast<int>(items.size())) {
            int action = handleTwentyListPrompt();
            if (action == 2) {
                return false;
            }
        }
    }

    return true;
}

// Displays full details of one airport
void SearchManager::displayAirport(const Airport& airport) {
    cout << BOLD << CYAN << "----------------------------------------\n" << RESET;
    cout << "Name: " << airport.name << endl;
    cout << "Type: " << airport.type << endl;
    cout << "Country: " << airport.iso_country << endl;
    cout << "Region: " << airport.iso_region << endl;
    cout << "Municipality: " << airport.municipality << endl;
    cout << "IATA Code: " << airport.iata_code << endl;
    cout << "ICAO Code: " << airport.icao_code << endl;
    cout << "Elevation (ft): " << airport.elevation_ft << endl;
    cout << "Latitude: " << airport.latitude << endl;
    cout << "Longitude: " << airport.longitude << endl;
}

// Option 1: Search airports by country
void SearchManager::searchByCountry(const vector<Airport>& airports) {
    while (true) {
        int mode;
        string selectedCountry;

        cout << "===== Search Airports by Country =====\n";

        mode = getValidatedMenuChoice(
            "1. Show available countries",
            "2. Enter country code manually"
        );
        if (mode == -1) {
            return;
        }

        if (mode == 1) {
            set<string> uniqueCountries;

            for (const Airport& airport : airports) {
                if (!airport.iso_country.empty()) {
                    uniqueCountries.insert(airport.iso_country);
                }
            }

            vector<string> countryList(uniqueCountries.begin(), uniqueCountries.end());

            if (!displayListInPages(countryList, "===== Available Countries =====")) {
                return;
            }

            int choice = getValidatedIndexChoice(
                static_cast<int>(countryList.size()),
                "\nSelect a country: "
            );
            if (choice == -1) {
                return;
            }

            selectedCountry = countryList[choice - 1];
        }
        else {
            cout << BOLD << CYAN << "Enter country code (example: US, GB, BD): " << RESET;
            cin >> selectedCountry;
            clearInputBuffer();

            transform(selectedCountry.begin(), selectedCountry.end(),
                      selectedCountry.begin(), ::toupper);
        }

        cout << "\nSearching airports in " << selectedCountry << "...\n\n";

        bool found = false;
        int count = 0;
        int shownCount = 0;

        for (const Airport& airport : airports) {
            if (airport.iso_country == selectedCountry) {
                displayAirport(airport);
                found = true;
                count++;
                shownCount++;

                if (!continueDisplayingResults(shownCount)) {
                    return;
                }
            }
        }

        if (!found) {
            cout << RED << "No airports found for country: " << selectedCountry << endl << RESET;

            int action = handleNoResultsPrompt();
            if (action == 2) {
                return;
            }

            continue;
        }

        cout << BOLD << CYAN << "\nTotal airports found: " << count << endl << RESET;

        int action = handleSearchAgainPrompt();
        if (action == 2) {
            return;
        }
    }
}

// Option 2: Search airports by name
void SearchManager::searchByName(const vector<Airport>& airports) {
    while (true) {
        int mode;
        string searchText;

        cout << BOLD << CYAN << "===== Search Airports by Name =====\n" << RESET;

        mode = getValidatedMenuChoice(
            "1. Enter full or partial airport name",
            "2. Enter first letter to see available airport names"
        );
        if (mode == -1) {
            return;
        }

        if (mode == 1) {
            cout << "Enter full or partial airport name: ";
            getline(cin, searchText);
        }
        else {
            char firstLetter;

            while (true) {
                cout << "Enter first letter: ";
                cin >> firstLetter;

                if (!cin.fail() && isalpha(firstLetter)) {
                    clearInputBuffer();
                    break;
                }

                clearInputBuffer();

                int action = handleInvalidInput();
                if (action == 2) {
                    return;
                }
            }

            firstLetter = tolower(firstLetter);

            vector<string> matchingNames;

            for (const Airport& airport : airports) {
                if (!airport.name.empty() && tolower(airport.name[0]) == firstLetter) {
                    matchingNames.push_back(airport.name);
                }
            }

            if (matchingNames.empty()) {
                cout << RED << "No airport names found starting with: "
                     << firstLetter << endl << RESET;

                int action = handleNoResultsPrompt();
                if (action == 2) {
                    return;
                }

                continue;
            }

            if (!displayListInPages(matchingNames, "===== Available Airports =====")) {
                return;
            }

            int choice = getValidatedIndexChoice(
                static_cast<int>(matchingNames.size()),
                "\nSelect an airport: "
            );
            if (choice == -1) {
                return;
            }

            searchText = matchingNames[choice - 1];
        }

        string lowerSearch = searchText;
        transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);

        cout << CYAN << "\nSearch results:\n" << RESET;

        bool found = false;
        int count = 0;
        int shownCount = 0;

        for (const Airport& airport : airports) {
            string lowerName = airport.name;
            transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

            if (lowerName.find(lowerSearch) != string::npos) {
                displayAirport(airport);
                found = true;
                count++;
                shownCount++;

                if (!continueDisplayingResults(shownCount)) {
                    return;
                }
            }
        }

        if (!found) {
            cout << RED << "No airports found matching: " << searchText << endl << RESET;

            int action = handleNoResultsPrompt();
            if (action == 2) {
                return;
            }

            continue;
        }

        cout << BOLD << CYAN << "\nTotal airports found: " << count << endl << RESET;

        int action = handleSearchAgainPrompt();
        if (action == 2) {
            return;
        }
    }
}

// Option 3: Search airports by IATA code
void SearchManager::searchByIATA(const vector<Airport>& airports) {
    while (true) {
        int mode;
        string selectedIATA;

        cout << BOLD << CYAN << "===== Search Airport by IATA Code =====\n" << RESET;

        mode = getValidatedMenuChoice(
            "1. Show available IATA codes",
            "2. Enter IATA code manually"
        );
        if (mode == -1) {
            return;
        }

        if (mode == 1) {
            set<string> uniqueIATA;

            for (const Airport& airport : airports) {
                if (!airport.iata_code.empty()) {
                    uniqueIATA.insert(airport.iata_code);
                }
            }

            vector<string> iataList(uniqueIATA.begin(), uniqueIATA.end());

            if (!displayListInPages(iataList, "===== Available IATA Codes =====")) {
                return;
            }

            int choice = getValidatedIndexChoice(
                static_cast<int>(iataList.size()),
                "\nSelect an IATA code: "
            );
            if (choice == -1) {
                return;
            }

            selectedIATA = iataList[choice - 1];
        }
        else {
            while (true) {
                cout << BLUE << "Enter IATA code (example: LHR, JFK, DAC): " << RESET;
                cin >> selectedIATA;

                if (!cin.fail() && !selectedIATA.empty()) {
                    clearInputBuffer();
                    transform(selectedIATA.begin(), selectedIATA.end(),
                              selectedIATA.begin(), ::toupper);
                    break;
                }

                clearInputBuffer();

                int action = handleInvalidInput();
                if (action == 2) {
                    return;
                }
            }
        }

        cout << CYAN << "\nSearch results:\n" << RESET;

        bool found = false;
        int count = 0;
        int shownCount = 0;

        for (const Airport& airport : airports) {
            string airportIATA = airport.iata_code;
            transform(airportIATA.begin(), airportIATA.end(),
                      airportIATA.begin(), ::toupper);

            if (airportIATA == selectedIATA) {
                displayAirport(airport);
                found = true;
                count++;
                shownCount++;

                if (!continueDisplayingResults(shownCount)) {
                    return;
                }
            }
        }

        if (!found) {
            cout << RED << "No airport found with IATA code: " << selectedIATA << endl << RESET;

            int action = handleNoResultsPrompt();
            if (action == 2) {
                return;
            }

            continue;
        }

        cout << BOLD << CYAN << "\nTotal airports found: " << count << endl << RESET;

        int action = handleSearchAgainPrompt();
        if (action == 2) {
            return;
        }
    }
}
