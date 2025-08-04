/**
 * Name: Dinh Nguyen Cam Tu 🇻🇳
 * Professor: Kamran Eftekhari, Ph.D.
 * Class: Su25 CIS D002B 61Z Intermediate Programming Method C++
 * File: Logger.h
 * Purpose: Declares the Logger class which provides static methods 
 *          for logging messages with timestamps to a file. Supports 
 *          initializing the log file, writing log entries, and closing 
 *          the log file to release resources.
 * 
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
using namespace std;

/**
 * Logger class provides static methods to manage logging messages
 * to a file with timestamps. It handles initialization, writing logs,
 * and closing the log file.
 */
class Logger {
public:
    /**
     * Initialize the log file with the given filename.
     * Opens the file in append mode.
     * @param filename The name of the log file to open.
     */
    static void init(const string& filename);


    /**
     * Write a message to the log file with a timestamp.
     * Does nothing if the log file is not open.
     * @param message The log message to write.
     */
    static void log(const string& message);

    /**
     * Close the log file if it is open.
     * Frees any resources related to logging.
     */
    static void close();

private:
    static ofstream logFile;    // Static output file stream for logging
};

#endif
