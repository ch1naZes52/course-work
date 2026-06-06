#pragma once

class GameTimer {
public:
    GameTimer();
    int seconds() const;
    void start();
    void stop();
    void reset();
    void tick();

private:
    int m_seconds;
    bool m_running;
};