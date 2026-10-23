

#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include "BGTileView.h"
#include "BonusView.h"
#include "PlatformView.h"
#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "logic/AbstractFactory.h"

#include <logic/BGTile.h>
// #include "BonusView.h"

/**
 * @class ConcreteFactory
 * @brief Concrete factory for creating game objects
 */
class ConcreteFactory : public AbstractFactory {
public:
    explicit ConcreteFactory(sf::RenderWindow& window) : m_window(window) {};

    /**
     * @brief Creates a player
     * @param x The x position of the player
     * @param y The y position of the player
     * @param width The width of the player
     * @param height The height of the player
     * @param jumpForce The jump force of the player
     * @return The player
     */
    std::unique_ptr<Player> createPlayer(float x, float y, float width, float height, float jumpForce) override {
        auto player = std::make_unique<Player>(x, y, width, height, jumpForce);

        // Attach SFML-specific rendering logic
        auto playerView = std::make_shared<PlayerView>(player.get());
        player->attach([this, playerView]() { playerView->render(m_window); });
        return player;
    }

    /**
     * @brief Creates a platform
     * @param type The type of the platform
     * @param x The x position of the platform
     * @param y The y position of the platform
     * @param width The width of the platform
     * @param height The height of the platform
     * @return The platform
     */
    std::unique_ptr<Platform> createPlatform(Platform::Type type, float x, float y, float width,
                                             float height) override {

        auto createCorrectPlatform = [&]() -> std::unique_ptr<Platform> {
            switch (type) {
            case Platform::Type::STATIC:
                return std::make_unique<StaticPlatform>(x, y, width, height);
            case Platform::Type::HORIZONTAL:
                return std::make_unique<HorizontalPlatform>(x, y, width, height);
            case Platform::Type::VERTICAL:
                return std::make_unique<VerticalPlatform>(x, y, width, height);
            case Platform::Type::TEMPORARY:
                return std::make_unique<TemporaryPlatform>(x, y, width, height);
            default:
                return std::make_unique<StaticPlatform>(x, y, width, height);
            }
        };

        auto platform = createCorrectPlatform();

        if (!platform) {
            return std::nullptr_t();
        }

        // Attach SFML-specific rendering logic
        auto platformView = std::make_shared<PlatformView>(platform.get());

        if (!platformView) {
            return std::nullptr_t();
        }

        platform->attach([this, platformView]() { platformView->render(m_window); });
        return platform;
    }

    /**
     * @brief Creates a background tile
     * @param x The x position of the tile
     * @param y The y position of the tile
     * @param width The width of the tile
     * @param height The height of the tile
     * @return The background tile
     */
    std::unique_ptr<BG_Tile> createBGTile(float x, float y, float width, float height) override {
        auto bgTile = std::make_unique<BG_Tile>(x, y, width, height);

        if (!bgTile) {
            return std::nullptr_t();
        }

        // Attach SFML-specific rendering logic
        auto bgTileView = std::make_shared<BGTileView>(bgTile.get());
        bgTile->attach([this, bgTileView]() { bgTileView->render(m_window); });
        return bgTile;
    }

    /**
     * @brief Creates a bonus
     * @param x The x position of the bonus
     * @param y The y position of the bonus
     * @param width The width of the bonus
     * @param height The height of the bonus
     * @return The bonus
     */
    std::unique_ptr<Bonus> createBonus(float x, float y, float width, float height) override {
        auto bonus = std::make_unique<Bonus>(x, y, width, height);

        if (!bonus) {
            return std::nullptr_t();
        }

        // Attach SFML-specific rendering logic
        auto bonusView = std::make_shared<BonusView>(bonus.get());
        bonus->attach([this, bonusView]() { bonusView->render(m_window); });
        return bonus;
    }

private:
    sf::RenderWindow& m_window; // Reference to the window
};

#endif // CONCRETEFACTORY_H
