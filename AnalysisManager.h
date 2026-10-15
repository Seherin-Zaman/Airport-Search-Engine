#ifndef ANALYSISMANAGER_H        // Include guard to prevent multiple inclusions of this header file
#define ANALYSISMANAGER_H        // Include guard to prevent multiple inclusions of this header file

#include <vector>                // Include vector for using vector data structure
#include "Airport.h"             // Include the header for airport struct defination
using namespace std;

// Handles analysis-related features
class AnalysisManager {
public:
    static void countByType(const vector<Airport>& airports);             // Count airports by selected type
    static void showElevationAnalysis(const vector<Airport>& airports);  // Show elevation analysis based on user-selected crieria
    static void showMissingIATA(const vector<Airport>& airports);        // Show airports with missing IATA codes with option to display details or just count
    static void groupByMunicipality(const vector<Airport>& airports);    // Group airports by municipality with options to show all, search specific municipality, or show top municiplaities by airportt count
    //static bool handleInvalidInput();
};

#endif
