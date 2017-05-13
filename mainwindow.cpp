#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    show_viewer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_viewer()
{
    ui->role_select->clear();
    ui->role_select->addItem("Viewer");
    ui->main_ui_2->setCurrentWidget(ui->not_login);
    ui->main_ui->setCurrentWidget(ui->find_books);
}

void MainWindow::on_basket_clicked()
{
    if(ui->login_button->text() == "Login")
    {
        QMessageBox *alert = new QMessageBox();
        alert->setWindowTitle("Error");
        alert->setText("Please login to continue.");
        alert->show();
    }
    else{
        QMessageBox *noti = new QMessageBox();
        noti->setWindowTitle("Success");
        noti->setText("The book is now in your basket.");
        noti->show();
    }
}

void MainWindow::on_edit_book_manage_button_clicked()
{
    BookManagement *edit = new BookManagement();
    edit->show();
}

void MainWindow::on_add_account_button_clicked()
{
    ManageAccount *add = new ManageAccount();
    add->showadd();
    add->show();
}

void MainWindow::on_add_book_button_clicked()
{
    BookManagement *add = new BookManagement();
    add->showaddbook();
    add->show();
}

void MainWindow::on_info_button_clicked()
{
    if(ui->login_button->text() == "Login")
    {
        QMessageBox *alert = new QMessageBox();
        alert->setWindowTitle("Error");
        alert->setText("Please login to see your info.");
        alert->show();
    }
}

void MainWindow::on_login_button_clicked()
{
    ui->mainStack->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_close_login_form_button_clicked()
{
    ui->mainStack->setCurrentWidget(ui->rolePage);
}
