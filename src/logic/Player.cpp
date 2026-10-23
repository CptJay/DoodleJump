

#include "logic/Player.h"

#include <logic/Platform.h>
Player::Player(float x, float y, float width, float height, float jumpForce, ObjType type)
    : EntityModel(x, y, width, height, type), m_jumpForce(jumpForce), m_velocityX(0.0f), m_velocityY(50.0f), m_gravity(-9.8f),
      m_isJumping(true) {}

void Player::update(float deltaTime) {
    deltaTime *= 5;

    // Doodle jump player logic, keep in mind that the y-axis is inverted in SFML
    m_velocityY += m_gravity * deltaTime;
    m_y -= m_velocityY * deltaTime;
    m_x += m_velocityX * deltaTime;

    // If, the player is about to jump, apply the jump force
    if (m_isJumping) {
        m_velocityY = m_jumpForce;
        m_isJumping = false;
    }

    // if player is touching the wall, teleport to the other side
    if (m_x <= 0) {
        m_x = 600 - m_width - 1;
    } else if (m_x >= 600 - m_width) {
        m_x = 0;
    }

    // Logger::getInstance().log(LogLevel::DEBUG, "Player velocity x: " + std::to_string(m_velocityX) + " y: " + std::to_string(m_velocityY));
    // Logger::getInstance().log(LogLevel::DEBUG, "Player x: " + std::to_string(m_x) + " y: " + std::to_string(m_y));
}
void Player::interact(EntityModel& other, Score* score) {
    // Collision detection platform
    if (other.getObjType() == EntityModel::ObjType::PLATFORM) {
        // Check if the player collides with the platform
        auto platform = dynamic_cast<Platform*>(&other);
        if (m_x < other.getX() + other.getWidth() && m_x + m_width > other.getX() && m_y < other.getY() + other.getHeight() &&
            m_y + m_height > other.getY() && m_velocityY < 0) {
            Logger::getInstance().log(LogLevel::DEBUG, "Player collided with a platform");
            // Activate the jump
            m_isJumping = true;
            m_jumpForce = 90;
            // slow down the jump force if the player is too fast
            if (m_jumpForce > 100) {
                m_jumpForce -= 25;
            }
            // Increase the score
            score->increaseScore(50);

            if (platform->getType() == Platform::Type::TEMPORARY) {
                // Remove the platform
                other.setY(platform->getY() - 3000);
            }
        }
    }

    // Collision detection bonus
    if (other.getObjType() == EntityModel::ObjType::BONUS) {
        // Check if the player collides with the bonus
        if (m_x < other.getX() + other.getWidth() && m_x + m_width > other.getX() && m_y < other.getY() + other.getHeight() &&
            m_y + m_height > other.getY()) {
            Logger::getInstance().log(LogLevel::DEBUG, "Player collided with a bonus");
            // Activate the jump and increase the jump force
            m_isJumping = true;
            m_jumpForce = 250;
            // Increase the score
            score->increaseScore(5000);
        }
    }
}

void Player::moveLeft() { m_velocityX = -100.0f; }

void Player::moveRight() { m_velocityX = 100.0f; }

void Player::stopMovement() { m_velocityX = 0.0f; }
