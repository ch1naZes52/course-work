#pragma once

#include "../Analyzer/GameAnalyzer.h"
#include "../Factory/GameFactory.h"
#include "../Flag/FlagManager.h"
#include "../Opener/CellOpener.h"
#include "../../Core/Board/GameBoard.h"
#include "../../Core/Game/GameResult.h"
#include "../../Core/Game/GameSettings.h"
#include "../../Core/Game/GameState.h"
#include "../../Core/Mine/MineCounter.h"
#include "../../Utils/Generator/RandomMineGenerator.h"

class GameController {
public:
    GameController();

    const GameSettings& settings() const;
    const GameBoard& board() const;
    const MineCounter& mineCounter() const;
    GameState state() const;
    GameResult result() const;
    bool minesGenerated() const;

    void restart(GameDifficulty difficulty);
    bool openCell(const CellPosition& position);
    bool toggleFlag(const CellPosition& position);

private:
    GameFactory m_factory;
    GameSettings m_settings;
    GameBoard m_board;
    MineCounter m_mineCounter;
    RandomMineGenerator m_mineGenerator;
    GameAnalyzer m_gameAnalyzer;
    CellOpener m_cellOpener;
    FlagManager m_flagManager;
    GameState m_state;
    GameResult m_result;
    bool m_minesGenerated;

    void generateMinesIfNeeded(const CellPosition& firstMove);
    void analyzeGameState();
    void finishGame(GameResult result);
};