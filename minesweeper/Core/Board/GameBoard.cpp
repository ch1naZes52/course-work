#include "GameBoard.h"

#include <stdexcept>

GameBoard::GameBoard()
    : m_size(0, 0) {
}

GameBoard::GameBoard(const BoardSize& size)
    : m_size(size) {
    createCells();
}

const BoardSize& GameBoard::size() const {
    return m_size;
}

int GameBoard::rows() const {
    return m_size.rows();
}

int GameBoard::columns() const {
    return m_size.columns();
}

int GameBoard::cellCount() const {
    return m_size.cellCount();
}

bool GameBoard::isValidPosition(const CellPosition& position) const {
    return m_size.contains(position);
}

Cell& GameBoard::cellAt(const CellPosition& position) {
    if (!isValidPosition(position)) {
        throw std::out_of_range("Invalid cell position");
    }

    return m_cells[position.row()][position.column()];
}

const Cell& GameBoard::cellAt(const CellPosition& position) const {
    if (!isValidPosition(position)) {
        throw std::out_of_range("Invalid cell position");
    }

    return m_cells[position.row()][position.column()];
}

std::vector<Cell*> GameBoard::neighborsOf(const CellPosition& position) {
    std::vector<Cell*> result;

    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int columnOffset = -1; columnOffset <= 1; ++columnOffset) {
            if (rowOffset == 0 && columnOffset == 0) {
                continue;
            }

            CellPosition neighborPosition(
                position.row() + rowOffset,
                position.column() + columnOffset
            );

            if (isValidPosition(neighborPosition)) {
                result.push_back(&cellAt(neighborPosition));
            }
        }
    }

    return result;
}

std::vector<const Cell*> GameBoard::neighborsOf(const CellPosition& position) const {
    std::vector<const Cell*> result;

    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int columnOffset = -1; columnOffset <= 1; ++columnOffset) {
            if (rowOffset == 0 && columnOffset == 0) {
                continue;
            }

            CellPosition neighborPosition(
                position.row() + rowOffset,
                position.column() + columnOffset
            );

            if (isValidPosition(neighborPosition)) {
                result.push_back(&cellAt(neighborPosition));
            }
        }
    }

    return result;
}

std::vector<Cell*> GameBoard::cells() {
    std::vector<Cell*> result;
    result.reserve(cellCount());

    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < columns(); ++column) {
            result.push_back(&m_cells[row][column]);
        }
    }

    return result;
}

std::vector<const Cell*> GameBoard::cells() const {
    std::vector<const Cell*> result;
    result.reserve(cellCount());

    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < columns(); ++column) {
            result.push_back(&m_cells[row][column]);
        }
    }

    return result;
}

void GameBoard::resize(const BoardSize& size) {
    m_size = size;
    createCells();
}

void GameBoard::reset() {
    for (Cell* cell : cells()) {
        cell->reset();
    }
}

void GameBoard::revealAllMines() {
    for (Cell* cell : cells()) {
        if (cell->isMine()) {
            cell->reveal();
        }
    }
}

int GameBoard::openedCellCount() const {
    int count = 0;

    for (const Cell* cell : cells()) {
        if (cell->isOpened()) {
            ++count;
        }
    }

    return count;
}

int GameBoard::flaggedCellCount() const {
    int count = 0;

    for (const Cell* cell : cells()) {
        if (cell->isFlagged()) {
            ++count;
        }
    }

    return count;
}

int GameBoard::closedCellCount() const {
    int count = 0;

    for (const Cell* cell : cells()) {
        if (cell->isClosed()) {
            ++count;
        }
    }

    return count;
}

int GameBoard::mineCount() const {
    int count = 0;

    for (const Cell* cell : cells()) {
        if (cell->isMine()) {
            ++count;
        }
    }

    return count;
}

void GameBoard::createCells() {
    m_cells.clear();
    m_cells.resize(rows());

    for (int row = 0; row < rows(); ++row) {
        m_cells[row].reserve(columns());

        for (int column = 0; column < columns(); ++column) {
            m_cells[row].push_back(Cell(CellPosition(row, column)));
        }
    }
}