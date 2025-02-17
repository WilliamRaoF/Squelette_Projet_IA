#ifndef BTENEMY_HPP
#define BTENEMY_HPP

#include "Player.hpp"
#include "BehaviorTree.h"

#include <cmath>

class BTEnemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    BTree behavior;

    BTEnemy(float x, float y);
    void update(float deltaTime, Grid& grid) override;
    void update(float deltaTime, Grid& grid, Player& player);
};

#endif // BTENEMY_HPP
