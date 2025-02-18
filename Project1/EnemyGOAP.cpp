#include "EnemyGOAP.h"

EnemyGOAP::EnemyGOAP(Player& p, Vector2f pos, float radiusDetect, int hp) : Enemy(pos, hp), player(p), detectionRadius(radiusDetect), isPatrolling(false), isHunting(false), isSearching(false), isFleeing(false) 
{
	detectionRadius = 100.0f;
	health = 100;
	position = pos;
}

void EnemyGOAP::patrol() {
    isPatrolling = true;
    isHunting = false;
    isSearching = false;
    isFleeing = false;
}

void EnemyGOAP::hunt() {
    isPatrolling = false;
    isHunting = true;
    isSearching = false;
    isFleeing = false;
}

void EnemyGOAP::search() {
    isPatrolling = false;
    isHunting = false;
    isSearching = true;
    isFleeing = false;
}

void EnemyGOAP::flee() {
    isPatrolling = false;
    isHunting = false;
    isSearching = false;
    isFleeing = true;
}

bool EnemyGOAP::getPatrolling() const {
    return isPatrolling;
}

bool EnemyGOAP::getHunting() const {
    return isHunting;
}

bool EnemyGOAP::getSearching() const {
    return isSearching;
}

bool EnemyGOAP::getFleeing() const {
    return isFleeing;
}

void EnemyGOAP::update(float deltaTime, Grid& grid, std::vector<Entity*> players)
{
}
