#include "GameBoard.h"

GameBoard::GameBoard() : m_size(), m_cells() {
    reset(m_size);
}

GameBoard::GameBoard(const BoardSize& size) : m_size(size), m_cells() {
    reset(size);
}

int GameBoard::rows() const {
    return m_size.rows();
}

int GameBoard::columns() const {
    return m_size.columns();
}

int GameBoard::cellCount() const {
    return m_size.cells();
}

bool GameBoard::contains(const CellPosition& position) const {
    return m_size.contains(position);
}

Cell& GameBoard::cell(const CellPosition& position) {
    return m_cells[index(position)];
}

const Cell& GameBoard::cell(const CellPosition& position) const {
    return m_cells[index(position)];
}

std::vector<CellPosition> GameBoard::neighbors(const CellPosition& position) const {
    std::vector<CellPosition> result;

    for (int row = -1; row <= 1; ++row) {
        for (int column = -1; column <= 1; ++column) {
            CellPosition next(position.row() + row, position.column() + column);

            if ((row != 0 || column != 0) && contains(next)) {
                result.push_back(next);
            }
        }
    }

    return result;
}

std::vector<Cell>& GameBoard::cells() {
    return m_cells;
}

const std::vector<Cell>& GameBoard::cells() const {
    return m_cells;
}

void GameBoard::reset(const BoardSize& size) {
    m_size = size;
    m_cells.clear();

    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < columns(); ++column) {
            m_cells.push_back(Cell(CellPosition(row, column)));
        }
    }
}

void GameBoard::revealMines() {
    for (Cell& cell : m_cells) {
        if (cell.isMine()) {
            cell.reveal();
        }
    }
}

int GameBoard::openedCount() const {
    int count = 0;

    for (const Cell& cell : m_cells) {
        count += cell.isOpened() ? 1 : 0;
    }

    return count;
}

int GameBoard::index(const CellPosition& position) const {
    return position.row() * columns() + position.column();
}