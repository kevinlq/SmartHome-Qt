#ifndef UNITL_H
#define UNITL_H

#include <QSettings>

class Unitl
{
public:

    static bool wrieteInit(QString path, QString user_key,
                           QString user_value);
    static bool readInit(QString path, QString user_key,
                         QString &user_value);
};

#endif // UNITL_H
