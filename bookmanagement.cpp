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

void BookManagement::showBorrowBookInfo(User_c user, Books_c book)
{
    ui->stackedWidget->setCurrentWidget(ui->librarian_noti);
    ui->user_info->setTextFormat(Qt::RichText);
    ui->user_info->setText("<b>Name: </b> " + user.Name + "<br />" +
                           "<b>LibID: </b> " + user.UserID);
    QPixmap pix;
    pix.loadFromData(book.Image);
    ui->book_image->setPixmap(pix);
    ui->book_name->setText(book.BName);
    ui->book_name->setFont(QFont("Myriad Pro",14,QFont::Bold));
    ui->book_info->setTextFormat(Qt::RichText);
    ui->book_info->setText("<b>Author: </b> " + book.Author + "<br />" +
                           "<b>Published Date: </b> " + book.PublishedDate + "<br />" +
                           "<b>Genre: </b> " + book.Kind + "<br />" +
                           "<b>Publisher: </b> " + book.Publisher + "<br />" +
                           "<b>BookID: </b> " + book.BookID);
}

void BookManagement::on_accept_button_clicked()
{
    emit accept_button_signals(this->request);
}

void BookManagement::on_deny_button_clicked()
{
    this->close();
}
