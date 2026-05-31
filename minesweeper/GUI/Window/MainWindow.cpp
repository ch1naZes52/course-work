#include "MainWindow.h"
#include "../Widgets/BoardWidget.h"
#include "../Widgets/StatusPanelWidget.h"

#include <QScrollArea>
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
    setMinimumSize(680, 700);
    resize(820, 780);
}

void MainWindow::setupCentralWidget() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    m_statusPanel = new StatusPanelWidget(centralWidget);
    m_boardWidget = new BoardWidget(centralWidget);

    QScrollArea* boardScrollArea = new QScrollArea(centralWidget);
    boardScrollArea->setWidget(m_boardWidget);
    boardScrollArea->setWidgetResizable(true);

    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);
    mainLayout->addWidget(m_statusPanel);
    mainLayout->addWidget(boardScrollArea, 1);

    setCentralWidget(centralWidget);
}

void MainWindow::setupConnections() {
    connect(m_boardWidget, &BoardWidget::flagCountChanged, m_statusPanel, &StatusPanelWidget::setPlacedFlags);
    connect(m_boardWidget, &BoardWidget::openedCellCountChanged, m_statusPanel, &StatusPanelWidget::setOpenedCells);
    connect(m_boardWidget, &BoardWidget::gameStatusChanged, m_statusPanel, &StatusPanelWidget::setStatus);
    connect(m_boardWidget, &BoardWidget::gameInfoChanged, m_statusPanel, &StatusPanelWidget::setGameInfo);
    connect(m_boardWidget, &BoardWidget::gameEventAdded, m_statusPanel, &StatusPanelWidget::addEvent);
    connect(m_statusPanel, &StatusPanelWidget::newGameRequested, m_boardWidget, &BoardWidget::resetPreview);
    connect(m_statusPanel, &StatusPanelWidget::newGameRequested, m_statusPanel, &StatusPanelWidget::reset);
    connect(m_statusPanel, &StatusPanelWidget::difficultySelected, m_boardWidget, &BoardWidget::setDifficulty);
}