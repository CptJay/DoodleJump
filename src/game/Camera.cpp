#include "game/Camera.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <cassert>
#include <game/BGTileView.h>
#include <game/BonusView.h>
#include <game/PlatformView.h>
#include <logic/BGTile.h>
#include <logic/Bonus.h>
#include <logic/Platform.h>
#include <logic/Player.h>
#include <logic/Random.h>
#include <utils/Logger.h>

void Camera::update(float deltaTime) {
    if (!m_player)
        return;

    // Get the player's current position
    float playerY = m_player->getY();

    // If the player has moved above the starting Y-position of the camera, adjust the view
    if (playerY < m_startY) {
        // Calculate the difference between the player's current position and the starting Y-position
        m_offsetY = m_startY - playerY;

        // Update the starting Y-position of the camera
        m_startY = playerY;

        // Move the view by the difference in Y-position
        m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y - m_offsetY);
    } else {
        // If the player has not moved above the starting Y-position, reset the offset
        m_offsetY = 0.f;
    }
}
void Camera::updateBGTiles(std::vector<std::unique_ptr<BG_Tile>>& bgTiles, std::vector<std::shared_ptr<BGTileView>>& bgTileViews) {
    if (bgTiles.empty())
        return;

    auto getSmallestY = [&bgTiles]() -> float {
        if (bgTiles.empty()) {
            Logger::getInstance().log(LogLevel::ERROR, "Camera.cpp: BG tiles vector is empty");
            return 0.f;
        }

        float smallestY = bgTiles[0]->getY(); // Initialize with the first tile's Y value
        for (const auto& tile : bgTiles) {
            if (tile->getY() < smallestY) {
                smallestY = tile->getY();
            }
        }
        return smallestY;
    };

    float smallestY = getSmallestY();
    float height = bgTiles[0]->getHeight();

    for (size_t i = 0; i < bgTiles.size(); ++i) {
        bgTiles[i]->setY(bgTiles[i]->getY() + m_offsetY);
        bgTileViews[i]->update();

        // Recycle BG tiles
        if (bgTiles[i]->getY() > getViewBottom()) {
            // Align the BG tile to the tiles on the ultimate top
            // bgTiles[i]->setY(smallestY - height);
            bgTiles[i]->setY(bgTiles[i]->getY() - (getViewHeight() + height));
            bgTileViews[i]->update();

            Logger::getInstance().log(LogLevel::DEBUG, "Camera.cpp: BG tile recycled");
            Logger::getInstance().log(LogLevel::DEBUG, "Camera.cpp: BG tile Y: " + Logger::toString(bgTiles[i]->getY()));
            Logger::getInstance().log(LogLevel::DEBUG, "Camera.cpp: Smallest Y: " + Logger::toString(smallestY));
        }
    }
}

void Camera::updatePlatforms(float deltaTime, std::vector<std::unique_ptr<Platform>>& platforms,
                             std::vector<std::shared_ptr<PlatformView>>& platformViews) {

    if (platforms.empty())
        return;

    // if (m_offsetY == 0.f)
    //     return;

    for (size_t i = 0; i < platforms.size(); ++i) {
        // Offset the Y-position of the platform
        platforms[i]->setY(platforms[i]->getY() + m_offsetY);
        platforms[i]->update(deltaTime);
        platformViews[i]->update();

        // Recycle the platform if it has moved off the screen
        if (platforms[i]->getY() > getViewBottom()) {
            platforms[i]->setX(
                Random::getInstance().getRandomValue<float>(0, getViewRight() - platforms[i]->getWidth()));
            platforms[i]->setY(Random::getInstance().getRandomValue<float>(getViewTop() - 300, getViewTop() - 100));
        }
    }
}

void Camera::updateBonuses(float deltaTime, std::vector<std::unique_ptr<Bonus>>& bonuses,
                           std::vector<std::shared_ptr<BonusView>>& bonusViews) {
    if (bonuses.empty())
        return;

    for (size_t i = 0; i < bonuses.size(); ++i) {
        // Offset the Y-position of the bonus
        bonuses[i]->setY(bonuses[i]->getY() + m_offsetY);
        bonusViews[i]->update();

        // Recycle the bonus if it has moved off the screen
        if (bonuses[i]->getY() > getViewBottom()) {
            bonuses[i]->setX(Random::getInstance().getRandomValue<float>(0, getViewRight() - bonuses[i]->getWidth()));
            bonuses[i]->setY(Random::getInstance().getRandomValue<float>(getViewTop() - 5000, getViewTop() - 100));
        }
    }

}

void Camera::updateScoreText(sf::Text& scoreText, int score) {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(getViewLeft() + 10, getViewTop() + 10);
}

void Camera::shake(float deltaTime, float duration, float magnitude) {
    if (duration <= 0.f || magnitude <= 0.f)
        return;

    // Calculate the shake offset
    float offsetX = Random::getInstance().getRandomValue<float>(-magnitude, magnitude);
    float offsetY = Random::getInstance().getRandomValue<float>(-magnitude, magnitude);

    // Apply the shake offset to the view
    m_view.move(offsetX, offsetY);

    // Reduce the duration of the shake
    duration -= deltaTime;

    // Reset the view to its original position after the shake duration has elapsed
    if (duration <= 0.f) {
        m_view.setCenter(m_view.getSize().x / 2, m_view.getSize().y / 2);
    }
}