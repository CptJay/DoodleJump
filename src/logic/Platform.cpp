#include "logic/Platform.h"

#include <game/Constants.h>

Platform::Platform(Type type, float x, float y, float width, float height, int points, ObjType objType)
    : EntityModel(x, y, width, height, objType), m_type(type), m_points(points) {
    Logger::getInstance().log(LogLevel::INFO, "Platform.cpp:5 Platform created");
}

StaticPlatform::StaticPlatform(float x, float y, float width, float height)
    : Platform(Type::STATIC, x, y, width, height, 10) {}

HorizontalPlatform::HorizontalPlatform(float x, float y, float width, float height, float speed, float direction)
    : Platform(Type::HORIZONTAL, x, y, width, height, 20), m_speed(speed), m_direction(direction) {}

void HorizontalPlatform::update(float deltaTime) {
    Platform::update(deltaTime);
    m_x += m_speed * deltaTime * m_direction;

    // If the platform reaches the window's edge, change direction
    if (m_x <= 0 || m_x + m_width >= DJGame::Constants::Screen::WIDTH) {
        m_direction *= -1;
    }
}

VerticalPlatform::VerticalPlatform(float x, float y, float width, float height, float speed, float direction, float range)
    : Platform(Type::VERTICAL, x, y, width, height, 30), m_speed(speed), m_direction(direction), m_range(range) {}

void VerticalPlatform::update(float deltaTime) {
    Platform::update(deltaTime);
    m_y += m_speed * deltaTime * m_direction;
    m_range -= m_speed * deltaTime * m_direction;

    // Use the range to move the platform up and down, not the platform's height
    if (m_range <= 0 || m_range >= 200) {
        m_direction *= -1;
        m_range = 100;
    }

}

TemporaryPlatform::TemporaryPlatform(float x, float y, float width, float height)
    : Platform(Type::TEMPORARY, x, y, width, height, 40) {}

void TemporaryPlatform::update(float deltaTime) {
    Platform::update(deltaTime);
}
