#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Enemy.hpp"
#include "BTEnemy.h"
#include "Grid.hpp"

#include <vector>
#include <ctime>


const int WINDOW_WIDTH = 1480;
const int WINDOW_HEIGHT = 880;

int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Grid grid;
    grid.loadFromFile("map.txt");

    Player player(200, 400);
    player.shape.setOrigin(player.shape.getSize() / 2.f);

    std::vector<Enemy> enemies = { Enemy(100, 100), Enemy(700, 100) };

    //*BEHAVIOR TREE ENEMY*\\ 
    std::vector<std::shared_ptr<BTEnemy>> btenemies;
    auto btEnemy = std::make_shared<BTEnemy>(200, 200);
    btEnemy->initBTree(grid);
    btenemies.push_back(btEnemy);

    sf::CircleShape radius(btEnemy->DETECTION_RADIUS);
    radius.setOutlineColor(sf::Color::Green);
    radius.setOutlineThickness(2);
    radius.setFillColor(sf::Color(0,255,0,15));
    radius.setOrigin(btEnemy->DETECTION_RADIUS, btEnemy->DETECTION_RADIUS);

    sf::CircleShape radiusVision(btEnemy->VISION_RADIUS);
    radiusVision.setOutlineColor(sf::Color::Red);
    radiusVision.setOutlineThickness(2);
    radiusVision.setFillColor(sf::Color(255, 0, 0, 15));
    radiusVision.setOrigin(btEnemy->VISION_RADIUS, btEnemy->VISION_RADIUS);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid);
        }
        for (auto& btenemy : btenemies) {
            btenemy->update(deltaTime, grid, player);
        }

        window.clear();

        radius.setPosition(btEnemy->shape.getPosition());
        radiusVision.setPosition(btEnemy->shape.getPosition());

        grid.draw(window);
        window.draw(radius);
        window.draw(radiusVision);
        window.draw(player.shape);

        for (const auto& enemy : enemies)
            window.draw(enemy.shape);

        for (const auto& btenemy : btenemies)
            window.draw(btenemy->shape);

        window.display();
    }
    return 0;
}

