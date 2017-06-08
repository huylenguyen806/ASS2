#include "loginform.h"
#include "ui_loginform.h"

loginform::loginform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginform)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
}

loginform::~loginform()
{
    delete ui;
}

void loginform::on_close_login_form_button_clicked()
{
    this->close();
    MainWindow w;
    w.show();
}
