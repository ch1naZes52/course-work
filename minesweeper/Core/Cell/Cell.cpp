#include "Cell.h"

Cell::Cell()
    : m_position(),
    m_state(CellState::Closed),
    m_type(CellType::Empty),
    m_adjacentMines(0) {
}

Cell::Cell(const CellPosition& position)
    : m_position(position),
    m_state(CellState::Closed),
    m_type(CellType::Empty),
    m_adjacentMines(0) {
}

const CellPosition& Cell::position() const {
    return m_position;
}

CellState Cell::state() const {
    return m_state;
}

CellType Cell::type() const {
    return m_type;
}

int Cell::adjacentMines() const {
    return m_adjacentMines;
}

bool Cell::isOpened() const {
    return m_state == CellState::Opened;
}

bool Cell::isClosed() const {
    return m_state == CellState::Closed;
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

bool Cell::canBeOpened() const {
    return m_state == CellState::Closed;
}

bool Cell::canBeFlagged() const {
    return m_state == CellState::Closed || m_state == CellState::Flagged;
}

void Cell::setPosition(const CellPosition& position) {
    m_position = position;
}

void Cell::setMine() {
    m_type = CellType::Mine;
    m_adjacentMines = 0;
}

void Cell::clearMine() {
    m_type = CellType::Empty;
    m_adjacentMines = 0;
}

void Cell::setAdjacentMines(int count) {
    if (m_type == CellType::Mine) {
        return;
    }

    m_adjacentMines = count;
    updateTypeByAdjacentMines();
}

bool Cell::open() {
    if (!canBeOpened()) {
        return false;
    }

    m_state = CellState::Opened;
    return true;
}

bool Cell::reveal() {
    if (m_state == CellState::Opened) {
        return false;
    }

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

bool Cell::placeFlag() {
    if (m_state != CellState::Closed) {
        return false;
    }

    m_state = CellState::Flagged;
    return true;
}

bool Cell::removeFlag() {
    if (m_state != CellState::Flagged) {
        return false;
    }

    m_state = CellState::Closed;
    return true;
}

void Cell::reset() {
    m_state = CellState::Closed;
    m_type = CellType::Empty;
    m_adjacentMines = 0;
}

void Cell::updateTypeByAdjacentMines() {
    if (m_adjacentMines > 0) {
        m_type = CellType::Number;
    }
    else {
        m_type = CellType::Empty;
    }
}