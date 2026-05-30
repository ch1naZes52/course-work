#pragma once

#include <QPushButton>

#include "../../Core/Cell/CellPosition.h"

class CellButton : public QPushButton {
    Q_OBJECT

public:
    explicit CellButton(const CellPosition& position, QWidget* parent = nullptr);

    const CellPosition& position() const;
    bool isPreviewOpened() const;
    bool isPreviewFlagged() const;

    void resetPreview();

signals:
    void opened();
    void flagChanged();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    CellPosition m_position;
    bool m_previewOpened;
    bool m_previewFlagged;

    void setupView();
    void openPreview();
    void toggleFlagPreview();
    void updateView();
};