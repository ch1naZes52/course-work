#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Cell/CellPosition.h"
#include "../../Core/Mine/MineCounter.h"

class FlagManager {
public:
    bool toggleFlag(GameBoard& board, MineCounter& mineCounter, const CellPosition& position);

private:
    bool placeFlag(Cell& cell, MineCounter& mineCounter);
    bool removeFlag(Cell& cell, MineCounter& mineCounter);
};