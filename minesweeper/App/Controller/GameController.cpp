#include "GameController.h"

GameController::GameController()
    : m_settings(m_factory.createSettings(GameDifficulty::Beginner)),
    m_board(m_factory.createBoard(m_settings)),
    m_counter(m_factory.createCounter(m_settings)),
    m_state(GameState::NotStarted),
    m_generated(false),
    m_observer(nullptr) {}

const GameSettings& GameController::settings() const {
    return m_settings;
}

const GameBoard& GameController::board() const {
    return m_board;
}

const MineCounter& GameController::counter() const {
    return m_counter;
}

GameState GameController::state() const {
    return m_state;
}

void GameController::setObserver(IGameObserver* observer) {
    m_observer = observer;
}

void GameController::restart(GameDifficulty difficulty) {
    m_settings = m_factory.createSettings(difficulty);
    m_board = m_factory.createBoard(m_settings);
    m_counter = m_factory.createCounter(m_settings);
    m_state = GameState::NotStarted;
    m_generated = false;
    event("Создана новая игра");
    notify();
}

bool GameController::openCell(const CellPosition& position) {
    if (m_state == GameState::Won || m_state == GameState::Lost) {
        return false;
    }

    if (!m_generated) {
        generate(position);
    }

    if (!m_opener.open(m_board, position)) {
        return false;
    }

    event("Открыта клетка " + positionText(position));

    GameResult result = m_analyzer.analyze(m_board);

    if (result != GameResult::None) {
        finish(result);
    }

    notify();
    return true;
}

bool GameController::toggleFlag(const CellPosition& position) {
    if (m_state != GameState::Running || !m_flags.toggle(m_board, m_counter, position)) {
        return false;
    }

    event("Изменен флажок " + positionText(position));
    notify();
    return true;
}

void GameController::generate(const CellPosition& firstMove) {
    m_generator.generate(m_board, m_settings.mines(), firstMove);
    m_counter.reset(m_settings.mines());
    m_state = GameState::Running;
    m_generated = true;
    event("Мины сгенерированы");
}

void GameController::finish(GameResult result) {
    if (result == GameResult::Defeat) {
        m_board.revealMines();
        m_state = GameState::Lost;
        event("Поражение");
        return;
    }

    m_state = GameState::Won;
    event("Победа");
}

void GameController::notify() {
    if (m_observer) {
        m_observer->onGameChanged();
    }
}

void GameController::event(const std::string& text) {
    if (m_observer) {
        m_observer->onGameEvent(text);
    }
}

std::string GameController::positionText(const CellPosition& position) const {
    return "(" + std::to_string(position.row() + 1) + ", " + std::to_string(position.column() + 1) + ")";
}