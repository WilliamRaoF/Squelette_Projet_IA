#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"


class Player : public Entity {
public:
    float SPEED = 150.f;
    //void update(float deltaTime, Grid& grid) override;
    static constexpr int DAMAGE = 20;
    static constexpr float ATTACK_COOLDOWN = 0.5f;
    float attackTimer;

    Player(float x, float y, int hp);
    void attack(std::vector<Entity*> enemies);
    void update(float deltaTime, Grid& grid, std::vector<Entity*> enemies) override;
};

#endif // PLAYER_HPP