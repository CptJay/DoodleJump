#include "game/BonusView.h"
#include <logic/Bonus.h>

BonusView::BonusView(const Bonus* bonus) : m_bonus(bonus) {
    Logger::getInstance().log(LogLevel::INFO, "BonusView.cpp: Creating bonus view");

    // Check if bonus texture can be loaded
    if (!m_texture.loadFromFile("../assets/power_up.png")) {
        Logger::getInstance().log(LogLevel::ERROR, "BonusView.cpp: Failed to load bonus texture");
        m_shape.setSize({bonus->getWidth(), bonus->getHeight()});
        m_shape.setPosition(bonus->getX(), bonus->getY());
        m_shape.setFillColor(sf::Color::Red);
    } else {
        m_shape.setTexture(&m_texture, false);
        m_shape.setSize({static_cast<float>(m_texture.getSize().x), static_cast<float>(m_texture.getSize().y)});
        Logger::getInstance().log(LogLevel::INFO, "BonusView.cpp: Bonus texture loaded");
    }
}

void BonusView::update() {
    m_shape.setPosition(m_bonus->getX(), m_bonus->getY());
}