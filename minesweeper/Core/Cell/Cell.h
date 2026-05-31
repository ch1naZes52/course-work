#pragma once

#include "CellPosition.h"
#include "CellState.h"
#include "CellType.h"

class Cell {
public:
    Cell();
    explicit Cell(const CellPosition& position);

    const CellPosition& position() const;
    CellState state() const;
    CellType type() const;
    int adjacentMines() const;

    bool isOpened() const;
    bool isClosed() const;
    bool isFlagged() const;
    bool isMine() const;
    bool isEmpty() const;
    bool isNumber() const;
    bool canBeOpened() const;
    bool canBeFlagged() const;

    void setPosition(const CellPosition& position);
    void setMine();
    void clearMine();
    void setAdjacentMines(int count);

    bool open();
    bool reveal();
    bool toggleFlag();
    bool placeFlag();
    bool removeFlag();

    void reset();

private:
    CellPosition m_position;
    CellState m_state;
    CellType m_type;
    int m_adjacentMines;

    void updateTypeByAdjacentMines();
};