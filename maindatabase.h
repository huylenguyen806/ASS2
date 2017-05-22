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
    QString email;
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
    int Amount;
};

class UserDemand_c
{
public:
    QString UserID;
    QString BorrowBookID;
    int Duration;
    UserDemand_c();
};

class OrderList_c
{
public:
    QString UserID;
    QString BookID;
    QString BorrowDay;
    QString ReturnDay;
};

class CurrentUser
{
public:
    QString currentAccount_name;
    QString currentRole;
    QString currentUserID;
    bool currentActive;
    QString currentName;
    QString currentBirthday;
    QString currentGender;
    QString currentID;
    QString currentCareer;
    QString currentEmail;
    QString currentPass;
    QVector<Books_c> BasketData;
    void clear(){
        currentAccount_name.clear();
        currentActive = 0;
        currentBirthday.clear();
        currentCareer.clear();
        currentEmail.clear();
        currentGender.clear();
        currentID.clear();
        currentName.clear();
        currentRole.clear();
        currentUserID.clear();
        currentPass.clear();
        BasketData.clear();
    }
};

#endif // MAINDATABASE_H
