#include "GameFactory.h"

GameSettings GameFactory::createSettings(GameDifficulty difficulty) const {
    if (difficulty == GameDifficulty::Beginner) {
        return GameSettings::beginner();
    }

    if (difficulty == GameDifficulty::Intermediate) {
        return GameSettings::intermediate();
    }

    if (difficulty == GameDifficulty::Expert) {
        return GameSettings::expert();
    }

    return GameSettings::beginner();
}

GameBoard GameFactory::createBoard(const GameSettings& settings) const {
    return GameBoard(settings.boardSize());
}

MineCounter GameFactory::createMineCounter(const GameSettings& settings) const {
    return MineCounter(settings.mineCount());
}