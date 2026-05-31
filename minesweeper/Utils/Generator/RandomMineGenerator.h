#pragma once

#include "IMineGenerator.h"

class RandomMineGenerator : public IMineGenerator {
public:
    void generate(GameBoard& board, int mineCount, const CellPosition& firstMove) override;

private:
    void clearBoard(GameBoard& board);
    void placeMines(GameBoard& board, int mineCount, const CellPosition& firstMove);
    void updateAdjacentMineCounts(GameBoard& board);
};