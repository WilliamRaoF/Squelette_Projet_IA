#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include <vector>


const int WINDOW_WIDTH = 1480;
const int WINDOW_HEIGHT = 880;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player({200 , 400});
    std::vector<Enemy> enemies = { Enemy(player ,{100,100}, 200.0f), Enemy(player, {700, 100}, 10.0f) };
    Grid grid;
    grid.loadFromFile("map.txt");

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
        enemies[0].update(deltaTime, grid);

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies)
            window.draw(enemy.shape);
        window.display();
    }
    return 0;
}

