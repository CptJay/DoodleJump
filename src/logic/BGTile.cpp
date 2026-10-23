

#include "logic/BGTile.h"
void BG_Tile::update(float deltaTime) {
    // Update the position of the background tile
    m_y += m_scrollSpeed * deltaTime;
}