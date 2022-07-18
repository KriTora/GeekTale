#include "window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    tick_timer = new QTimer();

    connect();
    backtotitle();
}

Window::~Window()
{
    delete ui;
    delete tick_timer;
}

void Window::resizeEvent(QResizeEvent*)
{
    // некоторые элементы интерфейса существуют в единственном экземпляре (например название игры или навигационная панель),
    // поэтому я написал не все ресайз-методы - считаю, что они не нужны и лучше для таких элементов написать поведение прямо здесь
    qDebug() << "New window size: " << size().rwidth() << "x" << size().rheight();

    // ***стак***
    // он анимает 95% окна по ширине и 90% по высоте; располагается в центре окна
    ui->pagestack->resize(int(size().rwidth() * 0.95), int(size().rheight() * 0.9));
    ui->pagestack->move(int((size().rwidth() - ui->pagestack->width()) / 2), int((size().rheight() - ui->pagestack->height()) / 2));


    // ***навигационная панель*** (в будущем - переписать ресайз-метод так, чтобы кнопки располагались красиво)
    // навигационная панель занимает 95% от ширины окна и 10% от высоты;
    // располагается в середине по горизонтали и (высота стака - его Y) по вертикали
    ui->navigation->resize(int(size().rwidth() * 0.95), int(size().rheight() * 0.1));
    ui->navigation->move(int((size().rwidth() - ui->navigation->width()) / 2), ui->pagestack->height() - ui->pagestack->y());
    // кнопка Главное меню
    resizeNavigationButtons(ui->btn_backtotitle);
    resizeNavigationButtons(ui->btn_toJob, ui->btn_backtotitle);


    // ***главное меню***
    // кнопка Новая игра
    resizeTitleMainButtons(ui->btn_newgame);
    // кнопка Выйти
    resizeTitleMainButtons(ui->btn_quit, ui->btn_newgame);
    // название игры
    // оно занимает 100% от ширины стака и 15% от высоты стака; не имеет отступов по горизонтали, отступ сверху: 10% от высоты стака;
    // размер шрифта: 18% от высоты стака
    ui->gametitle->resize(ui->pagestack->width(), int(ui->pagestack->height() * 0.15));
    ui->gametitle->move(0, int(ui->pagestack->height() * 0.10));
    ui->gametitle->setStyleSheet("font-size: " + QString::number(int(ui->pagestack->height() * 0.18)) + "px");
    // версия
    // этот лейбл не меняет размер, но перемещается так, чтобы всегда быть в левом нижнем углу стака
    ui->version->move(0, ui->pagestack->height() - ui->version->height());


    // ***главная (карточки)***
    // дата
    resizeMainLabelcards(ui->date_divide, ui->lbl_date, ui->lbl_date_calendar);
    // деньги
    resizeMainLabelcards(ui->money_divide, ui->lbl_money, ui->lbl_money_account, ui->lbl_date_calendar);
    // опыт
    resizeMainLabelcards(ui->xp_divide, ui->lbl_xp, ui->lbl_xp_account, ui->lbl_money_account);
}

void Window::resizeMainLabelcards(QFrame* d, QLabel* l1, QLabel* l2, QLabel* l3)
{
    // d = разделительная линия
    // l1 & l2 & l3 = соответственно устанавливаемые лейблы (1 - над и 2 - под линией) и предыдущий лейбл

    // если метод вызывается с тремя аргументоми, то лейблы располагаются по правилам (только первая карточка!):
    // ширина - 100% стака, высота - 4% стака; шрифт - 100% высоты лейбла;
    // отступ сверху первого лейбла - 10% высоты стака;
    // отступ сверху второго лейбла - (высота + Y) первого лейбла + (высота / 2) разделительной линии

    // разделительная линия всегда устанавливается по правилам:
    // 20% от ширины стака, 1% от высоты стака; располагается в середине по горизонтали и (высота + Y верхнего лейбла) по вертикали

    // если вызов производится с четырьмя аргументами, то правило определения отступа сверху для первого лейбла меняется:
    // (высота + Y) предыдущего лейбла + 10% высоты нового лейбла

    if (l3 == nullptr)
    {
        // первая карточка

        // сверху от линии
        l1->resize(ui->pagestack->width(), int(ui->pagestack->height() * 0.04));
        l1->move(0, int(ui->pagestack->height() * 0.1));
        l1->setStyleSheet("font-size: " + QString::number(int(l1->height())) + "px; border-top: 1px solid black");

        // линия
        d->resize(int(ui->pagestack->width() * 0.2), int(ui->pagestack->height() * 0.01));
        d->move(int((ui->pagestack->width() - d->width()) / 2), l1->height() + l1->y());

        // снизу от линии
        l2->resize(ui->pagestack->width(), int(ui->pagestack->height() * 0.04));
        l2->move(0, l1->height() + l1->y() + (d->height() / 2));
        l2->setStyleSheet("font-size: " + QString::number(int(l2->height())) + "px; border: none;  border-bottom: 1px solid black;");
    }
    else
    {
        // не первая карточка

        // сверху от линии
        l1->resize(ui->pagestack->width(), int(ui->pagestack->height() * 0.04));
        l1->move(0, l3->height() + l3->y() + int(l1->height() * 0.1));
        l1->setStyleSheet("font-size: " + QString::number(int(l1->height())) + "px; border-top: 1px solid black");

        // линия
        d->resize(int(ui->pagestack->width() * 0.2), int(ui->pagestack->height() * 0.01));
        d->move(int((ui->pagestack->width() - d->width()) / 2), l1->height() + l1->y());

        // снизу от линии
        l2->resize(ui->pagestack->width(), int(ui->pagestack->height() * 0.04));
        l2->move(0, l1->height() + l1->y() + (d->height() / 2));
        l2->setStyleSheet("font-size: " + QString::number(int(l2->height())) + "px; border: none;  border-bottom: 1px solid black;");
    }
}

void Window::resizeTitleMainButtons(QPushButton* b1, QPushButton* b2)
{
    // если метод вызывается с одним аргументом, то считается, что эта кнопка будет первой в меню - она будет самой верхней
    // в таком случае применяются правила:
    // размер: 25% от ширины стака, 8% высоты стака;
    // расположение: в середине по горизонтали, по вертикали - на 45% от высоты стака
    // шрифт: 44% от высоты кнопки

    // если метод вызывается с двумя аргументами, то b1 - добавляемая кнопка, а b2 - кнопка, расположенная выше добавляемой
    // в таком случае расположение кнопки по горизонтали определяется по формуле (высота + y) b2

    if (b2 == nullptr)
    {
        // первая кнопка

        b1->resize(int(ui->pagestack->width() * 0.25), int(ui->pagestack->height() * 0.08));
        b1->move(int((ui->pagestack->width() - b1->width()) / 2 ), int(ui->pagestack->height() * 0.45));
        b1->setStyleSheet("font-size: " + QString::number(int(b1->height() * 0.44)) + "px");
    }
    else
    {
        // не первая кнопка

        b1->resize(int(ui->pagestack->width() * 0.25), int(ui->pagestack->height() * 0.08));
        b1->move(int((ui->pagestack->width() - b1->width()) / 2 ), b2->height() + b2->y());
        b1->setStyleSheet("font-size: " + QString::number(int(b1->height() * 0.44)) + "px");
    }
}

void Window::resizeNavigationButtons(QPushButton* b1, QPushButton* b2)
{
    // b1 - кнопка, для которой регулируются размер и положение, b2 - предыдущая кнопка
    // если метод вызван с одним аргументом, то отступ слева равен нулю - это будет первая кнопка на навигационной панели;
    // если аргумента 2, то отступ b1 слева рассчитывается так: (ширина b2 + y b2 + 10% ширины b1)

    // общие правила:
    // размер кнопки: 9,5% от ширины панели, 100% от высоты панели;
    // размер шрифта: 25% от высоты кнопки

    if (b2 == nullptr)
    {
        // первая кнопка

        b1->resize(ui->navigation->width() * 0.095, ui->navigation->height());
        b1->setStyleSheet("font-size: " + QString::number(int(b1->height() * 0.25)) + "px");
    }
    else
    {
        // не первая кнопка

        b1->resize(ui->navigation->width() * 0.095, ui->navigation->height());
        b1->move(b2->width() + b2->y() + int(b1->width() * 0.1), 0);
        b1->setStyleSheet("font-size: " + QString::number(int(b1->height() * 0.25)) + "px");
    }
}

void Window::connect()
{
    qDebug() << "Connecting all slots to signals";

    // служебные слоты
    QObject::connect(tick_timer, &QTimer::timeout, this, &Window::tick);

    // навигационная панель
    QObject::connect(ui->btn_backtotitle, &QPushButton::clicked, this, &Window::backtotitle);

    // главное меню
    QObject::connect(ui->btn_newgame, &QPushButton::clicked, this, &Window::newgame);
    QObject::connect(ui->btn_quit, &QPushButton::clicked, this, &QApplication::quit);

}
