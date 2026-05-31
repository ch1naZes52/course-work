#pragma once

#include "IGameFactory.h"

class GameFactory : public IGameFactory {
public:
    GameSettings createSettings(GameDifficulty difficulty) const override;
    GameBoard createBoard(const GameSettings& settings) const override;
    MineCounter createMineCounter(const GameSettings& settings) const override;
};