

#ifndef BGTILEVIEW_H
#define BGTILEVIEW_H
#include "EntityView.h"

/**
 * Forward declarations
 */
class BG_Tile;

/**
 * @class BGTileView
 * @brief Represents the view for a BG tile
 */
class BGTileView : public EntityView {
public:
    explicit BGTileView(const BG_Tile* bgTile);

    /**
     * @brief Updates the view
     */
    void update() override;

    /**
     * @brief Renders the view
     * @param window The window to render to
     */
    void render(sf::RenderWindow& window) override;

private:
    const BG_Tile* m_bgTile; // Pointer to the logic model
};

#endif // BGTILEVIEW_H
