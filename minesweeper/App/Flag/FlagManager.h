#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Mine/MineCounter.h"

class FlagManager {
public:
    bool toggle(GameBoard& board, MineCounter& counter, const CellPosition& position);
};