

#include "game/EntityView.h"
EntityView::~EntityView() = default;

void EntityView::render(sf::RenderWindow& window) {
    window.draw(m_shape);
}