#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Cell/CellPosition.h"

class CellOpener {
public:
    bool open(GameBoard& board, const CellPosition& position);

private:
    void openEmptyArea(GameBoard& board, const CellPosition& startPosition);
};