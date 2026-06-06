#pragma once

class MineCounter {
public:
    MineCounter();
    int remaining() const;
    void reset(int mines);
    bool addFlag();
    bool removeFlag();

private:
    int m_mines;
    int m_flags;
};