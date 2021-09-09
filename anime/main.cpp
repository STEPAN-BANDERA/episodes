#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //tbb::spin_mutex mx;

    SetConsoleCP(866);
    SetConsoleOutputCP(866);
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
