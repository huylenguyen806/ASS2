#include "database.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QIcon>
#include <QSqlQuery>
#include <QApplication>
Database::Database()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(qApp->applicationDirPath() + "/database/libpro.sqlite");
    if(!mydb.open())
           {
                QMessageBox *alert = new QMessageBox();
                alert->setText("Error: connection with database failed");
                alert->setWindowIcon(QIcon(":/images/error.png"));
                alert->setWindowTitle("Error");
                alert->show();
           }
           else
           {
              qDebug() << "Database: connection ok";
           }

        // Lấy đống dữ liệu trong sql vào vector book
        QSqlQuery query1("SELECT * FROM BOOKS");
        int idIndex = query1.record().indexOf("BOOKID");
        int nameIndex = query1.record().indexOf("BNAME");
        int authorIndex = query1.record().indexOf("AUTHOR");
        int publisherIndex = query1.record().indexOf("PUBLISHER");
        int genreIndex = query1.record().indexOf("KIND");
        int dateIndex = query1.record().indexOf("PUBLISHEDDATE");
        int imageIndex = query1.record().indexOf("IMAGE");
        while (query1.next())
        {
            Books_c tempBooks;
            QString tempBookID = query1.value(idIndex).toString();
            QString tempBName = query1.value(nameIndex).toString();
            QString tempPublishedDate = query1.value(dateIndex).toString();
            QString tempAuthor = query1.value(authorIndex).toString();
            QString tempPublisher = query1.value(publisherIndex).toString();
            QString tempKind = query1.value(genreIndex).toString();
            QByteArray tempImage = query1.value(imageIndex).toByteArray();
            tempBooks.BookID = tempBookID;
            tempBooks.BName = tempBName;
            tempBooks.PublishedDate = tempPublishedDate;
            tempBooks.Author = tempAuthor;
            tempBooks.Publisher = tempPublisher;
            tempBooks.Kind = tempKind;
            tempBooks.Image = tempImage;
            BookData.append(tempBooks);
        }
        query1.clear();
        // Lấy đống dữ liệu trong sql vào vector user
        query1.exec("SELECT * FROM User");
        int IdUser = query1.record().indexOf("UserID");
        int usernameIndex = query1.record().indexOf("Name");
        int genderIndex = query1.record().indexOf("GENDER");
        int birthday = query1.record().indexOf("DAY OF BIRTH");
        int realID = query1.record().indexOf("ID/STUDENT ID");
        int career = query1.record().indexOf("CAREER");
        while (query1.next())
        {
           User_c tempUser;
           QString tempUserID = query1.value(IdUser).toString();
           QString tempName = query1.value(usernameIndex).toString();
           QString tempGender = query1.value(genderIndex).toString();
           QString tempDayOfBirth = query1.value(birthday).toString();
           QString tempID_StudentID = query1.value(realID).toString();
           QString tempCareer = query1.value(career).toString();
           tempUser.UserID=tempUserID;
           tempUser.Name=tempName;
           tempUser.Gender=tempGender;
           tempUser.DayOfBirth=tempDayOfBirth;
           tempUser.ID_StudentID=tempID_StudentID;
           tempUser.Career=tempCareer;
           UserData.append(tempUser);
        }
        query1.clear();
        // Lấy đống dữ liệu trong sql vào vector account
        query1.exec("SELECT * FROM Account");
        int accountname = query1.record().indexOf("USERNAME");
        int pass = query1.record().indexOf("PASSWORD");
        int ID = query1.record().indexOf("ID");
        int active = query1.record().indexOf("ACTIVE");
        while (query1.next())
        {
           Account_c tempAccount;
           QString tempUsername = query1.value(accountname).toString();
           QString tempPassword = query1.value(pass).toString();
           QString tempID = query1.value(ID).toString();
           bool tempActive = query1.value(active).toBool();
           tempAccount.Username=tempUsername;
           tempAccount.Password=tempPassword;
           tempAccount.ID=tempID;
           tempAccount.active=tempActive;
           AccountData.append(tempAccount);
        }
        query1.clear();
        // Lấy đống dữ liệu trong sql vào vector Role
        query1.exec("SELECT * FROM ROLE");
        int idrowRole_ID = query1.record().indexOf("ROLE ID");
        int idrowRole_desc = query1.record().indexOf("ROLE DESC");
        while (query1.next())
        {
           Role_c tempRole;
           QString tempRole_ID = query1.value(idrowRole_ID).toString();
           QString tempRole_Desc = query1.value(idrowRole_desc).toString();
           tempRole.Role_ID=tempRole_ID;
           tempRole.Role_Desc=tempRole_Desc;
           RoleData.append(tempRole);
        }
        query1.clear();
        // Lấy đống dữ liệu trong sql vào vector AccountRoleMap
        query1.exec("SELECT * FROM AccountRoleMap");
        idrowRole_ID = query1.record().indexOf("ROLE ID");
        int account_no = query1.record().indexOf("ACCOUNT NO");
        while (query1.next())
        {
           AccountRoleMap_c tempAccountRoleMap;
           QString tempAccount_No = query1.value(account_no).toString();
           QString temproles = query1.value(idrowRole_ID).toString();
           tempAccountRoleMap.Account_No=tempAccount_No;
           tempAccountRoleMap.roles=temproles;
           AccountRoleMapData.append(tempAccountRoleMap);
        }
        query1.clear();
        idrowRole_ID = NULL;
        account_no = NULL;
        idrowRole_desc = NULL;
        active = NULL;
        idIndex = NULL;
        ID = NULL;
        accountname = NULL;
        pass = NULL;
        usernameIndex = NULL;
        genderIndex = NULL;
        genreIndex = NULL;
        realID = NULL;
        career = NULL;
        birthday = NULL;
        IdUser = NULL;
        nameIndex = NULL;
        authorIndex = NULL;
        publisherIndex = NULL;
        genreIndex = NULL;
        dateIndex = NULL;
        imageIndex = NULL;
}


Database::~Database()
{

}
