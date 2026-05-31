#include "BoardWidget.h"
#include "CellButton.h"

#include <QGridLayout>

BoardWidget::BoardWidget(QWidget* parent)
    : QWidget(parent),
    m_controller(),
    m_gridLayout(nullptr),
    m_currentDifficulty(GameDifficulty::Beginner) {
    setupBoard();
}

void BoardWidget::resetPreview() {
    RestartGameCommand command(m_controller, m_currentDifficulty);
    command.execute();

    rebuildBoard();
    updateCounters();
    updateStatus();

    emit gameInfoChanged(m_controller.settings().mineCount(), currentModeText());
}

void BoardWidget::setDifficulty(GameDifficulty difficulty) {
    m_currentDifficulty = difficulty;

    RestartGameCommand command(m_controller, m_currentDifficulty);
    command.execute();

    rebuildBoard();
    updateCounters();
    updateStatus();

    emit gameInfoChanged(m_controller.settings().mineCount(), currentModeText());
}

void BoardWidget::setupBoard() {
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    m_gridLayout->setSpacing(2);

    createButtons();
    updateAllButtons();
    updateCounters();
    updateStatus();

    emit gameInfoChanged(m_controller.settings().mineCount(), currentModeText());
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

void BoardWidget::updateCounters() {
    emit flagCountChanged(m_controller.mineCounter().flaggedCells());
    emit openedCellCountChanged(m_controller.board().openedCellCount());
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

    if (!command.execute()) {
        updateStatus();
        return;
    }

    updateAllButtons();
    updateCounters();
    updateStatus();
}

void BoardWidget::toggleFlag(const CellPosition& position) {
    ToggleFlagCommand command(m_controller, position);

    if (!command.execute()) {
        updateStatus();
        return;
    }

    updateButton(position);
    updateCounters();
    updateStatus();
}

void BoardWidget::updateStatus() {
    if (m_controller.state() == GameState::NotStarted) {
        emit gameStatusChanged("Готов к игре");
        return;
    }

    if (m_controller.state() == GameState::Running) {
        emit gameStatusChanged("Игра идет");
        return;
    }

    if (m_controller.state() == GameState::Won) {
        emit gameStatusChanged("Победа");
        return;
    }

    if (m_controller.state() == GameState::Lost) {
        emit gameStatusChanged("Поражение");
        return;
    }
}

QString BoardWidget::currentModeText() const {
    if (m_currentDifficulty == GameDifficulty::Beginner) {
        return "Новичок 9x9";
    }

    if (m_currentDifficulty == GameDifficulty::Intermediate) {
        return "Любитель 16x16";
    }

    if (m_currentDifficulty == GameDifficulty::Expert) {
        return "Эксперт 16x30";
    }

    return "Пользовательский";
}