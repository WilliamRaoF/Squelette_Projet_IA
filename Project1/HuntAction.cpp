#include "HuntAction.h"

bool HuntAction::CanExecute(const State& state)
{
	return !state.getPatrolling() && !state.getSearching() && !state.getShouldFlee();
}

void HuntAction::Execute(State& state)
{
	cout << "L'ennemi chasse le joueur";
    enemyGoap->getshape().setFillColor(sf::Color::Red);
    sf::Vector2f direction = player->getshape().getPosition() - enemyGoap->getshape().getPosition();
    sf::Vector2f position = enemyGoap->getshape().getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 2.0f;
    }
    enemyGoap->getshape().setPosition(position);
}


