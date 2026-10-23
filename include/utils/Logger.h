#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <mutex> // For thread-safety in multithreaded environments
#include <string>

/**
 * @brief Log levels for the logger
 */
enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

/**
 * @class Logger
 * @brief A logger (singleton) class for logging messages to the console and optionally to a file
 */
class Logger {
public:
    /**
     * @brief Deleted copy constructor and assignment operator to prevent copying the singleton
     */
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    /**
     * @brief Get the singleton instance of the logger
     * @return The logger instance
     */
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    /**
     * @brief Log a message with the specified log level
     * @param level The log level
     * @param message The message to log
     */
    void log(LogLevel level, const std::string& message);

    /**
     * @brief Enable logging to a file
     * @param filename The name of the log file
     */
    void enableFileLogging(const std::string& filename = ".log");

    /**
     * @brief Disable logging to a file
     */
    void disableFileLogging();

    /**
     * @brief Set the minimum log level to log to file
     * @param level The minimum log level
     */
    template <typename T>
    static std::string toString(const T& value) {
        return std::to_string(value);
    }

private:
    Logger(); // Private constructor for singleton

    std::mutex m_logMutex; // Mutex for thread-safety

    std::ofstream m_logFile;       // Log file stream
    LogLevel m_minLogLevel;        // Minimum log level to log to file
    bool m_loggingEnabled = false; // Flag to check if logging to file is enabled

    static std::string logLevelToString(LogLevel level); // Convert log level to string
};

#endif // LOGGER_H
