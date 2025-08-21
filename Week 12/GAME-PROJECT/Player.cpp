#include "Player.h"
#include "Game.h"
#include "Monster.h"
Player::Player() : currentPosition(1) {}

void Player::setCurrentPosition(int currentPosition)
{
    if (currentPosition < 1 || currentPosition > GlobalConstants::MAX_BORDER)
        throw std::invalid_argument("Invalid position\n");

    this->currentPosition = currentPosition;
}

void Player::interact(Artifact& interactWithArtifact)
{
    interactWithArtifact.interact(*this);
}

LivingThings* Player::clone() const
{
    return new Player(*this);
}
