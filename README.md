# Airport-Search-Engine
This project is a console-based C++ Airport Search Engine developed as part of the Computer Science and Programming module.

The system reads airport data from a CSV file and allows users to search, analyse, modify, and perform geographical calculations efficiently. Advanced features such as distance calculations, filtering, and data persistence are included to enhance functionality and performance.

# System Overview
The system is designed for Nottingham SkyRoute Explorer (NSE).

The main objective of this project is to:
1. Demonstrate strong programming skills in C++
2. Implement efficient CSV file handling (read and write)
3. Provide a structured and user-friendly command-line interface
4. Apply searching, filtering, and analytical techniques
5. Integrate geographical calculations using mathematical formulas
6. Support dynamic data modification and persistence

# System Features
## 1. Search Features
1. Search airports by Country
2. Search airports by Name (full or partial)
3. Search airports by IATA Code

## 2. Analysis Features
1. Count airports by Type
2. Identify Highest and Lowest Elevation Airports
3. Find airports with Missing IATA Codes
4. Group airports by Municipality

## 3. Geographical Features
1. Calculate distance between two airports (Haversine formula)
2. Find nearest airport based on coordinates
3. List airports within a specified radius
## 4. Data Management Features
1. Add new airport records
2. Save updated airport data to CSV file

# System User
## User
The user can:
1. Search airport data
2. Analyse airport statistics
3. Perform geographical calculations
4. Add new airport records
5. Save updated data

# How to Run the Program
## Step 1 – Compile
g++ main.cpp AirportManager.cpp FileHandler.cpp SearchManager.cpp AnalysisManager.cpp GeoCalculator.cpp -o app.exe
## Step 2 – Run
app.exe

# Use Cases
## Use Case 1 – Start System
Description: User runs the application
Outcome: Main menu is displayed

## Use Case 2 – Select Menu Option

Description: User selects an option from the menu
Outcome: Relevant module is executed
Validation: Invalid input is handled and user is prompted again

### Search Module
## Use Case 3 – Search by Country
Description: User selects search by country
Outcome:
  1. User selects from available countries or enters manually
  2. Matching airports are displayed

## Use Case 4 – Search by Name
Description: User searches using full or partial airport name
Outcome:
  1. Matching airports are displayed
  2. Case-insensitive search is supported

## Use Case 5 – Search by IATA Code
Description: User searches using IATA code
Outcome:
 1. Exact airport match is displayed
 2. Handles invalid or missing codes

## Analysis Module
## Use Case 6 – Count Airports by Type
Description: User selects airport type
Outcome: Displays total number of airports of that type

## Use Case 7 – Elevation Analysis
Description: User selects elevation analysis
Outcome:
  1. Shows highest and lowest elevation airports
  2. Supports filtering by country or airport type

## Use Case 8 – Missing IATA Codes
Description: User checks airports without IATA codes
Outcome:
  1. Displays list or total count

## Use Case 9 – Group by Municipality
Description: User groups airports by municipality
Outcome:
  1. Displays municipality counts
  2. Supports searching and ranking
## Geographical Module
## Use Case 10 – Distance Between Airports
Description: User enters two airports (IATA or name)
Outcome:
   1. Distance is calculated using the Haversine formula

## Use Case 11 – Find Nearest Airport
Description: User enters coordinates
Outcome:
  1. Nearest airport is displayed

## Use Case 12 – Airports Within Radius
Description: User enters coordinates and radius
Outcome:
 1. Airports within the specified range are displayed

## Data Management Module
## Use Case 13 – Add New Airport
Description: User selects option to add a new airport
Outcome:
  1. User inputs airport details (name, country, coordinates, etc.)
  2. System validates input
  3. New airport object is created and added to dataset

## Use Case 14 – Save Airport Data
Description: User selects save option
Outcome:
 1. Updated airport data is written to CSV file
 2. Changes are stored permanently
    
# Key Technical Features
1. CSV file handling using file streams
2. File writing support for persistent data storage
3. Efficient data structures (vector, map, set)
4. Modular design using multiple classes
5. Input validation and error handling
6. Pagination (displaying results in groups of 20)
7. Case-insensitive searching
7. Mathematical computation using the Haversine formula

# Testing

Extensive manual testing has been conducted and documented in the GitHub repository and report.

# Tested Scenarios
1. Invalid user inputs
2. Empty dataset handling
3. Incorrect search values
4. Missing IATA codes
5. Municipality grouping
6. Adding new airport records
7. Saving and verifying CSV updates
8. Edge cases and boundary conditions
  
# Limitations / Future Improvements
1. Could implement inheritence
2. Could implement polymorphism
3. Could implement Graphical User Interface
4. Have to press Enter twice for some functions to run which can be fixed later.

# Reflection
Through this project, I have:
1. Improved my understanding of C++ programming concepts
2. Learned how to handle real-world datasets using CSV files
3. Applied data structures effectively
4. Developed modular and reusable code
5. Gained experience in file handling (reading and writing)
6. Strengthened skills in debugging and testing
7. Built a complete console-based application system

# Conclusion

This project successfully demonstrates the implementation of a fully functional airport search and analysis system, combining data processing, algorithmic thinking, and user interaction in C++.
