#include "logic/EntityModel.h"

void Subject::attach(const Observer& observer) {
    Logger::getInstance().log(LogLevel::INFO, "EntityModel.cpp:4 Attaching observer");
    m_observers.emplace_back(observer);
}

void Subject::notify() const {
    for (const auto& observer : m_observers) {
        observer();
    }
}