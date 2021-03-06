#include "window.h"
#include "ui_window.h"

void Window::tick()
{
    // календарь
    date.new_day();
    ui->lbl_date_calendar->setText(date.getDateString());
    ui->lbl_date_calendar->setToolTip(date.getDateTooltip());

    // деньги
    ui->lbl_money_account->setText(player.getMoney());

    //опыт
    ui->lbl_xp_account->setText(player.getXp());

    qDebug() << "Tick " << date.getDateString();
}

void Window::newgame()
{
    date.reset();
    player.reset();

    ui->pagestack->setCurrentIndex(1);
    ui->navigation->show();
    setWindowTitle("Главная");

    reloadNavigation();
    ui->btn_toMain->setEnabled(false);

    tick_timer->start(1000); // 1 тик = 1000 мс

    qDebug() << "Starting a new game";
}

// ***навигационная панель***
void Window::backtotitle()
{
    tick_timer->stop(); // заморозка времени в игре
    ui->pagestack->setCurrentIndex(0);
    ui->navigation->hide();
    setWindowTitle("Главное меню");

    qDebug() << "Going to title screen";
}

void Window::toMain()
{
    ui->pagestack->setCurrentIndex(1);
    setWindowTitle("Главная");

    reloadNavigation();
    ui->btn_toMain->setEnabled(false);

    qDebug() << "Going to main screen";
}

void Window::toJob()
{
    ui->pagestack->setCurrentIndex(2);
    setWindowTitle("Работа");

    reloadNavigation();
    ui->btn_toJob->setEnabled(false);

    qDebug() << "Going to job screen";
}
