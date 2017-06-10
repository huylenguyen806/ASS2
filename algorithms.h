#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "database.h"
#include <QVector>
#include <QMessageBox>

class LevenshteinDistance
{
public:
    int get_differences_between_2_strings(QString s, QString t);
};

class Search : private LevenshteinDistance
{
private:
    QVector<Books_c> Books;
    QVector<Account_c> Accounts;
    QVector<User_c> Users;
public:
    Search(QVector<Books_c> b);
    Search(QVector<Account_c> a);
    Search(QVector<User_c> u);

    void setBookData(QVector<Books_c> b);
    void setAccountData(QVector<Account_c> a);
    void setUserData(QVector<User_c> u);

    QVector<Books_c> getBookData();
    QVector<Account_c> getAccountData();
    QVector<User_c> getUserData();

    void findBookName(QString BName);
    void findBookGenre(QString Genre);
    void findBookAuthor(QString Author);
    void findBookPublisher(QString Publisher);

    void findAccountName(QString accountName);

    void findUserName(QString UserName);
    void findUserGender(QString UserGender);
    void findUserRealID(QString RealID);
    void findUserCareer(QString Career);
    void findUserEmail(QString email);
    void findUserBirthday(QString birthday);
};

#endif // ALGORITHMS_H
