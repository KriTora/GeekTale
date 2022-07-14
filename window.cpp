#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    connect();
    backtotitle();
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

    // навигационная панель
    // навигационная панель занимает 95% ширины окна и 10% высоты окна;
    // располагается в середине по горизонтали и (высота стака - его Y) по вертикали
    // размер кнопок кнопок: 9,5% ширины панели, 100% высоты панели;
    // первая кнопка не имеет отступа от края
    // размер шрифта: 25% от высоты кнопки

    ui->navigation->resize(int(size().rwidth() * 0.95), int(size().rheight() * 0.1));
    ui->navigation->move(int((size().rwidth() - ui->navigation->width()) / 2), ui->pagestack->height() - ui->pagestack->y());

    // главное меню
    ui->btn_backtotitle->resize(ui->navigation->width() * 0.095, ui->navigation->height());
    ui->btn_backtotitle->setStyleSheet("font-size: " + QString::number(int(ui->btn_backtotitle->height() * 0.25)) + "px");

    // *****главное меню*****
    // название игры занимает 100% ширины стака и 15% высоты стака; не имеет отступов по горизонтали, отступ сверху - 10% высоты стака;
    // размер шрифта - 18% высоты стака
    ui->gametitle->resize(ui->pagestack->width(), int(ui->pagestack->height() * 0.15));
    ui->gametitle->move(0, int(ui->pagestack->height() * 0.10));
    ui->gametitle->setStyleSheet("font-size: " + QString::number(int(ui->pagestack->height() * 0.18)) + "px");

    // лейбл версии не меняет размер, но перемещается так, чтобы всегда быть в левом нижнем углу стака
    ui->version->move(0, ui->pagestack->height() - ui->version->height());

    // основные кнопки: 25% ширины стака, 8% высоты стака; расположены в середине по горизонтали;
    // по вертикали: первая кнопка - 45% высоты стака; следующие - (высота предыдущей кнопки + её кооридана Y)
    // размер шрифта: 44% от высоты кнопки
    // новая игра
    ui->btn_newgame->resize(int(ui->pagestack->width() * 0.25), int(ui->pagestack->height() * 0.08));
    ui->btn_newgame->move(int((ui->pagestack->width() - ui->btn_newgame->width()) / 2 ), int(ui->pagestack->height() * 0.45));
    ui->btn_newgame->setStyleSheet("font-size: " + QString::number(int(ui->btn_newgame->height() * 0.44)) + "px");

    // выйти
    ui->btn_quit->resize(int(ui->pagestack->width() * 0.25), int(ui->pagestack->height() * 0.08));
    ui->btn_quit->move(int((ui->pagestack->width() - ui->btn_quit->width()) / 2 ), ui->btn_newgame->height() + ui->btn_newgame->y());
    ui->btn_quit->setStyleSheet("font-size: " + QString::number(int(ui->btn_quit->height() * 0.44)) + "px");
}

void Window::connect()
{
    // навигационная панель
    QObject::connect(ui->btn_backtotitle, &QPushButton::clicked, this, &Window::backtotitle);

    // главное меню
    QObject::connect(ui->btn_newgame, &QPushButton::clicked, this, &Window::newgame);
    QObject::connect(ui->btn_quit, &QPushButton::clicked, this, &QApplication::quit);
}
