#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Game/GameSettings.h"
#include "../../Core/Mine/MineCounter.h"

class IGameFactory {
public:
    virtual ~IGameFactory() = default;
    virtual GameSettings createSettings(GameDifficulty difficulty) const = 0;
    virtual GameBoard createBoard(const GameSettings& settings) const = 0;
    virtual MineCounter createCounter(const GameSettings& settings) const = 0;
};