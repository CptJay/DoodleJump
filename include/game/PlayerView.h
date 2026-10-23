

#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include "EntityView.h"

/**
 * Forward declarations
 */
class Player;

/**
 * @class PlayerView
 * @brief Represents the view for a Player
 */
class PlayerView : public EntityView {
public:
    explicit PlayerView(const Player* player);

    /**
     * @brief Updates the view of the player
     */
    void update() override;

    /**
     * @brief Changes the player texture to the left
     */
    void left();

    /**
     * @brief Changes the player texture to the right
     */
    void right();

private:
    const Player* m_player;            // Pointer to the logic entity
    bool m_textureLeftLoaded = false;  // Texture for the player facing left
    sf::Texture m_textureLeft;         // Texture for the player facing left
    bool m_textureRightLoaded = false; // Texture for the player facing right
    sf::Texture m_textureRight;        // Texture for the player facing right
};

#endif // PLAYERVIEW_H
