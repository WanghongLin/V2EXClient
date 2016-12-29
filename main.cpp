#include "v2exwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    V2EXWindow w;
    w.show();

    return a.exec();
}
