/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: Building.h
 * Purpose: This header file defines the Building class, which manages 
 *          a collection of Elevator objects and provides functionality 
 *          to assign floor requests, advance elevator states, and display 
 *          elevator status. It simulates how a building handles multiple 
 *          elevators across different floors.
 */

#ifndef BUILDING_H
#define BUILDING_H

#include "Elevator.h"
#include <vector>
using namespace std;

/**
 * The Building class represents a multi-story building that contains
 * multiple elevators. It handles assigning elevator requests,
 * stepping all elevators forward in their state machines, and 
 * displaying their status.
 */
class Building {
  private:
    int numFloors;                // Total number of floors in the building
    vector<Elevator> elevators;   // List of elevators in the building

  public:
    /**
     * Constructor that initializes the building with a given number
     * of floors and elevators.
     * @param floors - number of floors in the building
     * @param numElevators - number of elevators in the building
     */
    Building(int floors, int numElevators);

    /**
     * Assigns a floor request to an appropriate elevator.
     * @param floor - the floor number being requested
     */
    void assignRequest(int floor);

    // Advances each elevator by one step in its operation.
    void stepAll();

    // Displays the current status of all elevators in the building.
    void displayStatus() const;

    // Returns the total number of floors in the building.
    int getNumFloors() const;
};

#endif