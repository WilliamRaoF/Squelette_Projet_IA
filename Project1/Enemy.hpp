#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

#include "Pathfinding.hpp"
#include <iostream>

class Enemy : public Entity {
public:

    enum State;
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);

    void setPath(std::vector<sf::Vector2i> newPath);
    void setTarget(const sf::Vector2i& target);
    void detectPlayer(Grid& grid, const sf::Vector2i& playerPos);
    void update(float deltaTime, Grid& grid) override;
   
   
private:
    State currentState;
    sf::Vector2i gridPosition;
    std::vector<sf::Vector2i> path;
    int currentIndexPath = 0;

    void patrol();
    void chase(Grid& grid, const sf::Vector2i playerPos);
    void moveAlongPath(float deltaTime);
};

#endif // ENEMY_HPP