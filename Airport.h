#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
using namespace std;

// Structure representing a single airport record
// Each object of this struct stores data from one row of the CSV file
struct Airport {
    string ident;        // Unique airport identifier
    string type;         // Type of airport (e.g., small_airport, heliport)
    string name;         // Airport name
    int elevation_ft;    // Elevation in feet

    string continent;    // Continent code (e.g., NA, EU)
    string iso_country;  // Country code (e.g., US, UK)
    string iso_region;   // Region/state code

    string municipality; // City or municipality
    string icao_code;    // ICAO airport code
    string iata_code;    // IATA airport code

    string gps_code;     // GPS code
    string local_code;   // Local airport code

    double latitude;     // Latitude coordinate
    double longitude;    // Longitude coordinate
};

#endif
