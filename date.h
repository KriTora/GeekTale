#ifndef DATE_H
#define DATE_H

#include <QString>

class Date
{
private:
    int day, month, year;

    QString week[7] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
    int day_of_week;

    int years_since, months_since, days_since;

public:
    Date();
    void reset();
    void new_day(); // изменение дня на +1
    QString getDateString(); // возвращает строку с датой в формате dd.mm.yyyy
    QString getDateTooltip(); // возвращает текст для всплывающего окна даты
};

#endif // DATE_H
