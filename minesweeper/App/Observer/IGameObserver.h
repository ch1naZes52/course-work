#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Game/GameResult.h"
#include "../../Core/Game/GameSettings.h"
#include "../../Core/Game/GameState.h"
#include "../../Core/Mine/MineCounter.h"

#include <string>

class IGameObserver {
public:
    virtual ~IGameObserver() = default;

    virtual void onBoardChanged(const GameBoard& board) = 0;
    virtual void onCountersChanged(const MineCounter& mineCounter, int openedCells) = 0;
    virtual void onGameStatusChanged(GameState state, GameResult result) = 0;
    virtual void onGameInfoChanged(const GameSettings& settings) = 0;
    virtual void onGameEvent(const std::string& eventText) = 0;
};