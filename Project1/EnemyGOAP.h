#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Entity.hpp"
#include "Enemy.hpp"

class EnemyGOAP : public Enemy {
private:
    bool isPatrolling;
    bool isHunting;
    bool isSearching;
    bool isFleeing;

public:
    Player& player;
    float detectionRadius;
    int health;
    Vector2f position;

    EnemyGOAP(Player& p, Vector2f pos, float radius, int hp);

    void patrol();
    void hunt();
    void search();
    void flee();

    bool getPatrolling() const;
    bool getHunting() const;
    bool getSearching() const;
    bool getFleeing() const;

    void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;

    int GetHealth() const { return health; }
    Vector2f getPos() const { return position; }
};