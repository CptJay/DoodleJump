#ifndef GAME_H
#define GAME_H

#include "Camera.h"
#include "ConcreteFactory.h"
#include "Constants.h"
#include "PlatformView.h"
#include "PlayerView.h"
#include "SFML/Graphics.hpp"
#include "logic/Score.h"
#include <memory>

namespace DJGame {

/**
 * @class Game
 * @brief The main game class that handles the game loop.
 * Initializes the window, handles events, updates the game state, and renders the game.
 */
class Game {
public:
    explicit Game(const unsigned int& windowWidth = Constants::Screen::WIDTH,
                  const unsigned int& windowHeight = Constants::Screen::HEIGHT);
    ~Game();

    /**
     * @brief Runs the game loop
     */
    void run();

private:
    /**
     * @brief Handles events
     */
    void handleEvents();

    /**
     * @brief Updates the game state
     * @param deltaTime Time elapsed since the last update
     */
    void update(float deltaTime = 0.0f);

    /**
     * @brief Renders the game
     */
    void render();

    std::shared_ptr<sf::RenderWindow> m_window = nullptr; // The game window
    sf::View m_view = sf::View(
        sf::FloatRect(0, 0, Constants::Screen::WIDTH, Constants::Screen::HEIGHT)); // The view representing the camera
    std::unique_ptr<ConcreteFactory> m_factory = nullptr; // The factory for creating game objects
    std::unique_ptr<Camera> m_camera = nullptr;           // The camera that follows the player
    std::unique_ptr<Score> m_score = nullptr;             // The score
    sf::Text m_scoreText;                                 // The text for the score
    sf::Font m_font;                                      // The font for the score text

    // Game objects
    std::unique_ptr<PlayerView> m_playerView = nullptr;              // The player view
    std::shared_ptr<Player> m_player = nullptr;                      // The player model
    std::vector<std::shared_ptr<PlatformView>> m_platformViews = {}; // The platform views
    std::vector<std::unique_ptr<Platform>> m_platforms = {};         // The platforms
    std::vector<std::unique_ptr<BG_Tile>> m_bgTiles = {};            // The background tiles
    std::vector<std::shared_ptr<BGTileView>> m_bgTileViews = {};     // The background tile views
    std::vector<std::unique_ptr<Bonus>> m_bonuses = {};              // The bonuses
    std::vector<std::shared_ptr<BonusView>> m_bonusViews = {};       // The bonus views
};
} // namespace DJGame

#endif // GAME_H
