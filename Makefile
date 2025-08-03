#Project name
PROJECT_NAME := "Project 1: Elevator Simulator"

#COLOR
RED          := $(shell tput -Txterm setaf 1)
GREEN        := $(shell tput -Txterm setaf 2)
YELLOW       := $(shell tput -Txterm setaf 3)
RESET 		   := $(shell tput -Txterm sgr0)
ALERT        := $(YELLOW)$(DATE)$(RESET)

# Run project
.PHONY: run
run:
	@echo "[$(ALERT) - make run -> $(GREEN)$(PROJECT_NAME)$(RESET)]"
	@g++ -std=c++23 main.cpp building.cpp elevator.cpp logger.cpp -o ./build/elevator_simulator && ./build/elevator_simulator