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
#include "logger.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Constructor initializes the elevator's ID and sets initial state.
Elevator::Elevator(int id) 
  : id(id), currentFloor(0), direction(IDLE), doorOpen(false) {
    Logger::log("Elevator " + to_string(id) + " initialized at floor 0.");
}
  
// Add a floor request to the elevator's request queue.
void Elevator::addRequest(int floor) {
    if (floor == currentFloor) {
        doorOpen = true;
        cout << "Elevator " << id << " opening doors at floor " 
             << floor << endl;
        Logger::log("Elevator " + to_string(id) + 
                    " instantly opened doors at floor " + to_string(floor));
        this_thread::sleep_for(chrono::seconds(2));
        doorOpen = false;
        return;
    }

    if (floor > currentFloor) {
        upRequests.insert(floor);
        Logger::log("Elevator " + to_string(id) + " added UP request to floor " 
                    + to_string(floor));
    } else if (floor < currentFloor) {
        downRequests.insert(floor);
        Logger::log("Elevator " + to_string(id) + 
                    " added DOWN request to floor " + to_string(floor));
    }
}

// Move the elevator one step toward its next requested floor.
void Elevator::step() {
    if (upRequests.empty() && downRequests.empty()) {
        if (direction != IDLE) {
            Logger::log("Elevator " + to_string(id) + " is now IDLE.");
        }
        direction = IDLE;
        return;
    }

    if (direction == IDLE) {
        if (!upRequests.empty()) {
            direction = UP;
            Logger::log("Elevator " + to_string(id) + 
                        " changed direction to UP.");
        }
        else if (!downRequests.empty()) {
            direction = DOWN;
            Logger::log("Elevator " + to_string(id) + 
                        " changed direction to DOWN.");
        }
    }

    if (direction == UP) {
        auto it = upRequests.begin();
        int target = *it;

        if (currentFloor < target) {
            currentFloor++;
            Logger::log("Elevator " + to_string(id) + " moving UP to floor " + 
                        to_string(currentFloor));
        } else if (currentFloor == target) {
            doorOpen = true;
            cout << "Elevator " << id << " arrived at floor " << currentFloor 
                 << ". Doors opening..." << endl;
            Logger::log("Elevator " + to_string(id) + " arrived at floor " + 
                        to_string(currentFloor));
            this_thread::sleep_for(chrono::seconds(2));
            doorOpen = false;
            upRequests.erase(it);
            Logger::log("Elevator " + to_string(id) + 
                        " closed doors at floor " + to_string(currentFloor));
        }

        if (upRequests.empty()) {
            if (!downRequests.empty()) {
                direction = DOWN;
                Logger::log("Elevator " + to_string(id) + 
                            " switched direction to DOWN.");
            } else {
                direction = IDLE;
                Logger::log("Elevator " + to_string(id) + " is now IDLE.");
            }
        }
    } else if (direction == DOWN) {
        auto it = downRequests.begin();
        int target = *it;

        if (currentFloor > target) {
            currentFloor--;
            Logger::log("Elevator " + to_string(id) + 
                        " moving DOWN to floor " + to_string(currentFloor));
        } else if (currentFloor == target) {
            doorOpen = true;
            cout << "Elevator " << id << " arrived at floor " << currentFloor 
                 << ". Doors opening..." << endl;
            Logger::log("Elevator " + to_string(id) + " arrived at floor " + 
                        to_string(currentFloor));
            this_thread::sleep_for(chrono::seconds(2));
            doorOpen = false;
            downRequests.erase(it);
            Logger::log("Elevator " + to_string(id) + 
                        " closed doors at floor " + to_string(currentFloor));
        }

        if (downRequests.empty()) {
            if (!upRequests.empty()) {
                direction = UP;
                Logger::log("Elevator " + to_string(id) + 
                            " switched direction to UP.");
            } else {
                direction = IDLE;
                Logger::log("Elevator " + to_string(id) + " is now IDLE.");
            }
        }
    }
}

// Print the current status of the elevator to the console.
void Elevator::displayStatus() const {
    cout << "[Elevator " << id << "] Floor: " << currentFloor
        << ", Direction: " << (direction == UP ? "UP" : 
                                (direction == DOWN ? "DOWN" : "IDLE"))
        << ", Door: " << (doorOpen ? "Open" : "Closed") << endl;
    Logger::log("Status -> Elevator " + to_string(id) + 
        " | Floor: " + to_string(currentFloor) + 
        " | Direction: " + (direction == UP ? "UP" : 
                            (direction == DOWN ? "DOWN" : "IDLE")) + 
        " | Door: " + (doorOpen ? "Open" : "Closed"));
}

// Return true if the elevator has pending requests.
bool Elevator::hasRequests() const {
    return !(upRequests.empty() && downRequests.empty());
}

// Getter method to return the current floor of the elevator
int Elevator::getCurrentFloor() const {
    return currentFloor;
}
