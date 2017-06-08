#include "bookmanagement.h"
#include "ui_bookmanagement.h"
#include <QVariant>
#include <QMessageBox>

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

void BookManagement::show_lost_book_widget(User_c user, Books_c book)
{
    this->UserID = user.UserID;
    this->BookID = book.BookID;
    ui->stackedWidget->setCurrentWidget(ui->manage_lost_books);
    ui->lost_book_user_info->setTextFormat(Qt::RichText);
    ui->lost_book_user_info->setFont(QFont("Myriad Pro",14));
    ui->lost_book_user_info->setText("<b>Name : </b>" + user.Name + "<br /><b>UserID : </b>" + user.UserID);
    ui->lost_book_user_info->setWordWrap(true);
    ui->book_name_lost->setFont(QFont("Myriad Pro",14,QFont::Bold));
    ui->book_name_lost->setText(book.BName);
    ui->book_name_lost->setWordWrap(true);
    QPixmap pix;
    pix.loadFromData(book.Image);
    ui->book_image_lost->setPixmap(pix);
    ui->book_info_lost->setTextFormat(Qt::RichText);
    ui->book_info_lost->setFont(QFont("Myriad Pro",14));
    ui->book_info_lost->setText("<b>Author: </b> " + book.Author + "<br />" +
                           "<b>Published Date: </b> " + book.PublishedDate + "<br />" +
                           "<b>Genre: </b> " + book.Kind + "<br />" +
                           "<b>Publisher: </b> " + book.Publisher + "<br />" +
                           "<b>BookID: </b> " + book.BookID);
    ui->book_info_lost->setWordWrap(true);
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

void BookManagement::showBorrowBookInfo(User_c user, Books_c book, int duration)
{
    request->UserID = user.UserID;
    request->BorrowBookID = book.BookID;
    request->Duration = duration;
    ui->stackedWidget->setCurrentWidget(ui->librarian_noti);
    ui->user_info->setTextFormat(Qt::RichText);
    ui->user_info->setText("<b>Name: </b> " + user.Name + "<br />" +
                           "<b>LibID: </b> " + user.UserID);
    QPixmap pix;
    pix.loadFromData(book.Image);
    ui->book_image->setPixmap(pix);
    ui->book_name->setText(book.BName);
    ui->book_name->setFont(QFont("Myriad Pro",14,QFont::Bold));
    ui->book_name->setWordWrap(true);
    ui->book_info->setTextFormat(Qt::RichText);
    ui->book_info->setText("<b>Author: </b> " + book.Author + "<br />" +
                           "<b>Published Date: </b> " + book.PublishedDate + "<br />" +
                           "<b>Genre: </b> " + book.Kind + "<br />" +
                           "<b>Publisher: </b> " + book.Publisher + "<br />" +
                           "<b>BookID: </b> " + book.BookID);
    ui->book_info->setWordWrap(true);
    ui->duration_label->setFont(QFont("Myriad Pro",14,-1,false));
    ui->duration_label->setTextFormat(Qt::RichText);
    if(duration == 1)
        ui->duration_label->setText(" 1 Day");
    else
        ui->duration_label->setText(" " + QVariant(duration).toString() + " Days");
    ui->current_amount->setTextFormat(Qt::RichText);
    ui->current_amount->setFont(QFont("Myriad Pro",14,-1,false));
    ui->current_amount->setText(QString::number(book.realAmmount) + "/" + QString::number(book.Amount));
    if(book.realAmmount == 0)
        ui->accept_button->setDisabled(true);
}

void BookManagement::on_accept_button_clicked()
{
    emit accept_button_signals(this->request);
    this->close();
}

void BookManagement::on_deny_button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->deny_reason);
}

void BookManagement::on_cancel_refusal_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->librarian_noti);
}

void BookManagement::on_ok_refusal_clicked()
{
    if(ui->run_out_of_book->isChecked()){
        QString content = "Fail to borrow (ran out of books)";
        emit send_reason_for_denial(this->request->UserID, this->request->BorrowBookID, content,this->on);
        this->close();
    }
    else if(ui->monthly_cost_unpaid->isChecked()){
        emit send_reason_for_denial(this->request->UserID, this->request->BorrowBookID,
                                    "Fail to borrow (monthly cost unpaid)", this->on);
        this->close();
    }
    else if(ui->different->isChecked()){
        emit send_reason_for_denial(this->request->UserID, this->request->BorrowBookID,
                                    ui->different_reason->toPlainText(), this->on);
        this->close();
    }
}

void BookManagement::on_OK_lost_book_clicked()
{
    message = ui->message_punishment->toPlainText();
    money = ui->money_punishment->text();
    if(!message.isEmpty() && !money.isEmpty()){
        emit send_lost_book_punishment(this->UserID, this->BookID, this->message, this->money);
        this->close();
    }
    else {
        QMessageBox *noti = new QMessageBox();
        noti->setText("Please enter message and money for punishment.");
        noti->setWindowIcon(QIcon(":/images/error.png"));
        noti->setWindowTitle("Error");
        noti->show();
    }
}

void BookManagement::on_Cancel_lost_book_clicked()
{
    this->close();
}
