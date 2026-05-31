#include "GameAnalyzer.h"

GameResult GameAnalyzer::analyze(const GameBoard& board) const {
    if (hasOpenedMine(board)) {
        return GameResult::Defeat;
    }

    if (allSafeCellsOpened(board)) {
        return GameResult::Victory;
    }

    return GameResult::None;
}

bool GameAnalyzer::hasOpenedMine(const GameBoard& board) const {
    for (const Cell* cell : board.cells()) {
        if (cell->isMine() && cell->isOpened()) {
            return true;
        }
    }

    return false;
}

bool GameAnalyzer::allSafeCellsOpened(const GameBoard& board) const {
    for (const Cell* cell : board.cells()) {
        if (!cell->isMine() && !cell->isOpened()) {
            return false;
        }
    }

    return true;
}