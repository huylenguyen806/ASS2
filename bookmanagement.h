#ifndef BOOKMANAGEMENT_H
#define BOOKMANAGEMENT_H

#include <QWidget>
#include <maindatabase.h>
#include <QPixmap>

namespace Ui {
class BookManagement;
}

class BookManagement : public QWidget
{
    Q_OBJECT

public:
    UserDemand_c *request = new UserDemand_c();
    explicit BookManagement(QWidget *parent = 0);
    ~BookManagement();

signals:
    void accept_button_signals(UserDemand_c *order);
public slots:
    void on_cancel_add_book_button_clicked();

    void on_cancel_edit_book_button_clicked();

    void showaddbook();

    void showeditbook();

    void showBorrowBookInfo(User_c user, Books_c book);

private slots:
    void on_accept_button_clicked();

    void on_deny_button_clicked();

private:
    Ui::BookManagement *ui;
};

#endif // BOOKMANAGEMENT_H
