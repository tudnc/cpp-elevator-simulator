/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: building.cpp
 * Purpose: Implementation of the Building class which manages a group of 
 *          elevators in a building with multiple floors. It handles request 
 *          assignment, status display, and simulation stepping for all 
 *          elevators.
 */

#include "Building.h"
#include "Logger.h"

/*
Constructor for the Building class
Initializes the number of floors and creates the specified number of elevators.
*/
Building::Building(int floors, int numElevators): numFloors(floors) {
  for (int i = 0; i < numElevators; ++i) {
    elevators.emplace_back(i); // Create elevator with ID i
  }
  Logger::log("Building initialized with " + to_string(numFloors) + 
              " floors and " + to_string(numElevators) + " elevators.");
}

/**
 * Assign a request to an elevator.
 * If an elevator has no current requests, assign it to that elevator.
 * Otherwise, assign it to the elevator with the fewest requests.
 */
void Building::assignRequest(int floor) {
  int chosen = -1;
  int minDistance = numFloors + 1;

  for (size_t i = 0; i < elevators.size(); ++i) {
    int distance = abs(elevators[i].getCurrentFloor() - floor);

    if (!elevators[i].hasRequests()) {
        chosen = i;
        Logger::log("Floor request " + to_string(floor) + 
                    " assigned to idle Elevator " + to_string(i));
        break;
    }

    if (distance < minDistance) {
        minDistance = distance;
        chosen = i;
    }
  }

  if (chosen != -1) {
      elevators[chosen].addRequest(floor);
      Logger::log("Floor request " + to_string(floor) + 
                  " assigned to Elevator " + to_string(chosen) +
                  " (distance = " + to_string(minDistance) + ")");
  } else {
      Logger::log("No available elevator for floor request " + to_string(floor));
  }
}

// Progress all elevators by one simulation step.
void Building::stepAll() {
  Logger::log("Building stepping all elevators.");
  for (auto& elevator : elevators) {
    elevator.step();
  }
}

// Display the status of all elevators (e.g., current floor, requests queue)
void Building::displayStatus() const {
  Logger::log("Displaying status of all elevators.");
  for (const auto& elevator : elevators) {
    elevator.displayStatus();
  }
}

// Return the total number of floors in the building.
int Building::getNumFloors() const {
  return numFloors;
}
