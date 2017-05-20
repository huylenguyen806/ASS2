#include "maindatabase.h"
#include <QMessageBox>
#include <QIcon>
#include <QByteArray>
User_c::User_c()
{
    QString UserID;
    QString Name;
    QString Gender;
    QString DayOfBirth;
    QString ID_StudentID;
    QString Career;
}

User_c::~User_c()
{

}

Account_c::Account_c()
{
    QString Username;
    QString Password;
    QString ID;
    bool active;
}
Account_c::~Account_c()
{

}


Books_c::Books_c()
{
    QString BookID;
    QString BName;
    QString PublishedDate;
    QString Author;
    QString Publisher;
    QString Kind;
    QByteArray Image;
}

Books_c::~Books_c()
{

}

AccountRoleMap_c::AccountRoleMap_c()
{
    QString Account_No;
    QString Role_ID;
}

AccountRoleMap_c::~AccountRoleMap_c()
{

}

Role_c::Role_c()
{
    QString Role_ID;
    QString Role_Desc;
}

Role_c::~Role_c()
{

}
