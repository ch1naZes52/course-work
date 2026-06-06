#include "MineCounter.h"

MineCounter::MineCounter() : m_mines(0), m_flags(0) {}

int MineCounter::remaining() const {
    return m_mines - m_flags;
}

void MineCounter::reset(int mines) {
    m_mines = mines;
    m_flags = 0;
}

bool MineCounter::addFlag() {
    if (m_flags >= m_mines) {
        return false;
    }

    ++m_flags;
    return true;
}

bool MineCounter::removeFlag() {
    if (m_flags <= 0) {
        return false;
    }

    --m_flags;
    return true;
}