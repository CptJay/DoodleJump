#ifndef RANDOM_H
#define RANDOM_H

#include "utils/Logger.h"
#include <random>

/**
 * @class Random
 * @brief Singleton class for generating random numbers
 */
class Random {
public:
    /**
     * @brief Deleted copy constructor and assignment operator
     */
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    /**
     * @brief Get the instance of the Random class
     */
    static Random& getInstance() {
        static Random instance; // This creates the instance the first time it's needed
        return instance;
    }

    /**
     * @brief Get a random value between min and max.
     * Supported types: int, float
     * @tparam T The type of the value to generate
     * @param min The minimum value
     * @param max The maximum value
     */
    template <typename T = int>
    T getRandomValue(const T& min, const T& max) {
        if (min > max) {
            Logger::getInstance().log(LogLevel::ERROR, "Random.h: Random: min > max");
            return T(0);
        }

        if (std::is_same_v<T, int>) {
            Logger::getInstance().log(LogLevel::INFO, "Random.h: Random int value generated");
            std::uniform_int_distribution<int> dist(min, max);
            return dist(m_rng);
        }
        if (std::is_same_v<T, float>) {
            Logger::getInstance().log(LogLevel::INFO, "Random.h: Random float value generated");
            std::uniform_real_distribution<float> dist(min, max);
            return dist(m_rng);
        }
        Logger::getInstance().log(LogLevel::ERROR, "Random.h: unsupported type for getRandomValue");
        return T(0);
    }

private:
    Random() : m_rng(std::random_device{}()) {} // Constructor is private to prevent instantiation

    std::mt19937 m_rng; // Random number generator
};

#endif // RANDOM_H
