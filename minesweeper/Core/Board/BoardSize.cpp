#include "BoardSize.h"

BoardSize::BoardSize()
    : m_rows(0),
    m_columns(0) {
}

BoardSize::BoardSize(int rows, int columns)
    : m_rows(rows),
    m_columns(columns) {
}

int BoardSize::rows() const {
    return m_rows;
}

int BoardSize::columns() const {
    return m_columns;
}

int BoardSize::cellCount() const {
    return m_rows * m_columns;
}

void BoardSize::setRows(int rows) {
    m_rows = rows;
}

void BoardSize::setColumns(int columns) {
    m_columns = columns;
}

bool BoardSize::isValid() const {
    return m_rows > 0 && m_columns > 0;
}

bool BoardSize::contains(const CellPosition& position) const {
    return position.row() >= 0 &&
        position.row() < m_rows &&
        position.column() >= 0 &&
        position.column() < m_columns;
}