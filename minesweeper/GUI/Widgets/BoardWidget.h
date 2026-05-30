#pragma once

#include <QWidget>
#include <vector>

#include "../../Core/Board/GameBoard.h"
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
    GameBoard m_board;
    QGridLayout* m_gridLayout;
    std::vector<CellButton*> m_buttons;

    void setupBoard();
    void clearBoard();
    void createButtons();
    void updateCounters();
    void updateButton(const CellPosition& position);
    void updateAllButtons();
    void openCell(const CellPosition& position);
    void toggleFlag(const CellPosition& position);
};