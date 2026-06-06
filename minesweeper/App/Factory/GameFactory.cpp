#include "GameFactory.h"

GameSettings GameFactory::createSettings(GameDifficulty difficulty) const {
    return GameSettings::create(difficulty);
}

GameBoard GameFactory::createBoard(const GameSettings& settings) const {
    return GameBoard(settings.size());
}

MineCounter GameFactory::createCounter(const GameSettings& settings) const {
    MineCounter counter;
    counter.reset(settings.mines());
    return counter;
}