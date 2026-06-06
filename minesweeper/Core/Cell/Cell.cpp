#include "Cell.h"

Cell::Cell() : m_position(), m_state(CellState::Closed), m_type(CellType::Empty), m_adjacentMines(0) {}

Cell::Cell(const CellPosition& position) : m_position(position), m_state(CellState::Closed), m_type(CellType::Empty), m_adjacentMines(0) {}

const CellPosition& Cell::position() const {
    return m_position;
}

int Cell::adjacentMines() const {
    return m_adjacentMines;
}

bool Cell::isOpened() const {
    return m_state == CellState::Opened;
}

bool Cell::isFlagged() const {
    return m_state == CellState::Flagged;
}

bool Cell::isMine() const {
    return m_type == CellType::Mine;
}

bool Cell::isEmpty() const {
    return m_type == CellType::Empty;
}

bool Cell::isNumber() const {
    return m_type == CellType::Number;
}

bool Cell::canOpen() const {
    return m_state == CellState::Closed;
}

void Cell::setMine() {
    m_type = CellType::Mine;
    m_adjacentMines = 0;
}

void Cell::setAdjacentMines(int count) {
    if (!isMine()) {
        m_adjacentMines = count;
        m_type = count > 0 ? CellType::Number : CellType::Empty;
    }
}

bool Cell::open() {
    if (!canOpen()) {
        return false;
    }

    m_state = CellState::Opened;
    return true;
}

bool Cell::reveal() {
    m_state = CellState::Opened;
    return true;
}

bool Cell::toggleFlag() {
    if (m_state == CellState::Closed) {
        m_state = CellState::Flagged;
        return true;
    }

    if (m_state == CellState::Flagged) {
        m_state = CellState::Closed;
        return true;
    }

    return false;
}

void Cell::reset() {
    m_state = CellState::Closed;
    m_type = CellType::Empty;
    m_adjacentMines = 0;
}