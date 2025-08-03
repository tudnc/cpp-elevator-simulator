/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: main.cpp
 * Purpose: Simulate the operation of a building with multiple elevators.
 *          Users can input floor requests, and elevators will respond 
 *          accordingly.
 */

#include <iostream>
#include "building.h"
#include "logger.h"
#include <thread>     // For sleep functionality
#include <chrono>     // For time intervals
using namespace std;

int main() {
  Logger::init("elevator_log.txt"); // Initialize logging
  Logger::log("Simulation started.");

  /**
   * Variables:
   * NUM_FLOORS: Total number of floors in the building
   * NUM_ELEVATORS: Total number of elevators in the building
   * WAITING_TIME: Delay time (in seconds) between each simulation step
   * floor: Stores user input for floor requests
   * running: Controls the main simulation loop
   */
  int floor;
  const int NUM_FLOORS = 10;
  const int NUM_ELEVATORS = 2;
  const int WAITING_TIME = 2;
  bool running = true;

  // Create a building object with specified floors and elevators
  Building building(NUM_FLOORS, NUM_ELEVATORS);
  
  // Display initial simulation status
  cout << "Elevator Simulation Started (" << NUM_ELEVATORS 
       << " elevators, Floors 0-" << NUM_FLOORS - 1 << ")\n";
  
  // Main loop for simulation
  while (running) {
    // Display the current status of all elevators
    building.displayStatus();

    /**
     * Prompt:
     * - User can enter a floor number to request an elevator.
     * - Press Enter to let elevators continue moving without adding a new request.
     * - Enter -1 to quit the simulation.
     */
    cout << "Enter floor request (0-" << NUM_FLOORS - 1
         << "), press Enter to continue, or -1 to quit: ";
    string input;
    getline(cin, input);

    // If user presses Enter without input → just move elevators one step
    if (input.empty()) {
        Logger::log("No request entered, stepping elevators.");
        building.stepAll();
        this_thread::sleep_for(chrono::seconds(1));
        continue;
    }

    // Convert input string to integer (floor number)
    floor = stoi(input);  // convert string to int

    // Check if user wants to end the simulation
    if (floor == -1) {
      Logger::log("User exited simulation.");
      running = false;
      break;
    }

    // Validate floor input (must be within building's range)
    if (floor < 0 || floor >= NUM_FLOORS) {
      cout << "Invalid floor. Try again.\n";
      Logger::log("Invalid floor entered: " + to_string(floor));
      continue;
    }

    // Assign the request to the nearest/available elevator
    Logger::log("User requested floor " + to_string(floor));
    building.assignRequest(floor);

    // Move elevators one step toward their next destination
    building.stepAll();

    // Wait for a few seconds before the next loop (simulates real-time delay)
    this_thread::sleep_for(chrono::seconds(WAITING_TIME));
  }

  // Exit message
  cout << "Simulation ended.\n";
  Logger::log("Simulation ended.");
  Logger::close();
  return 0;
}


/*
Sample Run 1:
➜  elevator git:(develop) ✗ make run
[ - make run -> Project 1: Elevator Simulator]
Elevator Simulation Started (2 elevators, Floors 0-9)
[Elevator 0] Floor: 0, Direction: IDLE, Door: Closed
[Elevator 1] Floor: 0, Direction: IDLE, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit: 4
[Elevator 0] Floor: 1, Direction: UP, Door: Closed
[Elevator 1] Floor: 0, Direction: IDLE, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit: 2
[Elevator 0] Floor: 2, Direction: UP, Door: Closed
[Elevator 1] Floor: 1, Direction: UP, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit:
[Elevator 0] Floor: 3, Direction: UP, Door: Closed
[Elevator 1] Floor: 2, Direction: UP, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit:
Elevator 1 arrived at floor 2. Doors opening...
[Elevator 0] Floor: 4, Direction: UP, Door: Closed
[Elevator 1] Floor: 2, Direction: IDLE, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit: 5
Elevator 0 arrived at floor 4. Doors opening...
[Elevator 0] Floor: 4, Direction: IDLE, Door: Closed
[Elevator 1] Floor: 3, Direction: UP, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit:
[Elevator 0] Floor: 4, Direction: IDLE, Door: Closed
[Elevator 1] Floor: 4, Direction: UP, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit:
[Elevator 0] Floor: 4, Direction: IDLE, Door: Closed
[Elevator 1] Floor: 5, Direction: UP, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit:
Elevator 1 arrived at floor 5. Doors opening...
[Elevator 0] Floor: 4, Direction: IDLE, Door: Closed
[Elevator 1] Floor: 5, Direction: IDLE, Door: Closed
Enter floor request (0-9), press Enter to continue, or -1 to quit: -1
Simulation ended.
*/