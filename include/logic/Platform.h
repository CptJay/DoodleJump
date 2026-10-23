

#ifndef PLATFORM_H
#define PLATFORM_H
#include "EntityModel.h"
#include "Score.h"

/**
 * @class Platform
 * @brief Represents a platform entity
 */
class Platform : public EntityModel {
public:
    /**
     * @brief Platform types: STATIC, HORIZONTAL, VERTICAL, TEMPORARY
     */
    enum class Type { STATIC, HORIZONTAL, VERTICAL, TEMPORARY };

    /**
     * @brief Platform constructor
     */
    Platform(Type type, float x, float y, float width, float height, int points, ObjType objType = ObjType::PLATFORM);

    /**
     * @brief Virtual platform destructor
     */
    virtual ~Platform() = default;

    /**
     * @brief Update the platform
     */
    void update(float deltaTime) override {
        // Nothing to update
    }

    void interact(EntityModel& other, Score* score) override = 0;

    /**
     * @brief Get the type of the platform
     * @return type
     */
    [[nodiscard]] Type getType() const { return m_type; }

    /**
     * @brief Get the points of the platform
     * @return points
     */
    [[nodiscard]] int getPoints() const { return m_points; }

protected:
    Type m_type;  // Type of the platform
    int m_points; // Points of the platform
};

/**
 * @class StaticPlatform
 * @brief Represents a static platform entity
 */
class StaticPlatform : public Platform {
public:
    /**
     * @brief StaticPlatform constructor
     */
    StaticPlatform(float x, float y, float width, float height);

    /**
     * @brief StaticPlatform destructor
     */
    ~StaticPlatform() override = default;

    /**
     * @brief Update the platform
     */
    void update(float deltaTime) override {};

    /**
     * @brief Interact with another entity
     */
    void interact(EntityModel& other, Score* score) override {};
};

/**
 * @class HorizontalPlatform
 * @brief Represents a horizontal platform entity
 */
class HorizontalPlatform : public Platform {
public:
    /**
     * @brief HorizontalPlatform constructor
     */
    HorizontalPlatform(float x, float y, float width, float height, float speed = 100, float direction = 1);

    /**
     * @brief HorizontalPlatform destructor
     */
    ~HorizontalPlatform() override = default;

    /**
     * @brief Update the platform
     */
    void update(float deltaTime) override;

    /**
     * @brief Interact with another entity
     */
    void interact(EntityModel& other, Score* score) override {};

private:
    float m_speed;     // Speed of the platform
    float m_direction; // Direction of the platform
};

/**
 * @class VerticalPlatform
 * @brief Represents a vertical platform entity
 */
class VerticalPlatform : public Platform {
public:
    /**
     * @brief VerticalPlatform constructor
     */
    VerticalPlatform(float x, float y, float width, float height, float speed = 100, float direction = 1,
                     float range = 100);

    /**
     * @brief VerticalPlatform destructor
     */
    ~VerticalPlatform() override = default;

    /**
     * @brief Update the platform
     */
    void update(float deltaTime) override;

    /**
     * @brief Interact with another entity
     */
    void interact(EntityModel& other, Score* score) override {};

private:
    float m_speed;     // Speed of the platform
    float m_direction; // Direction of the platform
    float m_range;     // Range of the platform
};

/**
 * @class TemporaryPlatform
 * @brief Represents a temporary platform entity
 */
class TemporaryPlatform : public Platform {
public:
    /**
     * @brief TemporaryPlatform constructor
     */
    TemporaryPlatform(float x, float y, float width, float height);

    /**
     * @brief TemporaryPlatform destructor
     */
    ~TemporaryPlatform() override = default;

    /**
     * @brief Update the platform
     */
    void update(float deltaTime) override;

    /**
     * @brief Interact with another entity
     */
    void interact(EntityModel& other, Score* score) override {};
};

#endif // PLATFORM_H
