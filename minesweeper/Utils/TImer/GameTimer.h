#pragma once

#include <QObject>
#include <QTimer>

class GameTimer : public QObject {
    Q_OBJECT

public:
    explicit GameTimer(QObject* parent = nullptr);

    int seconds() const;
    bool isRunning() const;

public slots:
    void start();
    void stop();
    void reset();

signals:
    void secondsChanged(int seconds);

private:
    QTimer* m_timer;
    int m_seconds;
    bool m_running;

    void setupTimer();
};