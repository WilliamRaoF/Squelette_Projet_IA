#ifndef BTENEMY_HPP
#define BTENEMY_HPP

#include "Player.hpp"
#include "BehaviorTree.h"

#include <cmath>

class BTEnemy : public Entity, public std::enable_shared_from_this<BTEnemy> {
public:
    static constexpr float SPEED = 150.0f;
    static constexpr float DETECTION_RADIUS = 200.0f; //temporary

    std::shared_ptr<BTree> behavior = nullptr;


    BTEnemy(float x, float y);
    void update(float deltaTime, Grid& grid) override;
    void update(float deltaTime, Grid& grid, Player& player);

    void initBTree(Grid& grid);
};

#endif // BTENEMY_HPP
