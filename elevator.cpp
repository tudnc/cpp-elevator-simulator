/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: elevator.cpp
 * Purpose: This file implements the Elevator class, which simulates 
 *          the behavior of a single elevator including movement, request 
 *          processing, and status display.
 */

#include "elevator.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Constructor initializes the elevator's ID and sets initial state.
Elevator::Elevator(int id) 
  : id(id), currentFloor(0), direction(IDLE), doorOpen(false) {}
  
// Add a floor request to the elevator's request queue.
void Elevator::addRequest(int floor) {
  requests.push_back(floor);
}

// Move the elevator one step toward its next requested floor.
void Elevator::step() {
  if (requests.empty()) {
    direction = IDLE;
    return;
  }

  int target = requests.front();
  if (currentFloor < target) {
    currentFloor++;
    direction = UP;
  } else if (currentFloor > target) {
    currentFloor--;
    direction = DOWN;
  } else {
    // Elevator has reached the target floor
    doorOpen = true;
    cout << "Elevator " << id << " arrived at floor " << currentFloor 
         << ". Doors opening..." << endl;

    // Keep the door open for 2 seconds to visualize the door status
    this_thread::sleep_for(std::chrono::seconds(2));

    doorOpen = false;

    // Remove the completed request from the queue
    requests.erase(requests.begin());

    // Update the elevator's direction (set to IDLE if there are no remaining requests)
    direction = requests.empty() ? IDLE : direction;
  }
}

// Print the current status of the elevator to the console.
void Elevator::displayStatus() const {
  cout << "[Elevator " << id << "] Floor: " << currentFloor
       << ", Direction: " << (direction == UP ? "UP" : 
                             (direction == DOWN ? "DOWN" : "IDLE"))
       << ", Door: " << (doorOpen ? "Open" : "Closed") << endl;
}

// Return true if the elevator has pending requests.
bool Elevator::hasRequests() const {
  return !requests.empty();
}

// Getter method to return the current floor of the elevator
int Elevator::getCurrentFloor() const {
    return currentFloor;
}
