#pragma once

#include <QWidget>
#include <QString>
#include <vector>

#include "../../App/Command/OpenCellCommand.h"
#include "../../App/Command/RestartGameCommand.h"
#include "../../App/Command/ToggleFlagCommand.h"
#include "../../App/Controller/GameController.h"
#include "../../App/Observer/IGameObserver.h"
#include "../../Core/Game/GameDifficulty.h"
#include "../../Utils/Config/SettingsProvider.h"

class CellButton;
class QGridLayout;

class BoardWidget : public QWidget, public IGameObserver {
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);
    ~BoardWidget() override;

public slots:
    void resetPreview();
    void setDifficulty(GameDifficulty difficulty);

signals:
    void flagCountChanged(int count);
    void openedCellCountChanged(int count);
    void gameStatusChanged(const QString& status);
    void gameInfoChanged(int totalMines, const QString& mode);
    void gameEventAdded(const QString& eventText);

private:
    GameController m_controller;
    SettingsProvider m_settingsProvider;
    QGridLayout* m_gridLayout;
    std::vector<CellButton*> m_buttons;
    GameDifficulty m_currentDifficulty;

    void setupBoard();
    void rebuildBoard();
    void clearBoard();
    void createButtons();
    void updateButton(const CellPosition& position);
    void updateAllButtons();
    void openCell(const CellPosition& position);
    void toggleFlag(const CellPosition& position);
    QString statusText(GameState state, GameResult result) const;

    void onBoardChanged(const GameBoard& board) override;
    void onCountersChanged(const MineCounter& mineCounter, int openedCells) override;
    void onGameStatusChanged(GameState state, GameResult result) override;
    void onGameInfoChanged(const GameSettings& settings) override;
    void onGameEvent(const std::string& eventText) override;
};