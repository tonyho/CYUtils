#include "cyutil.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CYUtil w;
    w.show();

    return a.exec();
}
