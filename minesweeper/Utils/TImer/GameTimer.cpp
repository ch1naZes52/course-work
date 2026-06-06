#include "GameTimer.h"

GameTimer::GameTimer() : m_seconds(0), m_running(false) {}

int GameTimer::seconds() const {
    return m_seconds;
}

void GameTimer::start() {
    m_running = true;
}

void GameTimer::stop() {
    m_running = false;
}

void GameTimer::reset() {
    m_seconds = 0;
    m_running = false;
}

void GameTimer::tick() {
    if (m_running) {
        ++m_seconds;
    }
}