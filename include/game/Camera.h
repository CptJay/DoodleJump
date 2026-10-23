

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <memory>

/**
 * Forward declarations
 */
class BonusView;
class Bonus;
class PlatformView;
class BGTileView;
class Platform;
class BG_Tile;
class Player;

namespace sf {
class Text;
class View;
} // namespace sf

/**
 * @class Camera
 * @brief Represents the camera that follows the player
 */
class Camera {
public:
    /**
     * @brief Constructor
     * @param window The game window
     * @param playerModel The player model to track
     * @param view The view representing the camera
     */
    Camera(const sf::RenderWindow& window, std::shared_ptr<Player> playerModel, sf::View& view)
        : m_targetWindow(window), m_player(playerModel), m_view(view), m_startY(200.f), m_offsetY(0.f) {}

    /**
     * @brief Updates the camera
     * @param deltaTime Time elapsed since the last update
     */
    void update(float deltaTime);

    /**
     * @brief Updates the BG tiles
     * @param bgTiles The BG tiles to update
     * @param bgTileViews The BG tile views to update
     */
    void updateBGTiles(std::vector<std::unique_ptr<BG_Tile>>& bgTiles,
                       std::vector<std::shared_ptr<BGTileView>>& bgTileViews);

    /**
     * @brief Updates the platforms
     * @param deltaTime Time elapsed since the last update
     * @param platforms The platforms to update
     * @param platformViews The platform views to update
     */
    void updatePlatforms(float deltaTime, std::vector<std::unique_ptr<Platform>>& platforms,
                         std::vector<std::shared_ptr<PlatformView>>& platformViews);

    /**
     * @brief Updates the bonuses
     * @param deltaTime Time elapsed since the last update
     * @param bonuses The bonuses to update
     * @param bonusViews The bonus views to update
     */
    void updateBonuses(float deltaTime, std::vector<std::unique_ptr<Bonus>>& bonuses,
                       std::vector<std::shared_ptr<BonusView>>& bonusViews);

    /**
     * @brief Updates the score text
     * @param scoreText The score text to update
     * @param score The score to display
     */
    void updateScoreText(sf::Text& scoreText, int score);

    /**
     * @brief Applies the camera view to the window
     * @param window The window to apply the view to
     */
    void apply(sf::RenderWindow& window) { window.setView(m_view); }

    /**
     * @brief Shakes the camera - TODO: Method not working as intended, fix it
     * @param deltaTime Time elapsed since the last update
     * @param duration The duration of the shake effect
     * @param magnitude The magnitude of the shake effect
     */
    void shake(float deltaTime, float duration = 2, float magnitude = 10);

    /**
     * @brief Resets the camera
     */
    void reset() {
        m_startY = 0.f;
        m_view.setCenter(m_view.getSize().x / 2, m_view.getSize().y / 2);
    }

    /**
     * @brief Gets the top position of the camera view
     */
    [[nodiscard]] float getViewTop() const { return m_view.getCenter().y - m_view.getSize().y / 2; }

    /**
     * @brief Gets the height of the camera view
     */
    [[nodiscard]] float getViewHeight() const { return m_view.getSize().y; }

    /**
     * @brief Gets the bottom position of the camera view
     */
    [[nodiscard]] float getViewBottom() const { return m_view.getCenter().y + m_view.getSize().y / 2; }

    /**
     * @brief Gets the left position of the camera view
     */
    [[nodiscard]] float getViewLeft() const { return m_view.getCenter().x - m_view.getSize().x / 2; }

    /**
     * @brief Gets the width of the camera view
     */
    [[nodiscard]] float getViewWidth() const { return m_view.getSize().x; }

    /**
     * @brief Gets the right position of the camera view
     */
    [[nodiscard]] float getViewRight() const { return m_view.getCenter().x + m_view.getSize().x / 2; }

private:
    sf::View& m_view;                       // The view representing the camera
    const sf::RenderWindow& m_targetWindow; // Reference to the game window
    std::shared_ptr<Player> m_player;       // The player model to track
    float m_startY;                         // Initial Y-position of the camera
    float m_offsetY;                        // Offset to adjust the camera

    // Shake variables
    float m_shakeDuration = 0.f;  // Duration of the shake effect
    float m_shakeMagnitude = 0.f; // Magnitude of the shake effect
    float m_originalX = 0.f;      // Original X-position of the camera
    float m_originalY = 0.f;      // Original Y-position of the camera
};

#endif // CAMERA_H
