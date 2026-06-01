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
    m_gameTimer(nullptr),
    m_totalMines(10),
    m_placedFlags(0),
    m_openedCells(0),
    m_elapsedSeconds(0),
    m_status("Готов к игре"),
    m_mode("Новичок 9x9") {
    setupLayout();
    setupTimer();
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
    updateTimerByStatus();
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
    m_elapsedSeconds = 0;
    m_status = "Готов к игре";
    m_eventList->clear();
    m_gameTimer->reset();
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
        m_elapsedSeconds = 0;
        m_status = "Готов к игре";
        m_eventList->clear();
        m_gameTimer->reset();
        emit difficultySelected(selectedDifficulty());
        updateLabels();
        });
}

void StatusPanelWidget::setupDifficultySelector() {
    for (GameDifficulty difficulty : m_settingsProvider.difficulties()) {
        m_difficultyComboBox->addItem(m_settingsProvider.difficultyName(difficulty));
    }
}

void StatusPanelWidget::setupTimer() {
    m_gameTimer = new GameTimer(this);

    connect(m_gameTimer, &GameTimer::secondsChanged, this, [this](int seconds) {
        m_elapsedSeconds = seconds;
        updateLabels();
        });
}

void StatusPanelWidget::updateLabels() {
    m_minesLabel->setText(QString("Мины: %1").arg(m_totalMines - m_placedFlags));
    m_timerLabel->setText(QString("Время: %1").arg(formattedTime()));
    m_openedLabel->setText(QString("Открыто: %1").arg(m_openedCells));
    m_modeLabel->setText(m_mode);
    m_statusLabel->setText(m_status);
}

void StatusPanelWidget::updateTimerByStatus() {
    if (m_status == "Игра идет") {
        m_gameTimer->start();
        return;
    }

    if (m_status == "Победа" || m_status == "Поражение") {
        m_gameTimer->stop();
        return;
    }

    if (m_status == "Готов к игре") {
        m_gameTimer->reset();
        return;
    }
}

QString StatusPanelWidget::formattedTime() const {
    if (m_elapsedSeconds < 10) {
        return QString("00%1").arg(m_elapsedSeconds);
    }

    if (m_elapsedSeconds < 100) {
        return QString("0%1").arg(m_elapsedSeconds);
    }

    return QString::number(m_elapsedSeconds);
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