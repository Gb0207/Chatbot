#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Bok's Eat's Customer SERVER");
    w.show();

    return a.exec();
}
