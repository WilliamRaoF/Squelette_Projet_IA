#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);

    void setPath(std::vector<sf::Vector2i> newPath);

    void update(float deltaTime, Grid& grid) override;
    enum State { PATROL, CHASE, SEARCH };
    State currentState;
private:

    sf::Vector2i gridPosition;
    std::vector<sf::Vector2i> path;
    int currentIndexPath = 0;
};

#endif // ENEMY_HPP