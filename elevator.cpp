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
  if (floor == currentFloor) {
      // Nếu đang ở tầng đó, mở cửa luôn
      doorOpen = true;
      cout << "Elevator " << id << " opening doors at floor " << floor << endl;
      this_thread::sleep_for(chrono::seconds(2));
      doorOpen = false;
      return;
  }

  if (floor > currentFloor) {
      upRequests.insert(floor);
  } else if (floor < currentFloor) {
      downRequests.insert(floor);
  }
}


// Move the elevator one step toward its next requested floor.
void Elevator::step() {
  if (upRequests.empty() && downRequests.empty()) {
      direction = IDLE;
      return;
  }

  if (direction == IDLE) {
      // Khởi đầu chọn hướng theo request gần nhất
      if (!upRequests.empty()) direction = UP;
      else if (!downRequests.empty()) direction = DOWN;
  }

  if (direction == UP) {
      auto it = upRequests.begin();
      int target = *it;

      if (currentFloor < target) {
          currentFloor++;
      } else if (currentFloor == target) {
          doorOpen = true;
          cout << "Elevator " << id << " arrived at floor " << currentFloor << ". Doors opening..." << endl;
          this_thread::sleep_for(chrono::seconds(2));
          doorOpen = false;
          upRequests.erase(it);
      }

      // If there are no more upRequests, change direction or go idle
      if (upRequests.empty()) {
          if (!downRequests.empty())
              direction = DOWN;
          else
              direction = IDLE;
      }
  } else if (direction == DOWN) {
      auto it = downRequests.begin();
      int target = *it;

      if (currentFloor > target) {
          currentFloor--;
      } else if (currentFloor == target) {
          doorOpen = true;
          cout << "Elevator " << id << " arrived at floor " << currentFloor << ". Doors opening..." << endl;
          this_thread::sleep_for(chrono::seconds(2));
          doorOpen = false;
          downRequests.erase(it);
      }

      // If there are no more downRequests, change direction or go idle
      if (downRequests.empty()) {
          if (!upRequests.empty())
              direction = UP;
          else
              direction = IDLE;
      }
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
    return !(upRequests.empty() && downRequests.empty());
}


// Getter method to return the current floor of the elevator
int Elevator::getCurrentFloor() const {
    return currentFloor;
}
