#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    unsigned long long money;

public:
    Player();
    void reset(); // сброс всех характеристик игрока
    QString getMoney() { return QString::number(money) + " р."; }; // возвращает количество денег в виде строки
};

#endif // PLAYER_H
