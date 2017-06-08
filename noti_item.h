#ifndef NOTI_ITEM_H
#define NOTI_ITEM_H

#include <QWidget>
#include "maindatabase.h"
#include <QListWidgetItem>

namespace Ui {
class noti_item;
}

class noti_item : public QWidget
{
    Q_OBJECT

public:
    ReaderNoti_c noti;
    Books_c book;
    User_c user;
    QListWidgetItem *item = new QListWidgetItem();
    void set_info(QString info);
    void hide_reader_noti_detail();
    void hide_lost_book_detail();
    void set_lost_book_info(QString UserID, QString UserName, QString BookID, QString BName);
    explicit noti_item(QWidget *parent = 0);
    ~noti_item();
signals:
    void show_detail(ReaderNoti_c noti, Books_c book);
    void selectItem(QListWidgetItem*);
    void lost_book_detail(User_c user, Books_c book);
private slots:
    void on_pushButton_clicked();

    void on_lostbook_detail_clicked();

private:
    Ui::noti_item *ui;
};

#endif // NOTI_ITEM_H
