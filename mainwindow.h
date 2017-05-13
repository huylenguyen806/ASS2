#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "bookmanagement.h"
#include "manageaccount.h"
#include <QPicture>
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
    void on_basket_clicked();

    void on_edit_book_manage_button_clicked();

    void on_add_account_button_clicked();

    void on_add_book_button_clicked();

    void show_viewer();

    void on_info_button_clicked();

    void on_login_button_clicked();

    void on_close_login_form_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
