#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <cmath>

class Raycaster {
public:
    float startX, startY;  // Position du rayon
    float dirX, dirY;      // Direction du rayon

    Raycaster()
        : startX(0), startY(0), dirX(0), dirY(0) {
    }

    Raycaster(float startX, float startY, float dirX, float dirY)
        : startX(startX), startY(startY), dirX(dirX), dirY(dirY) {
    }

    // DDA Raycasting pour détecter les collisions avec la grille
    bool castRay(Grid& grid, float& hitX, float& hitY) {
        // Variables pour DDA
        float deltaX = std::abs(1 / dirX);
        float deltaY = std::abs(1 / dirY);

        // Variables de pas
        int stepX, stepY;

        // Calcul des pas
        if (dirX < 0) {
            stepX = -1;
        }
        else {
            stepX = 1;
        }

        if (dirY < 0) {
            stepY = -1;
        }
        else {
            stepY = 1;
        }

        // Variables pour la position du rayon
        float x = startX;
        float y = startY;

        // Initialisation des distances initiales
        float nextX = (stepX == 1) ? (std::floor(x) + 1) : std::floor(x);
        float nextY = (stepY == 1) ? (std::floor(y) + 1) : std::floor(y);

        float tMaxX = (nextX - x) * deltaX;
        float tMaxY = (nextY - y) * deltaY;

        float tDeltaX = deltaX;
        float tDeltaY = deltaY;

        // Boucle de Raycasting
        while (true) {
            if (tMaxX < tMaxY) {
                x = nextX;
                nextX += stepX;
                tMaxX += tDeltaX;
            }
            else {
                y = nextY;
                nextY += stepY;
                tMaxY += tDeltaY;
            }

            // Calcul des indices de la cellule
            int cellX = static_cast<int>(std::floor(x));
            int cellY = static_cast<int>(std::floor(y));

            // Vérification de la collision avec un obstacle
            if (!grid.isWalkable(cellX, cellY)) {
                hitX = x;
                hitY = y;
                return true;  // Collision trouvée
            }

            // Condition de sortie: si on sort de la grille
            if (cellX < 0 || cellY < 0 || cellX >= grid.cells[0].size() || cellY >= grid.cells.size()) {
                return false;  // Ray sort de la grille
            }
        }
    }
};