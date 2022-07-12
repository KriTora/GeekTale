#include <QApplication>
#include "window.h"

int main(int argc, char** argv)
{
    QApplication gameproc(argc, argv);

    Window win;
    win.show();

    return gameproc.exec();
}
