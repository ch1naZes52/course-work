#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Game/GameResult.h"

class GameAnalyzer {
public:
    GameResult analyze(const GameBoard& board) const;
};