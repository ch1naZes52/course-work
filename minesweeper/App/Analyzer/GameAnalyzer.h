#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Game/GameResult.h"

class GameAnalyzer {
public:
    GameResult analyze(const GameBoard& board) const;

    bool hasOpenedMine(const GameBoard& board) const;
    bool allSafeCellsOpened(const GameBoard& board) const;
};