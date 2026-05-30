#include "CellPosition.h"

CellPosition::CellPosition()
    : m_row(0),
    m_column(0) {
}

CellPosition::CellPosition(int row, int column)
    : m_row(row),
    m_column(column) {
}

int CellPosition::row() const {
    return m_row;
}

int CellPosition::column() const {
    return m_column;
}

void CellPosition::setRow(int row) {
    m_row = row;
}

void CellPosition::setColumn(int column) {
    m_column = column;
}

bool CellPosition::operator==(const CellPosition& other) const {
    return m_row == other.m_row && m_column == other.m_column;
}

bool CellPosition::operator!=(const CellPosition& other) const {
    return !(*this == other);
}