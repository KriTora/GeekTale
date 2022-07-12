#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::resizeEvent(QResizeEvent*)
{
    qDebug() << "New window size: " << size().rwidth() << "x" << size().rheight();

    // стак занимает 95% окна по ширине и 90% по высоте; располагается в центре окна
    ui->pagestack->resize(int(size().rwidth() * 0.95), int(size().rheight() * 0.9));
    ui->pagestack->move(int((size().rwidth() - ui->pagestack->width()) / 2), int((size().rheight() - ui->pagestack->height()) / 2));

    // *****главное меню*****
    // название игры занимает 100% ширины стака и 15% высоты стака; не имеет отступов по горизонтали, отступ сверху - 10% высоты стака;
    // размер шрифта - 18% высоты стака
    ui->gametitle->resize(ui->pagestack->width(), int(ui->pagestack->height() * 0.15));
    ui->gametitle->move(0, int(ui->pagestack->height() * 0.10));
    ui->gametitle->setStyleSheet("font-size: " + QString::number(int(ui->pagestack->height() * 0.18)) + "px");

    // лейбл версии не меняет размер, но перемещается так, чтобы всегда быть в левом нижнем углу стака
    ui->version->move(0, ui->pagestack->height() - ui->version->height());
}
