

#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <logic/Observer.h>

/**
 * @class EntityView
 * @brief Represents the view for an entity
 */
class EntityView : public Observer {
public:
    virtual ~EntityView();

    virtual void update() override = 0;

    virtual void render(sf::RenderWindow& window);

protected:
    sf::RectangleShape m_shape;
};

#endif // ENTITYVIEW_H
