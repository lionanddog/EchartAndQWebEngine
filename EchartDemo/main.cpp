#include "echartdemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EchartDemo w;
    w.show();
    return a.exec();
}
