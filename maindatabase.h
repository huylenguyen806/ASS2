#ifndef MAINDATABASE_H
#define MAINDATABASE_H
#include <QString>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QByteArray>

class User_c
{
public:
    QString UserID;
    QString Name;
    QString Gender;
    QString DayOfBirth;
    QString ID_StudentID;
    QString Career;
};

class Account_c
{
public:
    QString Username;
    QString Password;
    QString ID;
    bool active;
};

class AccountRoleMap_c
{
public:
    QString Account_No;
    QString roles;
};

class Role_c
{
public:
    QString Role_ID;
    QString Role_Desc;
};

class Books_c
{
public:
    QString BookID;
    QString BName;
    QString PublishedDate;
    QString Author;
    QString Publisher;
    QString Kind;
    QByteArray Image;
};

#endif // MAINDATABASE_H
