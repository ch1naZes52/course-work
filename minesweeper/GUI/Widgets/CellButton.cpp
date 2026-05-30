#include "CellButton.h"

#include <QMouseEvent>
#include <QString>
#include <QSizePolicy>

CellButton::CellButton(const CellPosition& position, QWidget* parent)
    : QPushButton(parent),
    m_position(position) {
    setupView();
    showClosed();
}

const CellPosition& CellButton::position() const {
    return m_position;
}

void CellButton::updateFromCell(const Cell& cell) {
    if (cell.isOpened()) {
        showOpened(cell);
        return;
    }

    if (cell.isFlagged()) {
        showFlagged();
        return;
    }

    showClosed();
}

void CellButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit openRequested(m_position);
        return;
    }

    if (event->button() == Qt::RightButton) {
        emit flagRequested(m_position);
        return;
    }

    QPushButton::mousePressEvent(event);
}

void CellButton::setupView() {
    setMinimumSize(42, 42);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::NoFocus);
}

void CellButton::showClosed() {
    setEnabled(true);
    setText("");
    setStyleSheet("QPushButton { background-color: #bdbdbd; border: 1px solid #777777; } QPushButton:hover { background-color: #cfcfcf; }");
}

void CellButton::showOpened(const Cell& cell) {
    setEnabled(true);

    if (cell.isNumber()) {
        setText(QString::number(cell.adjacentMines()));
    }
    else {
        setText("");
    }

    setStyleSheet("QPushButton { background-color: #d6d6d6; border: 1px solid #9e9e9e; font-size: 18px; font-weight: bold; }");
}

void CellButton::showFlagged() {
    setEnabled(true);
    setText("⚑");
    setStyleSheet("QPushButton { background-color: #f5d76e; border: 1px solid #8f8f8f; font-size: 20px; font-weight: bold; }");
}