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
