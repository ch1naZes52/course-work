#pragma once

#include "CellPosition.h"
#include "CellState.h"
#include "CellType.h"

class Cell {
public:
    Cell();
    explicit Cell(const CellPosition& position);
    const CellPosition& position() const;
    int adjacentMines() const;
    bool isOpened() const;
    bool isFlagged() const;
    bool isMine() const;
    bool isEmpty() const;
    bool isNumber() const;
    bool canOpen() const;
    void setMine();
    void setAdjacentMines(int count);
    bool open();
    bool reveal();
    bool toggleFlag();
    void reset();

private:
    CellPosition m_position;
    CellState m_state;
    CellType m_type;
    int m_adjacentMines;
};