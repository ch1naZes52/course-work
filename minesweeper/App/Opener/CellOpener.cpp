#include "CellOpener.h"

#include <queue>

bool CellOpener::open(GameBoard& board, const CellPosition& position) {
    if (!board.contains(position) || !board.cell(position).canOpen()) {
        return false;
    }

    if (board.cell(position).isMine() || board.cell(position).isNumber()) {
        return board.cell(position).open();
    }

    std::queue<CellPosition> queue;
    queue.push(position);

    while (!queue.empty()) {
        CellPosition current = queue.front();
        queue.pop();

        Cell& cell = board.cell(current);

        if (!cell.canOpen()) {
            continue;
        }

        cell.open();

        if (!cell.isEmpty()) {
            continue;
        }

        for (const CellPosition& next : board.neighbors(current)) {
            Cell& neighbor = board.cell(next);

            if (!neighbor.canOpen() || neighbor.isMine()) {
                continue;
            }

            if (neighbor.isEmpty()) {
                queue.push(next);
            }
            else {
                neighbor.open();
            }
        }
    }

    return true;
}