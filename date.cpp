#include "date.h"

Date::Date()
{
}

void Date::reset()
{
    day = 1,
    month = 1,
    year = 2000,
    day_of_week = 5,
    days_since = 1,
    months_since = 0,
    years_since = 0;
}

void Date::new_day()
{
    ++day;

    // 1..12 = январь..декабрь
    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day > 31 && month == 12) day = 1, month = 1, ++year, ++months_since, ++years_since;
            if (day > 31) day = 1, ++month, ++months_since;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            if (day > 30) day = 1, ++month, ++months_since;
            break;

        case 2:
            if (day > 28 && year % 4 != 0) day = 1, ++month, ++months_since;
            if (day > 29 && year % 4 == 0) day = 1, ++month, ++months_since;
            break;
    }

    ++day_of_week;
    if (day_of_week > 6) day_of_week = 0;

    ++days_since;
}

QString Date::getDateString()
{
    QString result;

    if (day <= 9) result += "0";
    result += QString::number(day) + ".";

    if (month <= 9) result += "0";
    result += QString::number(month) + "." + QString::number(year);

    return result;
}

QString Date::getDateTooltip()
{
    QString result = getDateString() + "\n" + week[day_of_week] + "\n\n";
    result += "С начала Вашей истории ";

    // извлечение последних двух цифр для подбора правильных слов
    int t = days_since, x1 = -1, x2 = -1;
    while (t > 0)
    {
        x1 = t % 10, t /= 10;

        if (t == 0) continue;
        x2 = t % 10, t /= 10;
    }

    // x1 всегда будет иметь значение, не равное -1, потому что x1 соответствует последней цифре
    // x2 почти всегда будет иметь значение, не равное -1, но влиять на что-то будет только когда он равен 1

    if (x2 == 1)
    {
            result += "прошло " + QString::number(days_since) + " дней";
    }
    else
    {
        switch (x1)
        {
            case 0:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                result += "прошло " + QString::number(days_since) + " дней";
                break;

            case 1:
                result += "прошёл " + QString::number(days_since) + " день";
                break;

            case 2:
            case 3:
            case 4:
                result += "прошло " + QString::number(days_since) + " дня";
                break;
        }
    }

    return result;
}
