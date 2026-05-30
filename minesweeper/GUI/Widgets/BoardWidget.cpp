#include "BoardWidget.h"
#include "CellButton.h"

#include <QGridLayout>

BoardWidget::BoardWidget(QWidget* parent)
    : QWidget(parent),
    m_settings(GameSettings::beginner()),
    m_gridLayout(nullptr),
    m_flagCount(0),
    m_openedCellCount(0) {
    setupBoard();
}

void BoardWidget::resetPreview() {
    m_flagCount = 0;
    m_openedCellCount = 0;

    for (CellButton* button : m_buttons) {
        button->resetPreview();
    }

    updateCounters();
}

void BoardWidget::setupBoard() {
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setContentsMargins(0, 0, 0, 0);
    m_gridLayout->setSpacing(2);

    createButtons();
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
            CellButton* button = new CellButton(CellPosition(row, column), this);

            connect(button, &CellButton::opened, this, [this, button]() {
                handleCellOpened(button);
                });

            connect(button, &CellButton::flagChanged, this, [this, button]() {
                handleCellFlagChanged(button);
                });

            m_buttons.push_back(button);
            m_gridLayout->addWidget(button, row, column);
        }
    }
}

void BoardWidget::updateCounters() {
    emit flagCountChanged(m_flagCount);
    emit openedCellCountChanged(m_openedCellCount);
}

void BoardWidget::handleCellOpened(CellButton* button) {
    if (!button->isPreviewOpened()) {
        return;
    }

    ++m_openedCellCount;
    updateCounters();
}

void BoardWidget::handleCellFlagChanged(CellButton* button) {
    if (button->isPreviewFlagged()) {
        ++m_flagCount;
    }
    else {
        --m_flagCount;
    }

    updateCounters();
}