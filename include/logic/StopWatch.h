

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <utils/Logger.h>

using namespace std::chrono;

/**
 * @class StopWatch
 * @brief A stopwatch (singleton) class to measure elapsed time.
 */
class StopWatch {
public:
    /**
     * @brief Deleted copy constructor
     */
    StopWatch(const StopWatch&) = delete;
    StopWatch& operator=(const StopWatch&) = delete;

    /**
     * @brief Get the singleton instance of the stopwatch
     */
    static StopWatch& getInstance() {
        static StopWatch instance; // This creates the instance the first time it's needed
        return instance;
    }

    /**
     * @brief Start the stopwatch
     */
    void start() {
        if (isRunning) {
            Logger::getInstance().log(LogLevel::ERROR, "StopWatch.h: Stopwatch already running");
            return;
        }
        isRunning = true;
    }

    /**
     * @brief Stop the stopwatch
     */
    void stop() {
        if (!isRunning) {
            Logger::getInstance().log(LogLevel::ERROR, "StopWatch.h: Stopwatch not running");
            return;
        }
        Logger::getInstance().log(LogLevel::INFO, "StopWatch.h: Stopwatch stopped at " +
                                                      std::to_string(steady_clock::now().time_since_epoch().count()));
        isRunning = false;
    }

    /**
     * @brief Get the elapsed time
     * @return The elapsed time
     */
    float getElapsedTime() {
        if (!isRunning) {
            Logger::getInstance().log(LogLevel::ERROR, "StopWatch.h: Stopwatch not running");
            return 0;
        }
        time_point<steady_clock> currentFrameTime = steady_clock::now();
        const duration<float> deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime; // Update the last frame time
        return deltaTime.count();
    }

    /**
     * @brief Reset the stopwatch
     */
    void reset() {
        Logger::getInstance().log(LogLevel::INFO, "StopWatch.h: Stopwatch reset");
        lastFrameTime = steady_clock::now();
        isRunning = false;
    }

private:
    StopWatch() : lastFrameTime(steady_clock::now()) {} // Private constructor

    time_point<steady_clock> lastFrameTime; // Time of the last frame
    bool isRunning = false;                 // Flag to indicate if the stopwatch is running
};

#endif // STOPWATCH_H
