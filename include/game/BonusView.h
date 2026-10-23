

#ifndef BONUSVIEW_H
#define BONUSVIEW_H
#include "EntityView.h"

/**
 * Forward declarations
 */
class Bonus;

/**
 * @class BonusView
 * @brief Represents the view for a Bonus
 */
class BonusView : public EntityView {
public:
    explicit BonusView(const Bonus* bonus);

    /**
     * @brief Updates the view
     */
    void update() override;

    /**
     * @brief Renders the view
     * @param window The window to render to
     */
    void render(sf::RenderWindow& window) override {
        // Draw the Bonus
        window.draw(m_shape);
    }

private:
    const Bonus* m_bonus;  // Pointer to the logic model
    sf::Texture m_texture; // Texture for the Bonus
};

#endif // BONUSVIEW_H
