/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: elevator.h
 * Purpose: Defines the Elevator class responsible for handling 
 *          elevator operations, including movement, requests, 
 *          door status, and sound notifications.
 * 
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <string>
#include <set>
#include <memory>
#include <SFML/Audio.hpp>  // SFML Audio Library
using namespace std;

// Enum to represent the movement direction of the elevator
enum Direction { UP, DOWN, IDLE };

class Elevator {
  private:
    int id;                     // Unique ID for the elevator
    int currentFloor;           // Current floor the elevator is on
    Direction direction;        // Current movement direction of the elevator
    bool doorOpen;              // Whether the elevator door is open
    set<int> upRequests;
    set<int, greater<int>> downRequests;

    // Shared sound buffer to create multiple sound instances
    sf::SoundBuffer dingBuffer;

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

    // Get the current floor of the elevator.
    int getCurrentFloor() const;

  private:
    // Helper function to play ding sound
    void playDingSound();
};

#endif
