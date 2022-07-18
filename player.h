#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    unsigned long long money;
    int xp;

public:
    Player();
    void reset(); // сброс всех характеристик игрока
    QString getMoney() { return QString::number(money) + " р."; }; // возвращает количество денег
    QString getXp() { return QString::number(xp); }; // возвращает количество опыта
};

#endif // PLAYER_H
