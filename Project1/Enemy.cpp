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

    int distance = std::abs(enemyPos.x - playerPos.x) + std::abs(enemyPos.y - playerPos.y);

    if (distance < 4 && !currentState == CHASE) {
            currentState = CHASE;
            setTarget(playerPos);
            setPath(Pathfinding::findPath(grid, enemyPos, playerPos));
            shape.setFillColor(sf::Color::Magenta);

    }
    else if (distance > 10 && currentState == CHASE) {
        currentState = SEARCH;
        shape.setFillColor(sf::Color::Red);
        
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

void Enemy::moveAlongPath(float deltaTime, Grid& grid)
{
    if (currentIndexPath < path.size()) {

        sf::Vector2i nextCell = path[currentIndexPath];
        sf::Vector2f nextPosition = sf::Vector2f(nextCell.x * CELL_SIZE, nextCell.y * CELL_SIZE);

        sf::Vector2f direction = nextPosition - shape.getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 0.1f) {
            direction /= distance;
            shape.setPosition(shape.getPosition() + direction * SPEED * deltaTime);
        } 
        if (distance < SPEED * deltaTime) {
            shape.setPosition(nextPosition);
            currentIndexPath++;
        }
    }
}

void Enemy::chase(Grid& grid, const sf::Vector2i& playerPos, float deltaTime)
{
   
    int dx = std::abs(playerPos.x - lastKnownPlayerPos.x);
    int dy = std::abs(playerPos.y - lastKnownPlayerPos.y);

    if (dx > 1 || dy > 1) {  
        lastKnownPlayerPos = playerPos;
        setPath(Pathfinding::findPath(grid, getGridPosition(), playerPos));  
    }

    moveAlongPath(deltaTime, grid);

}

void Enemy::patrol(float deltaTime, Grid& grid)
{
    static std::vector<sf::Vector2i> patrolPoints = { {2,2}, {8,2}, {8,8}, {20,13} };

    if (path.empty()) {
        targetPosition = patrolPoints[currentIndexPath];
        setPath(Pathfinding::findPath(grid, getGridPosition(), targetPosition));  
    }

    moveAlongPath(deltaTime, grid);

    if (currentIndexPath >= path.size()) {
        currentIndexPath = (currentIndexPath + 1) % patrolPoints.size();
        targetPosition = patrolPoints[currentIndexPath];
        setPath(Pathfinding::findPath(grid, getGridPosition(), targetPosition));  
    }
}

void Enemy::search(float deltaTime, Grid& grid)
{

}
