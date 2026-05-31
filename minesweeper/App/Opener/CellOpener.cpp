#include "CellOpener.h"

#include <queue>

bool CellOpener::open(GameBoard& board, const CellPosition& position) {
    if (!board.isValidPosition(position)) {
        return false;
    }

    Cell& cell = board.cellAt(position);

    if (!cell.canBeOpened()) {
        return false;
    }

    if (cell.isMine()) {
        return cell.open();
    }

    if (cell.isNumber()) {
        return cell.open();
    }

    openEmptyArea(board, position);
    return true;
}

void CellOpener::openEmptyArea(GameBoard& board, const CellPosition& startPosition) {
    std::queue<CellPosition> positions;
    positions.push(startPosition);

    while (!positions.empty()) {
        CellPosition currentPosition = positions.front();
        positions.pop();

        Cell& currentCell = board.cellAt(currentPosition);

        if (!currentCell.canBeOpened()) {
            continue;
        }

        currentCell.open();

        if (!currentCell.isEmpty()) {
            continue;
        }

        for (Cell* neighbor : board.neighborsOf(currentPosition)) {
            if (!neighbor->canBeOpened()) {
                continue;
            }

            if (neighbor->isMine()) {
                continue;
            }

            if (neighbor->isEmpty()) {
                positions.push(neighbor->position());
            }
            else {
                neighbor->open();
            }
        }
    }
}