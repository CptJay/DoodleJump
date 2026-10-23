

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "BGTile.h"
#include "Bonus.h"
#include "Platform.h"
#include "Player.h"
#include <memory>

/**
 * @class AbstractFactory
 * @brief Abstract Factory class
 */
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;

    /**
     * @brief Create object of type Player
     */
    virtual std::unique_ptr<Player> createPlayer(float x, float y, float width, float height, float jumpForce) = 0;

    /**
     * @brief Create a platform object of the specified type
     */
    virtual std::unique_ptr<Platform> createPlatform(Platform::Type type, float x, float y, float width,
                                                     float height) = 0;

    /**
     * @brief Create a BG tile object
     */
    virtual std::unique_ptr<BG_Tile> createBGTile(float x, float y, float width, float height) = 0;

    /**
     * @brief Create a bonus object
     */
    virtual std::unique_ptr<Bonus> createBonus(float x, float y, float width, float height) = 0;
};

#endif // ABSTRACTFACTORY_H
