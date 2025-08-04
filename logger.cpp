/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: logger.cpp
 * Purpose: Implements the Logger class responsible for managing 
 *          logging messages to a file with timestamps. Provides 
 *          functions to initialize the log file, write log entries, 
 *          and properly close the file.
 * 
 */
#include "logger.h"
#include <iostream>
#include <ctime>

// Definition of the static variable to manage the log file
ofstream Logger::logFile;

/**
 * Initialize the log file with the given filename.
 * The file is opened in append mode (adds to the end if file exists).
 * If the file fails to open, an error message is printed to stderr.
 * @param filename The name of the log file to open.
 */
void Logger::init(const string& filename) {
    logFile.open(filename, ios::out | ios::app);
    if (!logFile.is_open()) {
        cerr << "Failed to open log file: " << filename << endl;
    }
}

/**
 * Write a log entry to the log file with the current timestamp.
 * If the log file is not open, the function does nothing.
 * @param message The message string to be logged.
 */
void Logger::log(const string& message) {
    if (logFile.is_open()) {
        time_t now = time(0);       // Get current time
        char* dt = ctime(&now);     // Convert to string format
        dt[strlen(dt) - 1] = '\0';  // remove newline
        logFile << "[" << dt << "] " << message << endl;  // Write log with timestamp
    }
}

/**
 * Close the log file if it is currently open.
 * Ensures resources are freed when the program ends.
 */
void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
