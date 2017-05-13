#include "bookmanagement.h"
#include "ui_bookmanagement.h"

BookManagement::BookManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookManagement)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    setWindowModality(Qt::ApplicationModal);
}

BookManagement::~BookManagement()
{
    delete ui;
}

void BookManagement::on_cancel_add_book_button_clicked()
{
    ui->about_add->clear();
    ui->artist_add->clear();
    ui->book_name_add->clear();
    ui->genre_add->clear();
    ui->publishing_house_add->clear();
    this->close();
}

void BookManagement::on_cancel_edit_book_button_clicked()
{
    ui->about_edit->clear();
    ui->artist_edit->clear();
    ui->book_name_edit->clear();
    ui->genre_edit->clear();
    ui->publishing_house_edit->clear();
    this->close();
}

void BookManagement::showaddbook()
{
    ui->stackedWidget->setCurrentWidget(ui->add_book);
}

void BookManagement::showeditbook()
{
    ui->stackedWidget->setCurrentWidget(ui->edit_book);
}
