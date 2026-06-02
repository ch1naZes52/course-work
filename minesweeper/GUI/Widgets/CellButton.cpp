#include "CellButton.h"

#include <QMouseEvent>
#include <QSizePolicy>
#include <QString>

CellButton::CellButton(const CellPosition& position, QWidget* parent)
    : QPushButton(parent),
    m_position(position),
    m_locked(false) {
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

void CellButton::setLocked(bool locked) {
    m_locked = locked;
    updateCursor();
}

void CellButton::mousePressEvent(QMouseEvent* event) {
    if (m_locked) {
        return;
    }

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
    setMinimumSize(28, 28);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::NoFocus);
    updateCursor();
}

void CellButton::showClosed() {
    setText("");
    setStyleSheet("QPushButton { background-color: #bdbdbd; border: 1px solid #777777; border-radius: 2px; } QPushButton:hover { background-color: #cfcfcf; }");
}

void CellButton::showOpened(const Cell& cell) {
    if (cell.isMine()) {
        setText("✹");
        setStyleSheet("QPushButton { background-color: #d9534f; color: white; border: 1px solid #7a1f1c; border-radius: 2px; font-size: 18px; font-weight: bold; }");
        return;
    }

    if (cell.isNumber()) {
        setText(QString::number(cell.adjacentMines()));
        setStyleSheet(numberStyle(cell.adjacentMines()));
    }
    else {
        setText("");
        setStyleSheet("QPushButton { background-color: #e1e1e1; border: 1px solid #a6a6a6; border-radius: 2px; }");
    }
}

void CellButton::showFlagged() {
    setText("⚑");
    setStyleSheet("QPushButton { background-color: #f5d76e; color: #2f2f2f; border: 1px solid #8f8f8f; border-radius: 2px; font-size: 17px; font-weight: bold; }");
}

void CellButton::updateCursor() {
    if (m_locked) {
        setCursor(Qt::ArrowCursor);
    }
    else {
        setCursor(Qt::PointingHandCursor);
    }
}

QString CellButton::numberStyle(int number) const {
    if (number == 1) {
        return "QPushButton { background-color: #e1e1e1; color: #1d4ed8; border: 1px solid #a6a6a6; border-radius: 2px; font-size: 15px; font-weight: bold; }";
    }

    if (number == 2) {
        return "QPushButton { background-color: #e1e1e1; color: #15803d; border: 1px solid #a6a6a6; border-radius: 2px; font-size: 15px; font-weight: bold; }";
    }

    if (number == 3) {
        return "QPushButton { background-color: #e1e1e1; color: #b91c1c; border: 1px solid #a6a6a6; border-radius: 2px; font-size: 15px; font-weight: bold; }";
    }

    if (number == 4) {
        return "QPushButton { background-color: #e1e1e1; color: #3730a3; border: 1px solid #a6a6a6; border-radius: 2px; font-size: 15px; font-weight: bold; }";
    }

    return "QPushButton { background-color: #e1e1e1; color: #111827; border: 1px solid #a6a6a6; border-radius: 2px; font-size: 15px; font-weight: bold; }";
}