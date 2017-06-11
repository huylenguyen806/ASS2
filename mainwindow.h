#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "bookmanagement.h"
#include "manageaccount.h"
#include <QPicture>
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QFrame>
#include <QListWidgetItem>
#include "displaybookwidget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QApplication>
#include "database.h"
#include "readernotifications.h"
#include "noti_item.h"
#include <QDesktopServices>
#include <QTextStream>
#include "algorithms.h"
#include "advancedsearch.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void set_duration_button_clicked(int duration);
private slots:
    void delete_lost_book(QString UserID, QString BookID);

    void receive_lostbook_punishment(QString UserID, QString BookID, QString message, QString money);

    void show_lost_book_detail(User_c user, Books_c book);

    void send_lost_book(books *lost);

    void create_newbook_noti(books *newbook);

    void read_pdf_books(books *read_book);

    void return_book(books *return_book);

    void delete_readernoti_indata(ReaderNoti_c noti);

    void show_reader_noti_detail(ReaderNoti_c noti, Books_c book);

    void get_reason_for_denial(QString UserID, QString BookID, QString content, int on);

    void get_each_duration(QString bookID, int duration);

    void on_edit_book_manage_button_clicked();

    void on_add_account_button_clicked();

    void on_add_book_button_clicked();

    void show_viewer();

    void on_info_button_clicked();

    void on_login_button_clicked();

    void on_close_login_form_button_clicked();

    void clear_all_lineEdit();

    void createMessageBox(QString type, QString text);

    void on_reader_find_book_button_clicked();

    void on_goto_basket_button_clicked();

    void on_reader_change_pass_button_clicked();

    void on_manager_change_pass_button_clicked();

    void on_librarian_change_pass_button_clicked();

    void on_reader_noti_button_clicked();

    void on_manage_account_button_clicked();

    void on_manage_info_button_clicked();

    void on_manage_book_button_clicked();

    void on_manage_demand_button_clicked();

    void on_reset_pass_button_clicked();

    void createDisplayBookWidget();

    void put_in_basket_click(books *book_info);

    void createBookManagerWidget();

    void ListItemClicked(QWidget *widget);

    void on_edit_account_button_clicked();

    void on_remove_account_button_clicked();

    void on_lock_account_button_clicked();

    void on_unlock_account_button_clicked();

    void on_remove_info_button_clicked();

    void on_add_info_button_clicked();

    void on_edit_info_button_clicked();

    void on_cancel_change_pass_button_clicked();

    void on_remove_frome_basket_button_clicked();

    void on_remove_book_button_clicked();

    void on_borrow_button_clicked();

    void on_other_login_button_clicked();

    void on_role_select_currentTextChanged();

    void on_lineEdit_username_returnPressed();

    void on_lineEdit_password_returnPressed();

    void on_ok_change_pass_button_clicked();

    void on_remove_allbook_button_clicked();

    void on_borrow_all_button_clicked();

    void on_confirm_new_pass_returnPressed();

    void on_new_pass_returnPressed();

    void on_change_current_pass_returnPressed();

    void on_Detail_clicked();

    void on_set_duration_button_clicked();

    void accept_reader_request_about_borrowing_book(UserDemand_c *request);

    void on_reader_clearall_button_clicked();

    void on_librarian_tab_tabBarClicked(int index);

    void on_clear_all_lost_book_clicked();

    void on_lib_borrowed_books_detail_clicked();

    void on_clear_noti_librarian_button_clicked();

    void on_clear_all_noti_librarian_button_clicked();

    void on_search_books_returnPressed();

    void on_refresh_book_button_clicked();

    void advanced_book_search(QString BName, QString Genre, QString Author, QString Publisher);

    void on_find_book_button_clicked();

private:
    Ui::MainWindow *ui;
    Database data;
    CurrentUser user;
    int bookAmount;
    void set_reader();
    void set_usermanager();
    void set_librarian();
    void login();
    void show_reader_noti();
    void get_user_role(QString roleid);
    void get_current_user(QString userID);
    void send_request_to_librarian(QString userID, QString borrowBookID);
    void get_librarian_noti();
    void show_accounts();
    void resetRealAmountOfBooks();
    void show_reader_borrowed_books();
    void show_lost_books();
    void show_lib_borrowed_books();
};

#endif // MAINWINDOW_H
