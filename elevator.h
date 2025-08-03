/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: elevator.h
 * Purpose: Define the Elevator class, representing individual 
 *          elevator behavior
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <string>
using namespace std;

// Enum to represent the movement direction of the elevator
enum Direction { UP, DOWN, IDLE };

class Elevator {
  private:
    int id;                     // Unique ID for the elevator
    int currentFloor;           // Current floor the elevator is on
    Direction direction;        // Current movement direction of the elevator
    bool doorOpen;              // Whether the elevator door is open
    vector<int> requests;  // Queue of requested destination floors

  public:
    // Constructor: Initialize the elevator with an ID and set defaults
    Elevator(int id);

    // Add a floor request to the queue
    void addRequest(int floor);

    // Move the elevator one step toward the next requested floor
    void step();

    // Display the current status of the elevator (floor, direction, door)
    void displayStatus() const;

    // Check if the elevator has any pending requests
    bool hasRequests() const;

    int getCurrentFloor() const;
};

#endif

