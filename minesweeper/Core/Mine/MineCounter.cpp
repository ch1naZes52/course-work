#include "MineCounter.h"

MineCounter::MineCounter()
    : m_totalMines(0),
    m_flaggedCells(0) {
}

MineCounter::MineCounter(int totalMines)
    : m_totalMines(totalMines),
    m_flaggedCells(0) {
}

int MineCounter::totalMines() const {
    return m_totalMines;
}

int MineCounter::flaggedCells() const {
    return m_flaggedCells;
}

int MineCounter::remainingMines() const {
    return m_totalMines - m_flaggedCells;
}

void MineCounter::setTotalMines(int totalMines) {
    m_totalMines = totalMines;
    m_flaggedCells = 0;
}

void MineCounter::reset(int totalMines) {
    m_totalMines = totalMines;
    m_flaggedCells = 0;
}

bool MineCounter::addFlag() {
    if (m_flaggedCells >= m_totalMines) {
        return false;
    }

    ++m_flaggedCells;
    return true;
}

bool MineCounter::removeFlag() {
    if (m_flaggedCells <= 0) {
        return false;
    }

    --m_flaggedCells;
    return true;
}