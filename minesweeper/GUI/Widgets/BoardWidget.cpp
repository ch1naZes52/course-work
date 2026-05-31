#include "BoardWidget.h"
#include "CellButton.h"

#include <QGridLayout>

BoardWidget::BoardWidget(QWidget* parent)
    : QWidget(parent),
    m_controller(),
    m_gridLayout(nullptr),
    m_currentDifficulty(GameDifficulty::Beginner) {
    m_controller.addObserver(this);
    setupBoard();
}

BoardWidget::~BoardWidget() {
    m_controller.removeObserver(this);
}

void BoardWidget::resetPreview() {
    RestartGameCommand command(m_controller, m_currentDifficulty);
    command.execute();
}

void BoardWidget::setDifficulty(GameDifficulty difficulty) {
    m_currentDifficulty = difficulty;

    RestartGameCommand command(m_controller, m_currentDifficulty);
    command.execute();
}

void BoardWidget::setupBoard() {
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    m_gridLayout->setSpacing(2);

    createButtons();
    updateAllButtons();

    emit flagCountChanged(m_controller.mineCounter().flaggedCells());
    emit openedCellCountChanged(m_controller.board().openedCellCount());
    emit gameStatusChanged(statusText(m_controller.state(), m_controller.result()));
    emit gameInfoChanged(m_controller.settings().mineCount(), modeText(m_controller.settings()));
    emit gameEventAdded("Интерфейс подключен к наблюдателю игры");
}

void BoardWidget::rebuildBoard() {
    createButtons();
    updateAllButtons();
}

void BoardWidget::clearBoard() {
    for (CellButton* button : m_buttons) {
        m_gridLayout->removeWidget(button);
        delete button;
    }

    m_buttons.clear();
}

void BoardWidget::createButtons() {
    clearBoard();

    BoardSize size = m_controller.settings().boardSize();

    for (int row = 0; row < size.rows(); ++row) {
        for (int column = 0; column < size.columns(); ++column) {
            CellPosition position(row, column);
            CellButton* button = new CellButton(position, this);

            connect(button, &CellButton::openRequested, this, &BoardWidget::openCell);
            connect(button, &CellButton::flagRequested, this, &BoardWidget::toggleFlag);

            m_buttons.push_back(button);
            m_gridLayout->addWidget(button, row, column);
        }
    }
}

void BoardWidget::updateButton(const CellPosition& position) {
    int index = position.row() * m_controller.settings().boardSize().columns() + position.column();

    if (index < 0 || index >= static_cast<int>(m_buttons.size())) {
        return;
    }

    m_buttons[index]->updateFromCell(m_controller.board().cellAt(position));
}

void BoardWidget::updateAllButtons() {
    for (CellButton* button : m_buttons) {
        button->updateFromCell(m_controller.board().cellAt(button->position()));
    }
}

void BoardWidget::openCell(const CellPosition& position) {
    OpenCellCommand command(m_controller, position);
    command.execute();
}

void BoardWidget::toggleFlag(const CellPosition& position) {
    ToggleFlagCommand command(m_controller, position);
    command.execute();
}

QString BoardWidget::modeText(const GameSettings& settings) const {
    if (settings.difficulty() == GameDifficulty::Beginner) {
        return "Новичок 9x9";
    }

    if (settings.difficulty() == GameDifficulty::Intermediate) {
        return "Любитель 16x16";
    }

    if (settings.difficulty() == GameDifficulty::Expert) {
        return "Эксперт 16x30";
    }

    return "Пользовательский";
}

QString BoardWidget::statusText(GameState state, GameResult result) const {
    if (state == GameState::NotStarted) {
        return "Готов к игре";
    }

    if (state == GameState::Running) {
        return "Игра идет";
    }

    if (state == GameState::Won || result == GameResult::Victory) {
        return "Победа";
    }

    if (state == GameState::Lost || result == GameResult::Defeat) {
        return "Поражение";
    }

    return "Готов к игре";
}

void BoardWidget::onBoardChanged(const GameBoard& board) {
    Q_UNUSED(board)
        updateAllButtons();
}

void BoardWidget::onCountersChanged(const MineCounter& mineCounter, int openedCells) {
    emit flagCountChanged(mineCounter.flaggedCells());
    emit openedCellCountChanged(openedCells);
}

void BoardWidget::onGameStatusChanged(GameState state, GameResult result) {
    emit gameStatusChanged(statusText(state, result));
}

void BoardWidget::onGameInfoChanged(const GameSettings& settings) {
    rebuildBoard();
    emit gameInfoChanged(settings.mineCount(), modeText(settings));
}

void BoardWidget::onGameEvent(const std::string& eventText) {
    emit gameEventAdded(QString::fromStdString(eventText));
}