#include "MainWindow.h"
#include "../Widgets/BoardWidget.h"
#include "../Widgets/StatusPanelWidget.h"

#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_statusPanel(nullptr),
    m_boardWidget(nullptr) {
    setupWindow();
    setupCentralWidget();
    setupConnections();
}

void MainWindow::setupWindow() {
    setWindowTitle("Minesweeper");
    setMinimumSize(520, 620);
    resize(560, 660);
}

void MainWindow::setupCentralWidget() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    m_statusPanel = new StatusPanelWidget(centralWidget);
    m_boardWidget = new BoardWidget(centralWidget);

    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);
    mainLayout->addWidget(m_statusPanel);
    mainLayout->addWidget(m_boardWidget, 1);

    setCentralWidget(centralWidget);
}

void MainWindow::setupConnections() {
    connect(m_boardWidget, &BoardWidget::flagCountChanged, m_statusPanel, &StatusPanelWidget::setPlacedFlags);
    connect(m_boardWidget, &BoardWidget::openedCellCountChanged, m_statusPanel, &StatusPanelWidget::setOpenedCells);
    connect(m_statusPanel, &StatusPanelWidget::newGameRequested, m_boardWidget, &BoardWidget::resetPreview);
    connect(m_statusPanel, &StatusPanelWidget::newGameRequested, m_statusPanel, &StatusPanelWidget::reset);
}