#include "GameController.h"

#include <string>

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

    notifyGameInfoChanged(m_settings);
    notifyFullState();
    notifyGameEvent("Создана новая игра");
}

bool GameController::openCell(const CellPosition& position) {
    if (m_state == GameState::Won || m_state == GameState::Lost) {
        notifyGameEvent("Игра уже завершена");
        return false;
    }

    if (!m_board.isValidPosition(position)) {
        notifyGameEvent("Выбрана неверная клетка");
        return false;
    }

    bool generatedNow = !m_minesGenerated;

    generateMinesIfNeeded(position);

    if (generatedNow) {
        notifyGameEvent("Мины сгенерированы после первого хода");
    }

    if (!m_cellOpener.open(m_board, position)) {
        notifyGameEvent("Клетку нельзя открыть");
        notifyFullState();
        return false;
    }

    notifyGameEvent("Открыта клетка " + positionText(position));
    analyzeGameState();
    notifyFullState();
    return true;
}

bool GameController::toggleFlag(const CellPosition& position) {
    if (m_state == GameState::Won || m_state == GameState::Lost) {
        notifyGameEvent("Игра уже завершена");
        return false;
    }

    if (m_state != GameState::Running) {
        notifyGameEvent("Флаг можно поставить после первого хода");
        return false;
    }

    if (!m_board.isValidPosition(position)) {
        notifyGameEvent("Выбрана неверная клетка");
        return false;
    }

    bool wasFlagged = m_board.cellAt(position).isFlagged();

    if (!m_flagManager.toggleFlag(m_board, m_mineCounter, position)) {
        notifyGameEvent("Флаг нельзя изменить");
        notifyFullState();
        return false;
    }

    if (wasFlagged) {
        notifyGameEvent("Флаг снят с клетки " + positionText(position));
    }
    else {
        notifyGameEvent("Флаг установлен на клетку " + positionText(position));
    }

    notifyFullState();
    return true;
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
        notifyGameEvent("Игрок открыл мину");
        return;
    }

    if (result == GameResult::Victory) {
        m_state = GameState::Won;
        notifyGameEvent("Все безопасные клетки открыты");
        return;
    }
}

void GameController::notifyFullState() {
    notifyBoardChanged(m_board);
    notifyCountersChanged(m_mineCounter, m_board.openedCellCount());
    notifyGameStatusChanged(m_state, m_result);
}

std::string GameController::positionText(const CellPosition& position) const {
    return "(" + std::to_string(position.row() + 1) + ", " + std::to_string(position.column() + 1) + ")";
}