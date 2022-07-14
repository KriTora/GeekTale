#ifndef WINDOW_H
#define WINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QResizeEvent>

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
    void resizeEvent(QResizeEvent*);
    void connect(); // соединяет все сигналы и слоты

private slots:
    // навигационная панель
    void backtotitle(); // главное меню

    // главное меню
    void newgame(); // сбрасывает все параметры игрока и запускает игровую сессию
};

#endif // WINDOW_H
