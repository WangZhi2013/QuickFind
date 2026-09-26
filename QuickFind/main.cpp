#include "QuickFind.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QuickFind window;
    window.show();
    return app.exec();
}
