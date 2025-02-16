#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <iostream>

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Entity(sf::Vector2f pos , sf::Color color);
    virtual void update(float deltaTime, Grid& grid) = 0;
    sf::RectangleShape getshape();
};

#endif // ENTITY_HPP