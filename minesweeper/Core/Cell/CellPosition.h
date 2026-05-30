#pragma once

class CellPosition {
public:
    CellPosition();
    CellPosition(int row, int column);

    int row() const;
    int column() const;

    void setRow(int row);
    void setColumn(int column);

    bool operator==(const CellPosition& other) const;
    bool operator!=(const CellPosition& other) const;

private:
    int m_row;
    int m_column;
};