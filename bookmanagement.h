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
    int on;
    QString money;
    QString message;
    QString UserID;
    QString BookID;
    void show_lost_book_widget(User_c user, Books_c book);
    void show_borrowed_books(LibBorrowedBooks_c data);
    explicit BookManagement(QWidget *parent = 0);
    ~BookManagement();

signals:
    void accept_button_signals(UserDemand_c *order);
    void send_reason_for_denial(QString UserID, QString BookID, QString content, int on);
    void send_lost_book_punishment(QString UserID, QString BookID, QString message, QString money);
    void delete_lost_book(QString UserID, QString BookID);
public slots:
    void on_cancel_add_book_button_clicked();

    void on_cancel_edit_book_button_clicked();

    void showaddbook();

    void showeditbook();

    void showBorrowBookInfo(User_c user, Books_c book, int duration);

private slots:
    void on_accept_button_clicked();

    void on_deny_button_clicked();

    void on_cancel_refusal_clicked();

    void on_ok_refusal_clicked();

    void on_OK_lost_book_clicked();

    void on_Cancel_lost_book_clicked();

    void on_delete_lost_book_clicked();

private:
    Ui::BookManagement *ui;
};

#endif // BOOKMANAGEMENT_H
