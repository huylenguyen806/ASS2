#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_basket_clicked()
{
    QMessageBox *noti = new QMessageBox();
    noti->setText("The book is now in your basket.");
    noti->show();
}
