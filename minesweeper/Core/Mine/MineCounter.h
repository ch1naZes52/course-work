#pragma once

class MineCounter {
public:
    MineCounter();
    explicit MineCounter(int totalMines);

    int totalMines() const;
    int flaggedCells() const;
    int remainingMines() const;

    void setTotalMines(int totalMines);
    void reset(int totalMines);

    bool addFlag();
    bool removeFlag();

private:
    int m_totalMines;
    int m_flaggedCells;
};