#pragma once

#include "IMineGenerator.h"

class RandomMineGenerator : public IMineGenerator {
public:
    void generate(GameBoard& board, int mines, const CellPosition& firstMove) override;

private:
    void updateNumbers(GameBoard& board);
};