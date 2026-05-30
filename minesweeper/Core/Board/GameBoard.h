#pragma once

#include "BoardSize.h"
#include "../Cell/Cell.h"

#include <vector>

class GameBoard {
public:
    GameBoard();
    explicit GameBoard(const BoardSize& size);

    const BoardSize& size() const;
    int rows() const;
    int columns() const;
    int cellCount() const;

    bool isValidPosition(const CellPosition& position) const;

    Cell& cellAt(const CellPosition& position);
    const Cell& cellAt(const CellPosition& position) const;

    std::vector<Cell*> neighborsOf(const CellPosition& position);
    std::vector<const Cell*> neighborsOf(const CellPosition& position) const;

    std::vector<Cell*> cells();
    std::vector<const Cell*> cells() const;

    void resize(const BoardSize& size);
    void reset();

    int openedCellCount() const;
    int flaggedCellCount() const;
    int closedCellCount() const;

private:
    BoardSize m_size;
    std::vector<std::vector<Cell>> m_cells;

    void createCells();
};