#include "bankui.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BankUI w;

    w.show();

    return a.exec();
}
