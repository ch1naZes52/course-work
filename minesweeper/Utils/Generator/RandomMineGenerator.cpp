#include "RandomMineGenerator.h"

#include <algorithm>
#include <random>
#include <vector>

void RandomMineGenerator::generate(GameBoard& board, int mineCount, const CellPosition& firstMove) {
    clearBoard(board);
    placeMines(board, mineCount, firstMove);
    updateAdjacentMineCounts(board);
}

void RandomMineGenerator::clearBoard(GameBoard& board) {
    for (Cell* cell : board.cells()) {
        cell->reset();
    }
}

void RandomMineGenerator::placeMines(GameBoard& board, int mineCount, const CellPosition& firstMove) {
    std::vector<CellPosition> positions;
    positions.reserve(board.cellCount());

    for (int row = 0; row < board.rows(); ++row) {
        for (int column = 0; column < board.columns(); ++column) {
            CellPosition position(row, column);

            if (position != firstMove) {
                positions.push_back(position);
            }
        }
    }

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::shuffle(positions.begin(), positions.end(), generator);

    int minesToPlace = std::min(mineCount, static_cast<int>(positions.size()));

    for (int index = 0; index < minesToPlace; ++index) {
        board.cellAt(positions[index]).setMine();
    }
}

void RandomMineGenerator::updateAdjacentMineCounts(GameBoard& board) {
    for (Cell* cell : board.cells()) {
        if (cell->isMine()) {
            continue;
        }

        int count = 0;

        for (const Cell* neighbor : board.neighborsOf(cell->position())) {
            if (neighbor->isMine()) {
                ++count;
            }
        }

        cell->setAdjacentMines(count);
    }
}