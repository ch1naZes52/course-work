#include "minesweeper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    minesweeper window;
    window.show();
    return app.exec();
}
