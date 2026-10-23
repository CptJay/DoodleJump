

#include "utils/Logger.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <sstream>

void Logger::log(LogLevel level, const std::string& message) {
    // Check if the log level is high enough to be logged
    if (level < m_minLogLevel || !m_loggingEnabled) {
        return;
    }

    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    // Format the log message
    std::stringstream logMessage;
    logMessage << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << " [" << logLevelToString(level) << "]: " << message
               << std::endl;

    // Output to console
    std::cout << logMessage.str();

    // Output to file if enabled
    if (m_logFile.is_open()) {
        std::lock_guard<std::mutex> lock(m_logMutex);
        m_logFile << logMessage.str();
    }
}
void Logger::enableFileLogging(const std::string& filename) {
    if (!m_loggingEnabled) {
        return;
    }

    // Check if directory exists in root, if not create it
    if (!std::filesystem::exists("../logs")) {
        std::filesystem::create_directory("../logs");
        getInstance().log(LogLevel::INFO, "Created logs directory");
    }

    // If the file already exists, clear it
    if (std::filesystem::exists("../logs/" + filename)) {
        std::ofstream file("../logs/" + filename, std::ios::out | std::ios::trunc);
        file.close();
    }

    // open file in directory: logs/filename
    m_logFile.open("../logs/" + filename, std::ios::out | std::ios::app);
    if (!m_logFile.is_open()) {
        getInstance().log(LogLevel::ERROR, "Failed to open log file");
    }
}

void Logger::disableFileLogging() {
    if (m_logFile.is_open()) {
        m_logFile.close();
        getInstance().log(LogLevel::INFO, "Logger.cpp: Log file closed");
    }
}

Logger::Logger()
    : m_logFile(), m_logMutex(),
// In case of releasing the game and disable logging, you can set `m_loggingEnabled` to false.
#ifdef NDEBUG // Release mode
      m_minLogLevel(LogLevel::WARNING), m_loggingEnabled(true)
#else // Debug mode
      m_minLogLevel(LogLevel::DEBUG), m_loggingEnabled(true)
#endif
{
    enableFileLogging();
}

// Convert log level to string
std::string Logger::logLevelToString(const LogLevel level) {
    switch (level) {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}