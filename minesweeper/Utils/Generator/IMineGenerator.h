#pragma once

#include "../../Core/Board/GameBoard.h"

class IMineGenerator {
public:
    virtual ~IMineGenerator() = default;
    virtual void generate(GameBoard& board, int mines, const CellPosition& firstMove) = 0;
};