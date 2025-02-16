#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y, int hp);
    void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
};

#endif // ENEMY_HPP