#include "BoardWidget.h"
#include "CellButton.h"

#include <QGridLayout>

BoardWidget::BoardWidget(QWidget* parent)
    : QWidget(parent),
    m_settings(GameSettings::beginner()),
    m_board(m_settings.boardSize()),
    m_gridLayout(nullptr) {
    setupBoard();
}

void BoardWidget::resetPreview() {
    m_board.reset();
    updateAllButtons();
    updateCounters();
}

void BoardWidget::setupBoard() {
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    m_gridLayout->setSpacing(2);

    createButtons();
    updateAllButtons();
    updateCounters();
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

    BoardSize size = m_settings.boardSize();

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
    emit flagCountChanged(m_board.flaggedCellCount());
    emit openedCellCountChanged(m_board.openedCellCount());
}

void BoardWidget::updateButton(const CellPosition& position) {
    int index = position.row() * m_settings.boardSize().columns() + position.column();

    if (index < 0 || index >= static_cast<int>(m_buttons.size())) {
        return;
    }

    m_buttons[index]->updateFromCell(m_board.cellAt(position));
}

void BoardWidget::updateAllButtons() {
    for (CellButton* button : m_buttons) {
        button->updateFromCell(m_board.cellAt(button->position()));
    }
}

void BoardWidget::openCell(const CellPosition& position) {
    if (!m_board.isValidPosition(position)) {
        return;
    }

    Cell& cell = m_board.cellAt(position);

    if (!cell.open()) {
        return;
    }

    updateButton(position);
    updateCounters();
}

void BoardWidget::toggleFlag(const CellPosition& position) {
    if (!m_board.isValidPosition(position)) {
        return;
    }

    Cell& cell = m_board.cellAt(position);

    if (!cell.toggleFlag()) {
        return;
    }

    updateButton(position);
    updateCounters();
}