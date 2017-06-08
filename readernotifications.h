#ifndef READERNOTIFICATIONS_H
#define READERNOTIFICATIONS_H

#include <QDialog>
#include "maindatabase.h"

namespace Ui {
class ReaderNotifications;
}

class ReaderNotifications : public QDialog
{
    Q_OBJECT

public:
    ReaderNoti_c noti;
    void Create(ReaderNoti_c noti, Books_c book);
    explicit ReaderNotifications(QWidget *parent = 0);
    ~ReaderNotifications();
signals:
    void delete_noti(ReaderNoti_c noti);
private slots:
    void on_delete_b_clicked();

    void on_delete_u_clicked();

private:
    Ui::ReaderNotifications *ui;
};

#endif // READERNOTIFICATIONS_H
