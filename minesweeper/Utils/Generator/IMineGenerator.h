#pragma once

#include "../../Core/Board/GameBoard.h"
#include "../../Core/Cell/CellPosition.h"

class IMineGenerator {
public:
    virtual ~IMineGenerator() = default;

    virtual void generate(GameBoard& board, int mineCount, const CellPosition& firstMove) = 0;
};