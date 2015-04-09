#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <QVector>
#include "solution.h"

class Item
{
public:
    QString name;
    QVector<Item> items;
    QVector<Solution> solutions;

    Item();
    ~Item();
    Item(QString _name);
};

#endif // LEVEL_H
