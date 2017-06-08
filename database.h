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
#include <QDateTime>
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
    QVector<UserDemand_c> UserDemandData;
    QVector<OrderList_c> OrderListData;
    QVector<ReaderNoti_c> ReaderNotiData;
    QVector<OrderList_c> currentOrderList;
    QVector<LostBooks_c> LostBooksData;
    void write_into_userdemand_data(QString userid, QString borrowBookId, int duration);
    void change_password(QString userID, QString newpassword);
    bool write_into_orderlist(UserDemand_c *request);
    QVector<int> set_next_date(QDate currentdate, int duration);
    bool write_into_readernoti(QString UserID, QString BookID, QString content, int ON);
    bool delete_reader_noti_indata(ReaderNoti_c noti);
    void delete_all_reader_noti(ReaderNoti_c noti);
    bool delete_book_from_orderlist(QString UserID, QString BookID);
    bool delete_data_in_lostbooks(QString UserID, QString BookID);
    bool write_into_lostbooks(QString UserID, QString BookID);
};

#endif // DATABASE_H
