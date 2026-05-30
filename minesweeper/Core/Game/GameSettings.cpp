#include "GameSettings.h"

GameSettings::GameSettings()
    : m_boardSize(9, 9),
    m_mineCount(10),
    m_difficulty(GameDifficulty::Beginner) {
}

GameSettings::GameSettings(const BoardSize& boardSize, int mineCount, GameDifficulty difficulty)
    : m_boardSize(boardSize),
    m_mineCount(mineCount),
    m_difficulty(difficulty) {
}

const BoardSize& GameSettings::boardSize() const {
    return m_boardSize;
}

int GameSettings::mineCount() const {
    return m_mineCount;
}

GameDifficulty GameSettings::difficulty() const {
    return m_difficulty;
}

void GameSettings::setBoardSize(const BoardSize& boardSize) {
    m_boardSize = boardSize;
}

void GameSettings::setMineCount(int mineCount) {
    m_mineCount = mineCount;
}

void GameSettings::setDifficulty(GameDifficulty difficulty) {
    m_difficulty = difficulty;
}

bool GameSettings::isValid() const {
    return m_boardSize.isValid() &&
        m_mineCount > 0 &&
        m_mineCount < m_boardSize.cellCount();
}

GameSettings GameSettings::beginner() {
    return GameSettings(BoardSize(9, 9), 10, GameDifficulty::Beginner);
}

GameSettings GameSettings::intermediate() {
    return GameSettings(BoardSize(16, 16), 40, GameDifficulty::Intermediate);
}

GameSettings GameSettings::expert() {
    return GameSettings(BoardSize(16, 30), 99, GameDifficulty::Expert);
}

GameSettings GameSettings::custom(int rows, int columns, int mines) {
    return GameSettings(BoardSize(rows, columns), mines, GameDifficulty::Custom);
}