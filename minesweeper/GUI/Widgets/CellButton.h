#pragma once

#include <QPushButton>

#include "../../Core/Cell/Cell.h"

class CellButton : public QPushButton {
    Q_OBJECT

public:
    explicit CellButton(const CellPosition& position, QWidget* parent = nullptr);

    const CellPosition& position() const;

    void updateFromCell(const Cell& cell);

signals:
    void openRequested(const CellPosition& position);
    void flagRequested(const CellPosition& position);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    CellPosition m_position;

    void setupView();
    void showClosed();
    void showOpened(const Cell& cell);
    void showFlagged();
};