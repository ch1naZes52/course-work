#include "StatusPanelWidget.h"

#include <QComboBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>

StatusPanelWidget::StatusPanelWidget(QWidget* parent)
    : QWidget(parent),
    m_minesLabel(nullptr),
    m_timerLabel(nullptr),
    m_openedLabel(nullptr),
    m_modeLabel(nullptr),
    m_statusLabel(nullptr),
    m_difficultyComboBox(nullptr),
    m_newGameButton(nullptr),
    m_eventList(nullptr),
    m_totalMines(10),
    m_placedFlags(0),
    m_openedCells(0),
    m_status("Готов к игре"),
    m_mode("Новичок 9x9") {
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

void StatusPanelWidget::setStatus(const QString& status) {
    m_status = status;
    updateLabels();
}

void StatusPanelWidget::setGameInfo(int totalMines, const QString& mode) {
    m_totalMines = totalMines;
    m_mode = mode;
    updateLabels();
}

void StatusPanelWidget::addEvent(const QString& eventText) {
    m_eventList->insertItem(0, eventText);

    while (m_eventList->count() > 6) {
        delete m_eventList->takeItem(m_eventList->count() - 1);
    }
}

void StatusPanelWidget::reset() {
    m_placedFlags = 0;
    m_openedCells = 0;
    m_status = "Готов к игре";
    m_eventList->clear();
    updateLabels();
}

void StatusPanelWidget::setupLayout() {
    QFrame* panel = new QFrame(this);
    panel->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout* panelRootLayout = new QVBoxLayout(panel);
    panelRootLayout->setContentsMargins(12, 10, 12, 10);
    panelRootLayout->setSpacing(8);

    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->setSpacing(10);

    m_minesLabel = new QLabel(panel);
    m_timerLabel = new QLabel(panel);
    m_openedLabel = new QLabel(panel);
    m_modeLabel = new QLabel(panel);
    m_statusLabel = new QLabel(panel);
    m_difficultyComboBox = new QComboBox(panel);
    m_newGameButton = new QPushButton("Новая игра", panel);
    m_eventList = new QListWidget(panel);

    m_minesLabel->setMinimumWidth(80);
    m_timerLabel->setMinimumWidth(80);
    m_openedLabel->setMinimumWidth(95);
    m_modeLabel->setMinimumWidth(105);
    m_statusLabel->setMinimumWidth(90);
    m_difficultyComboBox->setMinimumWidth(110);
    m_eventList->setMaximumHeight(118);

    setupDifficultySelector();

    topLayout->addWidget(m_minesLabel);
    topLayout->addWidget(m_timerLabel);
    topLayout->addWidget(m_openedLabel);
    topLayout->addWidget(m_modeLabel);
    topLayout->addWidget(m_difficultyComboBox);
    topLayout->addStretch();
    topLayout->addWidget(m_statusLabel);
    topLayout->addWidget(m_newGameButton);

    QLabel* eventTitleLabel = new QLabel("Журнал событий", panel);

    panelRootLayout->addLayout(topLayout);
    panelRootLayout->addWidget(eventTitleLabel);
    panelRootLayout->addWidget(m_eventList);

    QVBoxLayout* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->addWidget(panel);

    connect(m_newGameButton, &QPushButton::clicked, this, &StatusPanelWidget::newGameRequested);

    connect(m_difficultyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() {
        m_placedFlags = 0;
        m_openedCells = 0;
        m_status = "Готов к игре";
        m_eventList->clear();
        emit difficultySelected(selectedDifficulty());
        updateLabels();
        });
}

void StatusPanelWidget::setupDifficultySelector() {
    m_difficultyComboBox->addItem("Новичок");
    m_difficultyComboBox->addItem("Любитель");
    m_difficultyComboBox->addItem("Эксперт");
}

void StatusPanelWidget::updateLabels() {
    m_minesLabel->setText(QString("Мины: %1").arg(m_totalMines - m_placedFlags));
    m_timerLabel->setText("Время: 000");
    m_openedLabel->setText(QString("Открыто: %1").arg(m_openedCells));
    m_modeLabel->setText(m_mode);
    m_statusLabel->setText(m_status);
}

GameDifficulty StatusPanelWidget::selectedDifficulty() const {
    if (m_difficultyComboBox->currentIndex() == 1) {
        return GameDifficulty::Intermediate;
    }

    if (m_difficultyComboBox->currentIndex() == 2) {
        return GameDifficulty::Expert;
    }

    return GameDifficulty::Beginner;
}