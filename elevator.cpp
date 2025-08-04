#include "elevator.h"
#include "logger.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

const string SOUND_DIRECTORY = "sounds/ding.mp3"; // Sound directory

// Constructor initializes the elevator's ID and sets initial state.
Elevator::Elevator(int id) 
  : id(id), currentFloor(0), direction(IDLE), doorOpen(false)
{
    Logger::log("Elevator " + to_string(id) + " initialized at floor 0.");

    // Open sound file
    if (!dingBuffer.loadFromFile(SOUND_DIRECTORY)) {
        Logger::log("Failed to load ding sound for Elevator " + to_string(id));
    }
}
  
// Add a floor request to the elevator's request queue.
void Elevator::addRequest(int floor) {
    if (floor == currentFloor) {
        doorOpen = true;
        cout << "Elevator " << id << " opening doors at floor " 
             << floor << endl;
        Logger::log("Elevator " + to_string(id) + 
                    " instantly opened doors at floor " + to_string(floor));

        // Make a ding sound when opening the door
        playDingSound();

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

            // Phát âm thanh ding khi thang máy mở cửa
            playDingSound();

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

            // Phát âm thanh ding khi thang máy mở cửa
            playDingSound();

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

// Helper to play ding sound with a separate instance
void Elevator::playDingSound() {
    if (dingBuffer.getSampleCount() > 0) {
        auto sound = make_unique<sf::Sound>(dingBuffer);
        sound->setVolume(100.f);
        sound->play();
        Logger::log("Playing ding sound for Elevator " + to_string(id));

        // Detached thread giữ sound sống đủ lâu để phát hết
        thread([s = std::move(sound)]() mutable {
            this_thread::sleep_for(chrono::seconds(2));
        }).detach();
    }
}

