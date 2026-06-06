#include "GameAnalyzer.h"

GameResult GameAnalyzer::analyze(const GameBoard& board) const {
    int safe = 0;
    int opened = 0;

    for (const Cell& cell : board.cells()) {
        if (cell.isMine() && cell.isOpened()) {
            return GameResult::Defeat;
        }

        safe += cell.isMine() ? 0 : 1;
        opened += !cell.isMine() && cell.isOpened() ? 1 : 0;
    }

    return safe == opened ? GameResult::Victory : GameResult::None;
}