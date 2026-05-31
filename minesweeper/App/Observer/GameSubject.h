#pragma once

#include "IGameObserver.h"

#include <vector>

class GameSubject {
public:
    void addObserver(IGameObserver* observer);
    void removeObserver(IGameObserver* observer);

protected:
    void notifyBoardChanged(const GameBoard& board);
    void notifyCountersChanged(const MineCounter& mineCounter, int openedCells);
    void notifyGameStatusChanged(GameState state, GameResult result);
    void notifyGameInfoChanged(const GameSettings& settings);
    void notifyGameEvent(const std::string& eventText);

private:
    std::vector<IGameObserver*> m_observers;
};