#pragma once

#include "BoardSize.h"
#include "../Cell/Cell.h"
#include <vector>

class GameBoard {
public:
    GameBoard();
    explicit GameBoard(const BoardSize& size);
    int rows() const;
    int columns() const;
    int cellCount() const;
    bool contains(const CellPosition& position) const;
    Cell& cell(const CellPosition& position);
    const Cell& cell(const CellPosition& position) const;
    std::vector<CellPosition> neighbors(const CellPosition& position) const;
    std::vector<Cell>& cells();
    const std::vector<Cell>& cells() const;
    void reset(const BoardSize& size);
    void revealMines();
    int openedCount() const;

private:
    BoardSize m_size;
    std::vector<Cell> m_cells;
    int index(const CellPosition& position) const;
};