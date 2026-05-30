#pragma once

#include <QWidget>
#include <vector>

#include "../../Core/Game/GameSettings.h"

class CellButton;
class QGridLayout;

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);

public slots:
    void resetPreview();

signals:
    void flagCountChanged(int count);
    void openedCellCountChanged(int count);

private:
    GameSettings m_settings;
    QGridLayout* m_gridLayout;
    std::vector<CellButton*> m_buttons;
    int m_flagCount;
    int m_openedCellCount;

    void setupBoard();
    void clearBoard();
    void createButtons();
    void updateCounters();
    void handleCellOpened(CellButton* button);
    void handleCellFlagChanged(CellButton* button);
};