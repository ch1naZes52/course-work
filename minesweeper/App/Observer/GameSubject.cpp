#include "GameSubject.h"

#include <algorithm>

void GameSubject::addObserver(IGameObserver* observer) {
    if (observer == nullptr) {
        return;
    }

    auto iterator = std::find(m_observers.begin(), m_observers.end(), observer);

    if (iterator != m_observers.end()) {
        return;
    }

    m_observers.push_back(observer);
}

void GameSubject::removeObserver(IGameObserver* observer) {
    auto iterator = std::remove(m_observers.begin(), m_observers.end(), observer);
    m_observers.erase(iterator, m_observers.end());
}

void GameSubject::notifyBoardChanged(const GameBoard& board) {
    for (IGameObserver* observer : m_observers) {
        observer->onBoardChanged(board);
    }
}

void GameSubject::notifyCountersChanged(const MineCounter& mineCounter, int openedCells) {
    for (IGameObserver* observer : m_observers) {
        observer->onCountersChanged(mineCounter, openedCells);
    }
}

void GameSubject::notifyGameStatusChanged(GameState state, GameResult result) {
    for (IGameObserver* observer : m_observers) {
        observer->onGameStatusChanged(state, result);
    }
}

void GameSubject::notifyGameInfoChanged(const GameSettings& settings) {
    for (IGameObserver* observer : m_observers) {
        observer->onGameInfoChanged(settings);
    }
}

void GameSubject::notifyGameEvent(const std::string& eventText) {
    for (IGameObserver* observer : m_observers) {
        observer->onGameEvent(eventText);
    }
}