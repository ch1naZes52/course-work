#pragma once

#include <QWidget>
#include <vector>

#include "../../App/Analyzer/GameAnalyzer.h"
#include "../../Core/Board/GameBoard.h"
#include "../../Core/Game/GameSettings.h"
#include "../../Utils/Generator/RandomMineGenerator.h"

class CellButton;
class QGridLayout;

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);

public slots:
    void resetPreview();

signals:
    void flagCountChanged(int count);
    void openedCellCountChanged(int count);
    void gameStatusChanged(const QString& status);

private:
    GameSettings m_settings;
    GameBoard m_board;
    RandomMineGenerator m_mineGenerator;
    GameAnalyzer m_gameAnalyzer;
    QGridLayout* m_gridLayout;
    std::vector<CellButton*> m_buttons;
    bool m_minesGenerated;
    bool m_gameFinished;

    void setupBoard();
    void clearBoard();
    void createButtons();
    void updateCounters();
    void updateButton(const CellPosition& position);
    void updateAllButtons();
    void openCell(const CellPosition& position);
    void toggleFlag(const CellPosition& position);
    void analyzeGameState();
    void finishGame(GameResult result);
};