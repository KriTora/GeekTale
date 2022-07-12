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
};

#endif // WINDOW_H
