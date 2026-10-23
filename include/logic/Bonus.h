

#ifndef BONUS_H
#define BONUS_H
#include "EntityModel.h"
#include "Score.h"

/**
 * @class Bonus
 * @brief Represents a bonus entity
 */
class Bonus : public EntityModel {
public:
    Bonus(float x, float y, float width, float height, ObjType type = ObjType::BONUS)
        : EntityModel(x, y, width, height, type) {};

    virtual ~Bonus() = default;

    /**
     * @brief Updates the bonus
     * @param deltaTime Time elapsed since the last update
     */
    void update(float deltaTime) override;

    /**
     * @brief Interacts with another entity
     * @param other The other entity to interact with
     * @param score The score to update
     */
    void interact(EntityModel& other, Score* score) override;

    /**
     * @brief Sets the bonus value
     * @param value The value to set
     */
    void setValue(int value) { m_value = value; }

    /**
     * @brief Gets the bonus value
     * @return The value of the bonus
     */
    [[nodiscard]] int getValue() const { return m_value; }

private:
    int m_value; // Value of the bonus
};

#endif // BONUS_H
