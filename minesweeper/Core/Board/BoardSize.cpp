#include "BoardSize.h"

BoardSize::BoardSize() : m_rows(9), m_columns(9) {}

BoardSize::BoardSize(int rows, int columns) : m_rows(rows), m_columns(columns) {}

int BoardSize::rows() const {
    return m_rows;
}

int BoardSize::columns() const {
    return m_columns;
}

int BoardSize::cells() const {
    return m_rows * m_columns;
}

bool BoardSize::contains(const CellPosition& position) const {
    return position.row() >= 0 && position.row() < m_rows && position.column() >= 0 && position.column() < m_columns;
}