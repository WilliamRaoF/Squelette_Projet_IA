#include "Entity.hpp"

Entity::Entity(sf::Vector2f pos, sf::Color color) {
    shape.setSize({ 35, 35 });
    shape.setPosition(pos);
    shape.setFillColor(color);
}

sf::RectangleShape Entity::getshape()
{
    return shape;
}
