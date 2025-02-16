#include "Enemy.hpp"
#include <cmath>

enum Enemy::State { PATROL, CHASE, SEARCH, PROTECT };
Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red), currentState(PATROL) {}

void Enemy::setPath(std::vector<sf::Vector2i> newPath)
{
	if (!newPath.empty()) {
		path = newPath;
		currentIndexPath = 0;
	}

}

void Enemy::setTarget(const sf::Vector2i& target)
{
    targetPosition = target;
}

void Enemy::detectPlayer(Grid& grid, const sf::Vector2i& playerPos)
{
    sf::Vector2i enemyPos = getGridPosition();

    int distance = std::abs(enemyPos.x - playerPos.x)+ std::abs(enemyPos.y - playerPos.y);

    if (distance < 4) {
        if (currentState != CHASE) {
            currentState = CHASE;
            setTarget(playerPos);
            path = Pathfinding::findPath(grid, enemyPos, playerPos);
            currentIndexPath = 0;
        }
    }
    else if (distance > 10 && currentState == CHASE) {
        if (currentState != SEARCH) {
            currentState = SEARCH;
        }
    }
}

void Enemy::update(float deltaTime, Grid& grid, sf::Vector2i& playerPos) {

    detectPlayer(grid, playerPos);

    switch (currentState) {
    case PATROL:
       patrol(deltaTime, grid);
      //  detectPlayer(grid, playerPos);
        break;
        //fonction de patrouille
         //if (/*fonction de détection du player*/) currentState = CHASE;
         //break;

    case CHASE:

        chase(grid, playerPos, deltaTime);
        //fonction de chase avec le pathfinding
         //if (!/*fonction de détection du player*/) {
         //    currentState = SEARCH;
         //}
        break;

    case SEARCH:
        break;
    
    case PROTECT: 
        break;
    
    default: 
        break;
    }
}

void Enemy::chase(Grid& grid, const sf::Vector2i& playerPos, float deltaTime)
{
    std::cout << "Player position chase : x :" << playerPos.x << "y :" << playerPos.y << std::endl;
   if (path.empty() || targetPosition != playerPos) {
        targetPosition = playerPos;
        path = Pathfinding::findPath(grid, getGridPosition(), playerPos);
        currentIndexPath = 0;
    }
    

    if (currentIndexPath < path.size()) {
        sf::Vector2f targetPos(path[currentIndexPath].x * CELL_SIZE, path[currentIndexPath].y * CELL_SIZE);
        sf::Vector2f direction = targetPos - shape.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0.1f) {
            direction /= length;
            sf::Vector2f newPosition = shape.getPosition() + (direction * SPEED * deltaTime);

            int gridX = newPosition.x / CELL_SIZE;
            int gridY = newPosition.y / CELL_SIZE;

            if (grid.getCell(gridY, gridX).walkable) {
                shape.setPosition(newPosition);
            }
        }
        else {
            shape.setPosition(targetPos);
            currentIndexPath++;
        }
    }
}

void Enemy::patrol(float deltaTime, Grid& grid)
{
    if (path.empty()) {
        path = { {2, 2}, {8, 2}, {8, 8}, {2, 8} };  
        currentIndexPath = 0;
    }

    if (currentIndexPath < path.size()) {
        sf::Vector2f targetPos(path[currentIndexPath].x * CELL_SIZE, path[currentIndexPath].y * CELL_SIZE);
        sf::Vector2f direction = targetPos - shape.getPosition();

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.1f) {
            direction /= length;
            shape.move(direction * SPEED * deltaTime);
        }
        else {
            shape.setPosition(targetPos); 
            currentIndexPath++;
        }
    }
    else {
 
        currentIndexPath = (currentIndexPath + 1) % 4;
        targetPosition = path[currentIndexPath];
        path = Pathfinding::findPath(grid, getGridPosition(), targetPosition);
    }
}
