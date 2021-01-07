#ifndef ADMIN_H
#define ADMIN_H
#include<QSqlQuery>
#include<QVariant>

class admin
{
public:
    admin();
    bool login(QString,QString);
};

#endif // ADMIN_H
