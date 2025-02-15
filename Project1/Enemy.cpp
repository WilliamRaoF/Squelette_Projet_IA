#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red) {}

void Enemy::setPath(std::vector<sf::Vector2i> newPath)
{
	if (!newPath.empty()) {
		path = newPath;
		currentIndexPath;
	}
}

void Enemy::update(float deltaTime, Grid& grid) {
	if (currentIndexPath >= path.size())
		return;
    switch (currentState) {
    case PATROL:
       //fonction de patrouille
        //if (/*fonction de détection du player*/) currentState = CHASE;
        //break;

    case CHASE:
       //fonction de chase avec le pathfinding
        //if (!/*fonction de détection du player*/) {
        //    currentState = SEARCH;
        //}
        break;

    case SEARCH:
        break;
    }


}
