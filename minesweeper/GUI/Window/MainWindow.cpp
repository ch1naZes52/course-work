#include "MainWindow.h"

#include <QComboBox>
#include <QEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMouseEvent>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_qtimer(new QTimer(this)) {
    m_controller.setObserver(this);
    setupUi();

    connect(m_qtimer, &QTimer::timeout, this, [this]() {
        m_timer.tick();
        updateLabels();
        });

    m_qtimer->start(1000);
    restart();
}

bool MainWindow::eventFilter(QObject* object, QEvent* event) {
    QPushButton* button = qobject_cast<QPushButton*>(object);

    if (!button || event->type() != QEvent::MouseButtonPress) {
        return QMainWindow::eventFilter(object, event);
    }

    QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
    int row = button->property("row").toInt();
    int column = button->property("column").toInt();

    if (mouse->button() == Qt::LeftButton) {
        openCell(row, column);
        return true;
    }

    if (mouse->button() == Qt::RightButton) {
        toggleFlag(row, column);
        return true;
    }

    return QMainWindow::eventFilter(object, event);
}

void MainWindow::setupUi() {
    QWidget* central = new QWidget(this);
    QVBoxLayout* root = new QVBoxLayout(central);
    QHBoxLayout* top = new QHBoxLayout();

    m_minesLabel = new QLabel(this);
    m_timeLabel = new QLabel(this);
    m_openedLabel = new QLabel(this);
    m_stateLabel = new QLabel(this);
    m_difficultyBox = new QComboBox(this);
    QPushButton* restartButton = new QPushButton("Новая игра", this);
    m_events = new QListWidget(this);

    m_difficultyBox->addItems({ "Новичок", "Любитель", "Эксперт" });

    top->addWidget(m_minesLabel);
    top->addWidget(m_timeLabel);
    top->addWidget(m_openedLabel);
    top->addWidget(m_difficultyBox);
    top->addWidget(m_stateLabel);
    top->addWidget(restartButton);

    QWidget* board = new QWidget(this);
    m_grid = new QGridLayout(board);
    m_grid->setSpacing(2);

    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidget(board);
    scroll->setWidgetResizable(true);

    root->addLayout(top);
    root->addWidget(new QLabel("ЛКМ — открыть клетку, ПКМ — поставить флаг", this));
    root->addWidget(m_events);
    root->addWidget(scroll, 1);

    setCentralWidget(central);
    setWindowTitle("Minesweeper");
    resize(840, 800);

    connect(restartButton, &QPushButton::clicked, this, &MainWindow::restart);
    connect(m_difficultyBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::restart);
}

void MainWindow::restart() {
    m_events->clear();
    m_timer.reset();

    RestartGameCommand command(m_controller, selectedDifficulty());
    command.execute();
}

void MainWindow::rebuildBoard() {
    for (QPushButton* button : m_buttons) {
        m_grid->removeWidget(button);
        delete button;
    }

    m_buttons.clear();

    for (int row = 0; row < m_controller.settings().size().rows(); ++row) {
        for (int column = 0; column < m_controller.settings().size().columns(); ++column) {
            QPushButton* button = new QPushButton(this);
            button->setMinimumSize(28, 28);
            button->setProperty("row", row);
            button->setProperty("column", column);
            button->installEventFilter(this);
            m_buttons.push_back(button);
            m_grid->addWidget(button, row, column);
        }
    }
}

void MainWindow::updateView() {
    const GameBoard& board = m_controller.board();

    if (static_cast<int>(m_buttons.size()) != board.cellCount()) {
        rebuildBoard();
    }

    for (QPushButton* button : m_buttons) {
        CellPosition position(button->property("row").toInt(), button->property("column").toInt());
        styleButton(button, board.cell(position));
    }

    updateLabels();
}

void MainWindow::updateLabels() {
    m_minesLabel->setText(QString("Мины: %1").arg(m_controller.counter().remaining()));
    m_timeLabel->setText(QString("Время: %1").arg(timeText()));
    m_openedLabel->setText(QString("Открыто: %1").arg(m_controller.board().openedCount()));
    m_stateLabel->setText(stateText());
}

void MainWindow::styleButton(QPushButton* button, const Cell& cell) {
    button->setEnabled(m_controller.state() != GameState::Won && m_controller.state() != GameState::Lost);

    if (cell.isFlagged()) {
        button->setText("⚑");
        return;
    }

    if (!cell.isOpened()) {
        button->setText("");
        return;
    }

    if (cell.isMine()) {
        button->setText("✹");
        return;
    }

    button->setText(cell.isNumber() ? QString::number(cell.adjacentMines()) : "");
}

void MainWindow::openCell(int row, int column) {
    OpenCellCommand command(m_controller, CellPosition(row, column));

    if (command.execute()) {
        m_timer.start();
    }
}

void MainWindow::toggleFlag(int row, int column) {
    ToggleFlagCommand command(m_controller, CellPosition(row, column));
    command.execute();
}

GameDifficulty MainWindow::selectedDifficulty() const {
    if (m_difficultyBox->currentIndex() == 1) {
        return GameDifficulty::Intermediate;
    }

    if (m_difficultyBox->currentIndex() == 2) {
        return GameDifficulty::Expert;
    }

    return GameDifficulty::Beginner;
}

QString MainWindow::stateText() const {
    if (m_controller.state() == GameState::Running) {
        return "Игра идет";
    }

    if (m_controller.state() == GameState::Won) {
        return "Победа";
    }

    if (m_controller.state() == GameState::Lost) {
        return "Поражение";
    }

    return "Готов к игре";
}

QString MainWindow::timeText() const {
    int seconds = m_timer.seconds();

    if (seconds < 10) {
        return QString("00%1").arg(seconds);
    }

    if (seconds < 100) {
        return QString("0%1").arg(seconds);
    }

    return QString::number(seconds);
}

void MainWindow::onGameChanged() {
    if (m_controller.state() == GameState::Won || m_controller.state() == GameState::Lost) {
        m_timer.stop();
    }

    updateView();
}

void MainWindow::onGameEvent(const std::string& text) {
    m_events->insertItem(0, QString::fromUtf8(text.c_str()));

    while (m_events->count() > 5) {
        delete m_events->takeItem(m_events->count() - 1);
    }
}