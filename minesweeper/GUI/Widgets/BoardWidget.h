#pragma once

#include <QWidget>
#include <QString>
#include <vector>

#include "../../App/Command/OpenCellCommand.h"
#include "../../App/Command/RestartGameCommand.h"
#include "../../App/Command/ToggleFlagCommand.h"
#include "../../App/Controller/GameController.h"
#include "../../Core/Game/GameDifficulty.h"

class CellButton;
class QGridLayout;

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);

public slots:
    void resetPreview();
    void setDifficulty(GameDifficulty difficulty);

signals:
    void flagCountChanged(int count);
    void openedCellCountChanged(int count);
    void gameStatusChanged(const QString& status);
    void gameInfoChanged(int totalMines, const QString& mode);

private:
    GameController m_controller;
    QGridLayout* m_gridLayout;
    std::vector<CellButton*> m_buttons;
    GameDifficulty m_currentDifficulty;

    void setupBoard();
    void rebuildBoard();
    void clearBoard();
    void createButtons();
    void updateCounters();
    void updateButton(const CellPosition& position);
    void updateAllButtons();
    void openCell(const CellPosition& position);
    void toggleFlag(const CellPosition& position);
    void updateStatus();
    QString currentModeText() const;
};