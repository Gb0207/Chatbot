#include "service.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service w;
    w.setWindowTitle("Bok's Eat's Customer Service");
    w.hide();
    return a.exec();
}
