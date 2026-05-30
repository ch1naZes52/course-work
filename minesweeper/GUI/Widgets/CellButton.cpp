#include "CellButton.h"

#include <QMouseEvent>

CellButton::CellButton(const CellPosition& position, QWidget* parent)
    : QPushButton(parent),
    m_position(position),
    m_previewOpened(false),
    m_previewFlagged(false) {
    setupView();
    updateView();
}

const CellPosition& CellButton::position() const {
    return m_position;
}

bool CellButton::isPreviewOpened() const {
    return m_previewOpened;
}

bool CellButton::isPreviewFlagged() const {
    return m_previewFlagged;
}

void CellButton::resetPreview() {
    m_previewOpened = false;
    m_previewFlagged = false;
    setEnabled(true);
    updateView();
}

void CellButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        openPreview();
        return;
    }

    if (event->button() == Qt::RightButton) {
        toggleFlagPreview();
        return;
    }

    QPushButton::mousePressEvent(event);
}

void CellButton::setupView() {
    setMinimumSize(42, 42);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::NoFocus);
}

void CellButton::openPreview() {
    if (m_previewOpened || m_previewFlagged) {
        return;
    }

    m_previewOpened = true;
    updateView();
    emit opened();
}

void CellButton::toggleFlagPreview() {
    if (m_previewOpened) {
        return;
    }

    m_previewFlagged = !m_previewFlagged;
    updateView();
    emit flagChanged();
}

void CellButton::updateView() {
    if (m_previewOpened) {
        setText(QString("%1:%2").arg(m_position.row() + 1).arg(m_position.column() + 1));
        setStyleSheet("QPushButton { background-color: #d6d6d6; border: 1px solid #9e9e9e; font-size: 11px; }");
        return;
    }

    if (m_previewFlagged) {
        setText("⚑");
        setStyleSheet("QPushButton { background-color: #f5d76e; border: 1px solid #8f8f8f; font-size: 20px; font-weight: bold; }");
        return;
    }

    setText("");
    setStyleSheet("QPushButton { background-color: #bdbdbd; border: 1px solid #777777; } QPushButton:hover { background-color: #cfcfcf; }");
}