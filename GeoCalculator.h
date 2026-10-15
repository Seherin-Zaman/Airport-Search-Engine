#ifndef GEOCALCULATOR_H            // Include guard to prevent multiple inclusions of this header file
#define GEOCALCULATOR_H            // Include guard to prevent multiple inclusions of this header file

#include <vector>                  // Include vector for using vector data structure
#include "Airport.h"               // Include the header for airport struct defination
using namespace std;

// Handles geographical calculations like distance between airports and finding nearest airport
class GeoCalculator {
public:
    static double haversine(double lat1, double lon1, double lat2, double lon2);    // Calculate distance between two coordinates using Haversine formula
    static void distanceBetweenAirports(const vector<Airport>& airports);           // Calculate distance between two airports based on user-selected criteria (IATA codes or names) with validation
    static void findNearestAirport(const vector<Airport>& airports);                // Find nearest airport to given coordinates with validation
    static void airportsWithinRadius(const vector<Airport>& airports);              // List airports within a certain radius of given coordinates with validation and display total count
};

#endif