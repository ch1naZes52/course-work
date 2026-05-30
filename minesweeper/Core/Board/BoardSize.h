#pragma once

#include "../Cell/CellPosition.h"

class BoardSize {
public:
    BoardSize();
    BoardSize(int rows, int columns);

    int rows() const;
    int columns() const;
    int cellCount() const;

    void setRows(int rows);
    void setColumns(int columns);

    bool isValid() const;
    bool contains(const CellPosition& position) const;

private:
    int m_rows;
    int m_columns;
};