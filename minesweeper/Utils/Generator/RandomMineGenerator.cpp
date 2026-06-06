#include "RandomMineGenerator.h"
#include <algorithm>
#include <random>
#include <vector>

void RandomMineGenerator::generate(GameBoard& board, int mines, const CellPosition& firstMove) {
    std::vector<CellPosition> positions;

    for (int row = 0; row < board.rows(); ++row) {
        for (int column = 0; column < board.columns(); ++column) {
            CellPosition position(row, column);

            if (position != firstMove) {
                positions.push_back(position);
            }
        }
    }

    std::shuffle(positions.begin(), positions.end(), std::mt19937(std::random_device()()));

    for (int i = 0; i < mines && i < static_cast<int>(positions.size()); ++i) {
        board.cell(positions[i]).setMine();
    }

    updateNumbers(board);
}

void RandomMineGenerator::updateNumbers(GameBoard& board) {
    for (Cell& cell : board.cells()) {
        if (cell.isMine()) {
            continue;
        }

        int count = 0;

        for (const CellPosition& position : board.neighbors(cell.position())) {
            count += board.cell(position).isMine() ? 1 : 0;
        }

        cell.setAdjacentMines(count);
    }
}