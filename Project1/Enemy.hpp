#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Player.hpp"
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
    void update(float deltaTime, Grid& grid, sf::Vector2i& playerPos) override;
   
   
private:
    State currentState;
    sf::Vector2i gridPosition;
    std::vector<sf::Vector2i> path;
    int currentIndexPath = 0;
    sf::Vector2i targetPosition;

    void chase(Grid& grid, const sf::Vector2i& playerPos, float deltaTime);
    void patrol(float deltaTime, Grid& grid);
};

#endif // ENEMY_HPP