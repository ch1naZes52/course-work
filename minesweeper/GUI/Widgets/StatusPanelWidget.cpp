#include "StatusPanelWidget.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

StatusPanelWidget::StatusPanelWidget(QWidget* parent)
    : QWidget(parent),
    m_minesLabel(nullptr),
    m_timerLabel(nullptr),
    m_openedLabel(nullptr),
    m_modeLabel(nullptr),
    m_newGameButton(nullptr),
    m_totalMines(10),
    m_placedFlags(0),
    m_openedCells(0) {
    setupLayout();
    updateLabels();
}

void StatusPanelWidget::setPlacedFlags(int count) {
    m_placedFlags = count;
    updateLabels();
}

void StatusPanelWidget::setOpenedCells(int count) {
    m_openedCells = count;
    updateLabels();
}

void StatusPanelWidget::reset() {
    m_placedFlags = 0;
    m_openedCells = 0;
    updateLabels();
}

void StatusPanelWidget::setupLayout() {
    QFrame* panel = new QFrame(this);
    panel->setFrameShape(QFrame::StyledPanel);

    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    panelLayout->setContentsMargins(12, 10, 12, 10);
    panelLayout->setSpacing(16);

    m_minesLabel = new QLabel(panel);
    m_timerLabel = new QLabel(panel);
    m_openedLabel = new QLabel(panel);
    m_modeLabel = new QLabel(panel);
    m_newGameButton = new QPushButton("Новая игра", panel);

    m_minesLabel->setMinimumWidth(110);
    m_timerLabel->setMinimumWidth(90);
    m_openedLabel->setMinimumWidth(130);
    m_modeLabel->setMinimumWidth(120);

    panelLayout->addWidget(m_minesLabel);
    panelLayout->addWidget(m_timerLabel);
    panelLayout->addWidget(m_openedLabel);
    panelLayout->addStretch();
    panelLayout->addWidget(m_modeLabel);
    panelLayout->addWidget(m_newGameButton);

    QVBoxLayout* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->addWidget(panel);

    connect(m_newGameButton, &QPushButton::clicked, this, &StatusPanelWidget::newGameRequested);
}

void StatusPanelWidget::updateLabels() {
    m_minesLabel->setText(QString("Мины: %1").arg(m_totalMines - m_placedFlags));
    m_timerLabel->setText("Время: 000");
    m_openedLabel->setText(QString("Открыто: %1").arg(m_openedCells));
    m_modeLabel->setText("Новичок 9x9");
}