#include "Entity.hpp"

Entity::Entity(float x, float y, sf::Color color) {
    shape.setSize({ 35, 35 });
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

sf::Vector2i Entity::getGridPosition() const
{
    return sf::Vector2i(
        static_cast<int>(shape.getPosition().x / CELL_SIZE),
            static_cast<int>(shape.getPosition().y / CELL_SIZE) );
}
