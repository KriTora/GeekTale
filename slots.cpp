#include "window.h"
#include "ui_window.h"

void Window::tick()
{
    date.new_day();
    ui->lbl_date_calendar->setText(date.getDateString());
    ui->lbl_date_calendar->setToolTip(date.getDateTooltip());

    qDebug() << "***Tick*** " << date.getDateString();
}

void Window::backtotitle()
{
    tick_timer->stop(); // заморозка времени в игре
    ui->pagestack->setCurrentIndex(0);
    ui->navigation->hide();
    setWindowTitle("Главное меню");

    qDebug() << "Going to title screen";
}

void Window::newgame()
{
    date.reset();
    tick_timer->start(1000); // 1 тик = 1000 мс

    ui->pagestack->setCurrentIndex(1);
    ui->navigation->show();
    setWindowTitle("Главная");

    qDebug() << "Starting a new game";
}
