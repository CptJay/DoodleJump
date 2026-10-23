

#include "game/PlatformView.h"

#include <logic/Platform.h>
PlatformView::PlatformView(const Platform* platform) : m_platform(platform) {
    Logger::getInstance().log(LogLevel::INFO, "PlatformView.cpp: PlatformView created");
    m_shape.setSize({platform->getWidth(), platform->getHeight()});
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setOutlineThickness(1.0f);
    m_shape.setOutlineColor(sf::Color::Black);
}

void PlatformView::update() {
    // Logger::getInstance().log(LogLevel::INFO, "PlatformView.cpp: PlatformView, sync position");
    m_shape.setPosition(m_platform->getX(), m_platform->getY());

    // Logger::getInstance().log(LogLevel::INFO, "PlatformView.cpp: PlatformView, update color");
    switch (m_platform->getType()) {
    case Platform::Type::STATIC:
        m_shape.setFillColor(sf::Color::Green);
        break;
    case Platform::Type::HORIZONTAL:
        m_shape.setFillColor(sf::Color::Blue);
        break;
    case Platform::Type::VERTICAL:
        m_shape.setFillColor(sf::Color::Yellow);
        break;
    case Platform::Type::TEMPORARY:
        m_shape.setFillColor(sf::Color::White);
        break;
    default:
        break;
    }
}