#pragma once

#include <QWidget>

#include "../../Core/Game/GameDifficulty.h"

class QLabel;
class QPushButton;
class QComboBox;
class QListWidget;

class StatusPanelWidget : public QWidget {
    Q_OBJECT

public:
    explicit StatusPanelWidget(QWidget* parent = nullptr);

public slots:
    void setPlacedFlags(int count);
    void setOpenedCells(int count);
    void setStatus(const QString& status);
    void setGameInfo(int totalMines, const QString& mode);
    void addEvent(const QString& eventText);
    void reset();

signals:
    void newGameRequested();
    void difficultySelected(GameDifficulty difficulty);

private:
    QLabel* m_minesLabel;
    QLabel* m_timerLabel;
    QLabel* m_openedLabel;
    QLabel* m_modeLabel;
    QLabel* m_statusLabel;
    QComboBox* m_difficultyComboBox;
    QPushButton* m_newGameButton;
    QListWidget* m_eventList;

    int m_totalMines;
    int m_placedFlags;
    int m_openedCells;
    QString m_status;
    QString m_mode;

    void setupLayout();
    void setupDifficultySelector();
    void updateLabels();
    GameDifficulty selectedDifficulty() const;
};