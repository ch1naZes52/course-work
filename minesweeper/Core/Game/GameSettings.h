#pragma once

#include "../Board/BoardSize.h"
#include "GameDifficulty.h"

class GameSettings {
public:
    GameSettings();
    GameSettings(const BoardSize& boardSize, int mineCount, GameDifficulty difficulty);

    const BoardSize& boardSize() const;
    int mineCount() const;
    GameDifficulty difficulty() const;

    void setBoardSize(const BoardSize& boardSize);
    void setMineCount(int mineCount);
    void setDifficulty(GameDifficulty difficulty);

    bool isValid() const;

    static GameSettings beginner();
    static GameSettings intermediate();
    static GameSettings expert();
    static GameSettings custom(int rows, int columns, int mines);

private:
    BoardSize m_boardSize;
    int m_mineCount;
    GameDifficulty m_difficulty;
};