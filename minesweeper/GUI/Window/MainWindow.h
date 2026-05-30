#pragma once

#include <QMainWindow>

class BoardWidget;
class StatusPanelWidget;

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    StatusPanelWidget* m_statusPanel;
    BoardWidget* m_boardWidget;

    void setupWindow();
    void setupCentralWidget();
    void setupConnections();
};