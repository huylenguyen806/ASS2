#include "manageaccount.h"
#include "ui_manageaccount.h"

ManageAccount::ManageAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageAccount)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    setWindowModality(Qt::ApplicationModal);
}

ManageAccount::~ManageAccount()
{
    delete ui;
}

void ManageAccount::on_Cancel_reset_pass_clicked()
{
    ui->reset_pass_account_name->clear();
    ui->reset_pass->clear();
    this->close();
}

void ManageAccount::on_Cancel_edit_account_clicked()
{
    ui->edit_account_name->clear();
    ui->edit_Role_account->clear();
    ui->edit_username_account->clear();
    this->close();
}

void ManageAccount::on_Cancel_add_account_clicked()
{
    ui->add_account_name->clear();
    ui->add_password->clear();
    ui->add_role->clear();
    ui->add_user_name->clear();
    this->close();
}
