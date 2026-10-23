

#include "game/BGTileView.h"

#include <logic/BGTile.h>
BGTileView::BGTileView(const BG_Tile* bgTile) : m_bgTile(bgTile) {
    m_shape.setSize({bgTile->getWidth(), bgTile->getHeight()});
    m_shape.setPosition({bgTile->getX(), bgTile->getY()});
    // (255, 255, 224) = Beige
    m_shape.setFillColor(sf::Color(255, 255, 224));
}

void BGTileView::update() {
    m_shape.setPosition({m_bgTile->getX(), m_bgTile->getY()});
    m_shape.setSize({m_bgTile->getWidth(), m_bgTile->getHeight()});
}
void BGTileView::render(sf::RenderWindow& window) {
    m_shape.setOutlineThickness(1.5f);
    m_shape.setOutlineColor(sf::Color::Black);
    EntityView::render(window);
}