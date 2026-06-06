#pragma once

#include "../Analyzer/GameAnalyzer.h"
#include "../Factory/GameFactory.h"
#include "../Flag/FlagManager.h"
#include "../Observer/IGameObserver.h"
#include "../Opener/CellOpener.h"
#include "../../Core/Game/GameState.h"
#include "../../Utils/Generator/RandomMineGenerator.h"

#include <string>

class GameController {
public:
    GameController();
    const GameSettings& settings() const;
    const GameBoard& board() const;
    const MineCounter& counter() const;
    GameState state() const;
    void setObserver(IGameObserver* observer);
    void restart(GameDifficulty difficulty);
    bool openCell(const CellPosition& position);
    bool toggleFlag(const CellPosition& position);

private:
    GameFactory m_factory;
    GameSettings m_settings;
    GameBoard m_board;
    MineCounter m_counter;
    RandomMineGenerator m_generator;
    GameAnalyzer m_analyzer;
    CellOpener m_opener;
    FlagManager m_flags;
    GameState m_state;
    bool m_generated;
    IGameObserver* m_observer;

    void generate(const CellPosition& firstMove);
    void finish(GameResult result);
    void notify();
    void event(const std::string& text);
    std::string positionText(const CellPosition& position) const;
};