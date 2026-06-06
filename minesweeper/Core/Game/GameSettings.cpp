#include "GameSettings.h"

GameSettings::GameSettings() : m_size(9, 9), m_mines(10), m_difficulty(GameDifficulty::Beginner) {}

GameSettings::GameSettings(const BoardSize& size, int mines, GameDifficulty difficulty) : m_size(size), m_mines(mines), m_difficulty(difficulty) {}

const BoardSize& GameSettings::size() const {
    return m_size;
}

int GameSettings::mines() const {
    return m_mines;
}

GameDifficulty GameSettings::difficulty() const {
    return m_difficulty;
}

GameSettings GameSettings::create(GameDifficulty difficulty) {
    if (difficulty == GameDifficulty::Intermediate) {
        return GameSettings(BoardSize(16, 16), 40, difficulty);
    }

    if (difficulty == GameDifficulty::Expert) {
        return GameSettings(BoardSize(16, 30), 99, difficulty);
    }

    return GameSettings(BoardSize(9, 9), 10, GameDifficulty::Beginner);
}