#include <QApplication>
#include "serial_tool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serial_tool w;
    w.show();
    
    return a.exec();
}
