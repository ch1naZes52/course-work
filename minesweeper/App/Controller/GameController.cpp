#include "GameController.h"

GameController::GameController()
    : m_factory(),
    m_settings(m_factory.createSettings(GameDifficulty::Beginner)),
    m_board(m_factory.createBoard(m_settings)),
    m_mineCounter(m_factory.createMineCounter(m_settings)),
    m_mineGenerator(),
    m_gameAnalyzer(),
    m_cellOpener(),
    m_flagManager(),
    m_state(GameState::NotStarted),
    m_result(GameResult::None),
    m_minesGenerated(false) {
}

const GameSettings& GameController::settings() const {
    return m_settings;
}

const GameBoard& GameController::board() const {
    return m_board;
}

const MineCounter& GameController::mineCounter() const {
    return m_mineCounter;
}

GameState GameController::state() const {
    return m_state;
}

GameResult GameController::result() const {
    return m_result;
}

bool GameController::minesGenerated() const {
    return m_minesGenerated;
}

void GameController::restart(GameDifficulty difficulty) {
    m_settings = m_factory.createSettings(difficulty);
    m_board = m_factory.createBoard(m_settings);
    m_mineCounter = m_factory.createMineCounter(m_settings);
    m_state = GameState::NotStarted;
    m_result = GameResult::None;
    m_minesGenerated = false;
}

bool GameController::openCell(const CellPosition& position) {
    if (m_state == GameState::Won || m_state == GameState::Lost) {
        return false;
    }

    if (!m_board.isValidPosition(position)) {
        return false;
    }

    generateMinesIfNeeded(position);

    if (!m_cellOpener.open(m_board, position)) {
        return false;
    }

    analyzeGameState();
    return true;
}

bool GameController::toggleFlag(const CellPosition& position) {
    if (m_state != GameState::Running) {
        return false;
    }

    return m_flagManager.toggleFlag(m_board, m_mineCounter, position);
}

void GameController::generateMinesIfNeeded(const CellPosition& firstMove) {
    if (m_minesGenerated) {
        return;
    }

    m_mineGenerator.generate(m_board, m_settings.mineCount(), firstMove);
    m_mineCounter.reset(m_settings.mineCount());
    m_minesGenerated = true;
    m_state = GameState::Running;
}

void GameController::analyzeGameState() {
    GameResult analyzedResult = m_gameAnalyzer.analyze(m_board);

    if (analyzedResult != GameResult::None) {
        finishGame(analyzedResult);
    }
}

void GameController::finishGame(GameResult result) {
    m_result = result;

    if (result == GameResult::Defeat) {
        m_state = GameState::Lost;
        m_board.revealAllMines();
        return;
    }

    if (result == GameResult::Victory) {
        m_state = GameState::Won;
        return;
    }
}