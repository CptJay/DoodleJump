

#include "game/PlayerView.h"

#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <logic/Player.h>
#include <logic/Random.h>
PlayerView::PlayerView(const Player* player) : m_player(player) {
    Logger::getInstance().log(LogLevel::INFO, "PlayerView.cpp: Creating player view");

    // Check if player texture can be loaded
    if (!m_textureRight.loadFromFile("../assets/player_right.png") || !m_textureLeft.loadFromFile("../assets/player_left.png")) {
        Logger::getInstance().log(LogLevel::ERROR, "PlayerView.cpp: Failed to load player texture");
        m_shape.setSize({player->getWidth(), player->getHeight()});
        m_shape.setFillColor(sf::Color::Red);
    } else {
        m_shape.setTexture(&m_textureRight, false);
        m_shape.setSize({static_cast<float>(m_textureRight.getSize().x), static_cast<float>(m_textureRight.getSize().y)});

        // Set bools to true
        m_textureRightLoaded = true;
        m_textureLeftLoaded = true;
        Logger::getInstance().log(LogLevel::INFO, "PlayerView.cpp: Player texture loaded");
    }

}

void PlayerView::update() {
    // if player is touching the wall then randomly change the color
    // TODO: Change to custom Random generator
    if (m_player->getX() <= 5 || m_player->getX() >= 800) {
        m_shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    }

    m_shape.setPosition(m_player->getX(), m_player->getY());
}
void PlayerView::left() {
    if (!m_textureLeftLoaded) {
        return;
    }

    m_shape.setTexture(&m_textureLeft, false);
}

void PlayerView::right() {
    if (!m_textureRightLoaded) {
        return;
    }

    m_shape.setTexture(&m_textureRight, false);
}