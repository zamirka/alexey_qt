#ifndef SOLUTION_H
#define SOLUTION_H

#include <QString>

class Solution
{
public:
    int step;
    QString description;
    QString image;

    Solution();
    Solution(int _step, QString _description, QString _image);
    ~Solution();
};

#endif // SOLUTION_H
