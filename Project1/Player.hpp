#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
public:
    static constexpr float SPEED = 200.0f;
    sf::Vector2f playerPos;

    Player(sf::Vector2f pos);

    void update(float deltaTime, Grid& grid) override;
    sf::Vector2f getpos() { return shape.getPosition(); }
};

#endif // PLAYER_HPP