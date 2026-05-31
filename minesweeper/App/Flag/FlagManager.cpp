#include "FlagManager.h"

bool FlagManager::toggleFlag(GameBoard& board, MineCounter& mineCounter, const CellPosition& position) {
    if (!board.isValidPosition(position)) {
        return false;
    }

    Cell& cell = board.cellAt(position);

    if (!cell.canBeFlagged()) {
        return false;
    }

    if (cell.isFlagged()) {
        return removeFlag(cell, mineCounter);
    }

    return placeFlag(cell, mineCounter);
}

bool FlagManager::placeFlag(Cell& cell, MineCounter& mineCounter) {
    if (!mineCounter.addFlag()) {
        return false;
    }

    if (!cell.placeFlag()) {
        mineCounter.removeFlag();
        return false;
    }

    return true;
}

bool FlagManager::removeFlag(Cell& cell, MineCounter& mineCounter) {
    if (!cell.removeFlag()) {
        return false;
    }

    if (!mineCounter.removeFlag()) {
        cell.placeFlag();
        return false;
    }

    return true;
}