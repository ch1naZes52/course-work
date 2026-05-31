#pragma once

#include <QWidget>

class QLabel;
class QPushButton;

class StatusPanelWidget : public QWidget {
    Q_OBJECT

public:
    explicit StatusPanelWidget(QWidget* parent = nullptr);

public slots:
    void setPlacedFlags(int count);
    void setOpenedCells(int count);
    void setStatus(const QString& status);
    void reset();

signals:
    void newGameRequested();

private:
    QLabel* m_minesLabel;
    QLabel* m_timerLabel;
    QLabel* m_openedLabel;
    QLabel* m_modeLabel;
    QLabel* m_statusLabel;
    QPushButton* m_newGameButton;

    int m_totalMines;
    int m_placedFlags;
    int m_openedCells;
    QString m_status;

    void setupLayout();
    void updateLabels();
};