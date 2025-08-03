# Project 1: Elevator Simulator

## Overview
This is a project to simulate elevator system in a multi-storey building. The project helps to visualize the elevator movement simulation. It helps to handle floor request, door opening or closing.

**Features:**
- Change elevator number and floor number.
- Allocate floor requests by elevator location.
- Display elevator status (floor, door open/close status, and navigation).
- Delay door open/close
- Control panel interface

**Code Structure:**
- main.cpp: Main simulation loop, user input handling.
- building.cpp/h: Manages multiple elevators and request distribution
- elevator.cpp/h: Single elevator movement and request processing.
- logger.cpp/h: Logging utility for recording events

---

## Build and Run

### Prerequisites:
- g++ compiler supporting C++23
- Make utility

### How to compile and run

Open terminal and run:

```bash
make run
```
OR

```bash
g++ -std=c++23 main.cpp building.cpp elevator.cpp logger.cpp -o ./build/elevator_simulator

./build/elevator_simulator
```

---
## Team Collaboration & Contribution Doc

| Member Name         | Role                         | Contributions                                              |
|---------------------|------------------------------|------------------------------------------------------------|
| Dinh Nguyen Cam Tu   | Team Leader, Developer, Tester, Documenter | Designed classes Building and Elevator, implemented main logic, added logging, prepared README, wrote test cases, conducted testing and debugging |

