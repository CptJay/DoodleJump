

#ifndef BGTILE_H
#define BGTILE_H
#include "EntityModel.h"
#include "Score.h"

/**
 * @class BG_Tile
 * @brief Represents a background tile
 */
class BG_Tile : public EntityModel {
public:
    BG_Tile(float x, float y, float width, float height, ObjType obj = ObjType::BGTile)
        : EntityModel(x, y, width, height, obj), m_scrollSpeed(0.0f) {};

    virtual ~BG_Tile() = default;

    /**
     * @brief Updates the background tile
     * @param deltaTime Time elapsed since the last update
     */
    void update(float deltaTime) override;

    /**
     * @brief Interacts with another entity
     * @param other The other entity to interact with
     * @param score The score to update
     */
    void interact(EntityModel& other, Score* score) override {};

    /**
     * @brief Gets the scrolling speed of the tile
     * @return The scrolling speed
     */
    [[nodiscard]] float getScrollSpeed() const { return m_scrollSpeed; }

    /**
     * @brief Sets the scrolling speed of the tile
     * @param speed The scrolling speed
     */
    void setScrollSpeed(float speed) { m_scrollSpeed = speed; }

private:
    float m_scrollSpeed; // Scrolling speed of the tile
};

#endif // BGTILE_H
