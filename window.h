#ifndef WINDOW_H
#define WINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTimer>

#include "ui_window.h"
#include "date.h"
#include "player.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;
    QTimer *tick_timer;

    Date date; // хранит в себе все данные о текущей игровой дате
    Player player; // хранит в себе все данные об игроке

    void resizeEvent(QResizeEvent*); // ниже описаны ресайз-методы для различных элементов UI
    void resizeMainLabelcards(QFrame*, QLabel*, QLabel*, QLabel* = nullptr); // обработка размера и расположения карточек (например карточка даты - связка двух лейблов и линии)
    void resizeTitleMainButtons(QPushButton*, QPushButton* = nullptr); // обработка основных кнопок в главном меню
    void resizeNavigationButtons(QPushButton*, QPushButton* = nullptr); // обработка кнопок навигации

    void connect(); // соединяет все сигналы и слоты

private slots:
    // служебные слоты
    void tick(); // обновление данных

    // слоты навигационной панели
    void backtotitle(); // главное меню

    // слоты главного меню
    void newgame(); // сбрасывает все параметры игрока и запускает игровую сессию
};

#endif // WINDOW_H
