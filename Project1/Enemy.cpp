#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y, int hp) : Entity(x, y, sf::Color::Red, hp) {}

void Enemy::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {
}


