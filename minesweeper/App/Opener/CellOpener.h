#pragma once

#include "../../Core/Board/GameBoard.h"

class CellOpener {
public:
    bool open(GameBoard& board, const CellPosition& position);
};