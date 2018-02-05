#include "include/Tetris/player.h"

/**
 * @brief Get sum of player points
 * @return Player points
 */
unsigned int Tetris::Player::getPoints() const
{
    return this->points;
}

/**
 * @brief Set sum of player points
 * @param value Value to be set
 */
void Tetris::Player::setPoints(unsigned int value)
{
    this->points = value;
}

/**
 * @brief Add points to player points sum
 * @param points Amount of points to be added
 */
void Tetris::Player::addPoints(unsigned int points)
{
    this->points += points;
}

/**
 * @brief Get current player level
 * @return Player level
 */
unsigned int Tetris::Player::getLevel() const
{
    return this->level;
}

/**
 * @brief Set player level
 * @param value Level to be set
 */
void Tetris::Player::setLevel(unsigned int value)
{
    this->level = value;
}

/**
 * @brief Add levels to player level
 * @param levels Levels to be added
 */
void Tetris::Player::addLevels(unsigned int levels)
{
    this->level += levels;
}

