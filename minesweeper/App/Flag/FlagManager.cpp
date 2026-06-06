#include "FlagManager.h"

bool FlagManager::toggle(GameBoard& board, MineCounter& counter, const CellPosition& position) {
    if (!board.contains(position) || board.cell(position).isOpened()) {
        return false;
    }

    Cell& cell = board.cell(position);

    if (cell.isFlagged()) {
        cell.toggleFlag();
        counter.removeFlag();
        return true;
    }

    if (!counter.addFlag()) {
        return false;
    }

    cell.toggleFlag();
    return true;
}