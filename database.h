#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QVector>
#include "maindatabase.h"
#include <Qtsql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlRecord>
class Database
{
public:
    Database();
    ~Database();
    QVector<User_c> UserData;
    QVector<Account_c> AccountData;
    QVector<Books_c> BookData;
    QVector<AccountRoleMap_c> AccountRoleMapData;
    QVector<Role_c> RoleData;
};

#endif // DATABASE_H
