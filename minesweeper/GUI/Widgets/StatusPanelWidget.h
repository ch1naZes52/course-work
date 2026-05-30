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
    void reset();

signals:
    void newGameRequested();

private:
    QLabel* m_minesLabel;
    QLabel* m_timerLabel;
    QLabel* m_openedLabel;
    QLabel* m_modeLabel;
    QPushButton* m_newGameButton;

    int m_totalMines;
    int m_placedFlags;
    int m_openedCells;

    void setupLayout();
    void updateLabels();
};