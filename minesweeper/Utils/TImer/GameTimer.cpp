#include "GameTimer.h"

GameTimer::GameTimer(QObject* parent)
    : QObject(parent),
    m_timer(nullptr),
    m_seconds(0),
    m_running(false) {
    setupTimer();
}

int GameTimer::seconds() const {
    return m_seconds;
}

bool GameTimer::isRunning() const {
    return m_running;
}

void GameTimer::start() {
    if (m_running) {
        return;
    }

    m_running = true;
    m_timer->start(1000);
}

void GameTimer::stop() {
    if (!m_running) {
        return;
    }

    m_running = false;
    m_timer->stop();
}

void GameTimer::reset() {
    stop();
    m_seconds = 0;
    emit secondsChanged(m_seconds);
}

void GameTimer::setupTimer() {
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, [this]() {
        ++m_seconds;
        emit secondsChanged(m_seconds);
        });
}