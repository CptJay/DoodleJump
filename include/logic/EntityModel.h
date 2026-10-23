

#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include <functional>
#include <utils/Logger.h>
#include <vector>

/**
 * Forward declarations
 */
class Score;

/**
 * @class Subject
 * @brief Subject class for observer pattern
 */
class Subject {
public:
    using Observer = std::function<void()>;

    /**
     * @brief Attach an observer to the subject
     * @param observer
     */
    void attach(const Observer& observer);

    /**
     * @brief Notify all observers
     */
    void notify() const;

    /**
     * @brief Subject destructor
     */
    virtual ~Subject() = default;

private:
    std::vector<Observer> m_observers; // List of observers
};

class EntityModel : public Subject {
public:
    /**
     * @brief Enum class for object type
     */
    enum class ObjType {
        PLAYER,
        PLATFORM,
        BONUS,
        BGTile,
    };

    /**
     * @brief EntityModel constructor
     */
    EntityModel(float x, float y, float width, float height, ObjType type)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_ObjType(type) {};

    /**
     * @brief EntityModel destructor
     */
    virtual ~EntityModel() = default;

    /**
     * @brief Update the entity
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Interact with another entity
     */
    virtual void interact(EntityModel& other, Score* score) = 0;

    /**
     * @brief Get the x position of the entity
     * @return x position
     */
    [[nodiscard]] float getX() const { return m_x; }

    /**
     * @brief Get the y position of the entity
     * @return y position
     */
    [[nodiscard]] float getY() const { return m_y; }

    /**
     * @brief Get the width of the entity
     * @return width
     */
    [[nodiscard]] float getWidth() const { return m_width; }

    /**
     * @brief Get the height of the entity
     * @return height
     */
    [[nodiscard]] float getHeight() const { return m_height; }

    /**
     * @brief Set the x position of the entity
     * @param x
     */
    void setX(float x) { m_x = x; }

    /**
     * @brief Set the y position of the entity
     * @param y
     */
    void setY(float y) { m_y = y; }

    /**
     * @brief Set the width of the entity
     * @param width
     */
    void setWidth(float width) { m_width = width; }

    /**
     * @brief Set the height of the entity
     * @param height
     */
    void setHeight(float height) { m_height = height; }

    /**
     * @brief Get the type of the entity
     * @return type
     */
    [[nodiscard]]
    virtual ObjType getObjType() const {
        return m_ObjType;
    }

protected:
    float m_x;      // x position
    float m_y;      // y position
    float m_width;  // width
    float m_height; // height

    ObjType m_ObjType; // type of the entity
};

#endif // ENTITYMODEL_H
