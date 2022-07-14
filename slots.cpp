#include "window.h"
#include "ui_window.h"

void Window::backtotitle()
{
    ui->pagestack->setCurrentIndex(0);
    ui->navigation->hide();
    setWindowTitle("Главное меню");
}

void Window::newgame()
{
    ui->pagestack->setCurrentIndex(1);
    ui->navigation->show();
    setWindowTitle("Главная");
}
