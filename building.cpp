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

#include "building.h"

/*
Constructor for the Building class
Initializes the number of floors and creates the specified number of elevators.
*/
Building::Building(int floors, int numElevators): numFloors(floors) {
  unsigned int i;
  for (i = 0; i < numElevators; ++i) {
    elevators.emplace_back(i); // Create elevator with ID i
  }
}

/**
 * Assign a request to an elevator.
 * If an elevator has no current requests, assign it to that elevator.
 * Otherwise, assign it to the elevator with the fewest requests.
 */
void Building::assignRequest(int floor) {
  // unsigned int i;
  // int minRequests = 
  //       elevators[0].hasRequests() ? elevators[0].hasRequests() : 0;
  // int chosen = 0;

  // // Find an elevator with no current requests
  // for (i = 0; i < elevators.size(); ++i) {
  //   if (!elevators[i].hasRequests()) {
  //     chosen = i;
  //     break;
  //   }
  // }

  // // Assign the floor request to the chosen elevator
  // elevators[chosen].addRequest(floor);

  int chosen = -1;
  int minDistance = numFloors + 1;

  for (size_t i = 0; i < elevators.size(); ++i) {
    // Calculate the distance from the elevator to the requested floor
    int distance = abs(elevators[i].getCurrentFloor() - floor);

    // If the elevator has no requests, prioritize selecting this elevator
    if (!elevators[i].hasRequests()) {
        chosen = i;
        break;
    }

    // Select the elevator with the smallest distance
    if (distance < minDistance) {
        minDistance = distance;
        chosen = i;
    }
  }

  // Assign the request to the chosen elevator
  if (chosen != -1) {
      elevators[chosen].addRequest(floor);
  }
}

// Progress all elevators by one simulation step.
void Building::stepAll() {
  for (auto& elevator : elevators) {
    elevator.step();
  }
}

// Display the status of all elevators (e.g., current floor, requests queue)
void Building::displayStatus() const {
  for (const auto& elevator : elevators) {
    elevator.displayStatus();
  }
}

// Return the total number of floors in the building.
int Building::getNumFloors() const {
  return numFloors;
}