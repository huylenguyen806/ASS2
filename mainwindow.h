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
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_edit_book_manage_button_clicked();

    void on_add_account_button_clicked();

    void on_add_book_button_clicked();

    void show_viewer();

    void on_info_button_clicked();

    void on_login_button_clicked();

    void on_close_login_form_button_clicked();

    void clear_all_lineEdit();

    void login();

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

private:
    Ui::MainWindow *ui;
    QSqlDatabase bookdata;
};

#endif // MAINWINDOW_H
