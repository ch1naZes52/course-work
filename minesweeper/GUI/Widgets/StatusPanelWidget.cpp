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
    m_hintLabel(nullptr),
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

    while (m_eventList->count() > 7) {
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
    panel->setObjectName("statusPanel");
    panel->setFrameShape(QFrame::NoFrame);
    panel->setStyleSheet(
        "#statusPanel {"
        " background-color: #20242c;"
        " border: 1px solid #3a3f4b;"
        " border-radius: 8px;"
        "}"
        "QLabel {"
        " color: #f3f4f6;"
        " background-color: transparent;"
        " border: none;"
        "}"
        "QLabel#infoLabel {"
        " color: #111827;"
        " background-color: #f9fafb;"
        " border: 1px solid #d1d5db;"
        " border-radius: 5px;"
        " padding: 5px 8px;"
        " font-weight: bold;"
        "}"
        "QLabel#hintLabel {"
        " color: #cbd5e1;"
        " font-size: 12px;"
        "}"
        "QLabel#eventTitleLabel {"
        " color: #f9fafb;"
        " font-weight: bold;"
        "}"
        "QComboBox {"
        " color: #111827;"
        " background-color: #ffffff;"
        " border: 1px solid #9ca3af;"
        " border-radius: 5px;"
        " padding: 5px 8px;"
        " font-weight: bold;"
        "}"
        "QComboBox::drop-down {"
        " width: 24px;"
        " border-left: 1px solid #d1d5db;"
        "}"
        "QComboBox QAbstractItemView {"
        " color: #111827;"
        " background-color: #ffffff;"
        " selection-background-color: #dbeafe;"
        " selection-color: #111827;"
        " border: 1px solid #9ca3af;"
        "}"
        "QPushButton {"
        " color: #111827;"
        " background-color: #ffffff;"
        " border: 1px solid #9ca3af;"
        " border-radius: 5px;"
        " padding: 6px 14px;"
        " font-weight: bold;"
        "}"
        "QPushButton:hover {"
        " background-color: #e5e7eb;"
        "}"
        "QListWidget {"
        " color: #111827;"
        " background-color: #ffffff;"
        " border: 1px solid #d1d5db;"
        " border-radius: 5px;"
        " padding: 4px;"
        "}"
        "QListWidget::item {"
        " padding: 4px;"
        "}"
    );

    QVBoxLayout* panelRootLayout = new QVBoxLayout(panel);
    panelRootLayout->setContentsMargins(14, 12, 14, 12);
    panelRootLayout->setSpacing(10);

    QHBoxLayout* infoLayout = new QHBoxLayout();
    infoLayout->setSpacing(10);

    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->setSpacing(10);

    m_minesLabel = new QLabel(panel);
    m_timerLabel = new QLabel(panel);
    m_openedLabel = new QLabel(panel);
    m_modeLabel = new QLabel(panel);
    m_statusLabel = new QLabel(panel);
    m_hintLabel = new QLabel("ЛКМ — открыть клетку, ПКМ — поставить флаг", panel);
    m_difficultyComboBox = new QComboBox(panel);
    m_newGameButton = new QPushButton("Новая игра", panel);
    m_eventList = new QListWidget(panel);

    m_minesLabel->setObjectName("infoLabel");
    m_timerLabel->setObjectName("infoLabel");
    m_openedLabel->setObjectName("infoLabel");
    m_modeLabel->setObjectName("infoLabel");
    m_statusLabel->setObjectName("infoLabel");
    m_hintLabel->setObjectName("hintLabel");

    m_minesLabel->setMinimumWidth(110);
    m_timerLabel->setMinimumWidth(110);
    m_openedLabel->setMinimumWidth(120);
    m_modeLabel->setMinimumWidth(140);
    m_statusLabel->setMinimumWidth(130);
    m_hintLabel->setMinimumWidth(290);
    m_difficultyComboBox->setMinimumWidth(150);
    m_newGameButton->setMinimumWidth(130);
    m_eventList->setMaximumHeight(132);

    m_newGameButton->setCursor(Qt::PointingHandCursor);
    m_difficultyComboBox->setCursor(Qt::PointingHandCursor);

    setupDifficultySelector();

    infoLayout->addWidget(m_minesLabel);
    infoLayout->addWidget(m_timerLabel);
    infoLayout->addWidget(m_openedLabel);
    infoLayout->addWidget(m_modeLabel);
    infoLayout->addStretch();
    infoLayout->addWidget(m_statusLabel);

    controlLayout->addWidget(m_difficultyComboBox);
    controlLayout->addWidget(m_newGameButton);
    controlLayout->addWidget(m_hintLabel);
    controlLayout->addStretch();

    QLabel* eventTitleLabel = new QLabel("Журнал событий", panel);
    eventTitleLabel->setObjectName("eventTitleLabel");

    panelRootLayout->addLayout(infoLayout);
    panelRootLayout->addLayout(controlLayout);
    panelRootLayout->addWidget(eventTitleLabel);
    panelRootLayout->addWidget(m_eventList);

    QVBoxLayout* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->addWidget(panel);

    connect(m_newGameButton, &QPushButton::clicked, this, &StatusPanelWidget::newGameRequested);

    connect(m_difficultyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() {
        reset();
        emit difficultySelected(selectedDifficulty());
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
    updateStatusStyle();
}

void StatusPanelWidget::updateStatusStyle() {
    if (m_status == "Игра идет") {
        m_statusLabel->setStyleSheet(
            "QLabel#infoLabel {"
            " color: #1d4ed8;"
            " background-color: #dbeafe;"
            " border: 1px solid #93c5fd;"
            " border-radius: 5px;"
            " padding: 5px 8px;"
            " font-weight: bold;"
            "}"
        );
        return;
    }

    if (m_status == "Победа") {
        m_statusLabel->setStyleSheet(
            "QLabel#infoLabel {"
            " color: #166534;"
            " background-color: #dcfce7;"
            " border: 1px solid #86efac;"
            " border-radius: 5px;"
            " padding: 5px 8px;"
            " font-weight: bold;"
            "}"
        );
        return;
    }

    if (m_status == "Поражение") {
        m_statusLabel->setStyleSheet(
            "QLabel#infoLabel {"
            " color: #991b1b;"
            " background-color: #fee2e2;"
            " border: 1px solid #fca5a5;"
            " border-radius: 5px;"
            " padding: 5px 8px;"
            " font-weight: bold;"
            "}"
        );
        return;
    }

    m_statusLabel->setStyleSheet(
        "QLabel#infoLabel {"
        " color: #374151;"
        " background-color: #f9fafb;"
        " border: 1px solid #d1d5db;"
        " border-radius: 5px;"
        " padding: 5px 8px;"
        " font-weight: bold;"
        "}"
    );
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