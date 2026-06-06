#pragma once

#include "../Board/BoardSize.h"
#include "GameDifficulty.h"

class GameSettings {
public:
    GameSettings();
    GameSettings(const BoardSize& size, int mines, GameDifficulty difficulty);
    const BoardSize& size() const;
    int mines() const;
    GameDifficulty difficulty() const;
    static GameSettings create(GameDifficulty difficulty);

private:
    BoardSize m_size;
    int m_mines;
    GameDifficulty m_difficulty;
};