#include "logic/Score.h"
#include <logic/Player.h>

Score::Score(Player* player) : m_score(0), m_player(player) {
    m_highestY = static_cast<int>(m_player->getY());
}

Score::~Score() {}

void Score::update() {
    if (static_cast<int>(m_player->getY()) < m_highestY) {
        m_highestY = static_cast<int>(m_player->getY());
        m_score += 10;
    }
}