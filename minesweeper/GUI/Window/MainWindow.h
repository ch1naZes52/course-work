#pragma once

#include "../../App/Command/OpenCellCommand.h"
#include "../../App/Command/RestartGameCommand.h"
#include "../../App/Command/ToggleFlagCommand.h"
#include "../../App/Controller/GameController.h"
#include "../../App/Observer/IGameObserver.h"
#include "../../Utils/Timer/GameTimer.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <vector>

class QLabel;
class QComboBox;
class QGridLayout;
class QListWidget;

class MainWindow : public QMainWindow, public IGameObserver {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* object, QEvent* event) override;

private:
    GameController m_controller;
    GameTimer m_timer;
    QTimer* m_qtimer;
    QLabel* m_minesLabel;
    QLabel* m_timeLabel;
    QLabel* m_openedLabel;
    QLabel* m_stateLabel;
    QComboBox* m_difficultyBox;
    QListWidget* m_events;
    QGridLayout* m_grid;
    std::vector<QPushButton*> m_buttons;

    void setupUi();
    void restart();
    void rebuildBoard();
    void updateView();
    void updateLabels();
    void styleButton(QPushButton* button, const Cell& cell);
    void openCell(int row, int column);
    void toggleFlag(int row, int column);
    GameDifficulty selectedDifficulty() const;
    QString stateText() const;
    QString timeText() const;

    void onGameChanged() override;
    void onGameEvent(const std::string& text) override;
};