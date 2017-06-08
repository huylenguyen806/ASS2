#include "readernotifications.h"
#include "ui_readernotifications.h"
#include <QMessageBox>

ReaderNotifications::ReaderNotifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReaderNotifications)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowIcon(QIcon(":/images/detail_icon.ico"));
}

ReaderNotifications::~ReaderNotifications()
{
    delete ui;
}

void ReaderNotifications::Create(ReaderNoti_c noti, Books_c book)
{
    if(noti.BookID.isEmpty() == true || noti.account_no.isEmpty() == true){
        if(!noti.BookID.isEmpty()){
            ui->content_detail->setFont(QFont("MyriadPro",14));
            ui->content_detail->setText(noti.content);
            ui->content_detail->setWordWrap(true);
            ui->bookname->setTextFormat(Qt::RichText);
            ui->bookname->setFont(QFont("Myriad Pro",14,QFont::Bold));
            ui->bookname->setText(book.BName);
            ui->bookname->setWordWrap(true);
            ui->bookinfo->setTextFormat(Qt::RichText);
            ui->bookinfo->setFont(QFont("Myriad Pro",12));
            ui->bookinfo->setText("<b>Author: </b> " + book.Author + "<br />" +
                                   "<b>Published Date: </b> " + book.PublishedDate + "<br />" +
                                   "<b>Genre: </b> " + book.Kind + "<br />" +
                                   "<b>Publisher: </b> " + book.Publisher + "<br />" +
                                   "<b>BookID: </b> " + book.BookID);
            ui->bookinfo->setWordWrap(true);
            QPixmap pix;
            pix.loadFromData(book.Image);
            ui->bookimage->setPixmap(pix);
            ui->stackedWidget->setCurrentWidget(ui->book_notifications);
            setWindowTitle("Notification about book");
        }
        else if(!noti.account_no.isEmpty()){
            ui->content_user_detail->setTextFormat(Qt::RichText);
            ui->content_user_detail->setText(noti.content + "<br/>On the date: " + noti.date);
            ui->content_user_detail->setFont(QFont("Myriad Pro",14,-1,false));
            ui->stackedWidget->setCurrentWidget(ui->info_noifications);
            setWindowTitle("Notification about your info");
        }
    }
}

void ReaderNotifications::on_delete_b_clicked()
{
    QMessageBox *newbox = new QMessageBox();
    newbox->setText("Are you sure you want to remove this notification?");
    newbox->setWindowIcon(QIcon(":/images/warning.png"));
    newbox->setWindowTitle("Warning");
    QPushButton *Y = newbox->addButton(QMessageBox::Yes);
    QPushButton *N = newbox->addButton(QMessageBox::No);
    newbox->setDefaultButton(N);
    newbox->exec();
    if(newbox->clickedButton() == Y){
        emit delete_noti(this->noti);
        this->close();
    }
    else if(newbox->clickedButton() == N)
        this->close();
}

void ReaderNotifications::on_delete_u_clicked()
{
    QMessageBox *newbox = new QMessageBox();
    newbox->setText("Are you sure you want to remove this notification?");
    newbox->setWindowIcon(QIcon(":/images/warning.png"));
    newbox->setWindowTitle("Warning");
    QPushButton *Y = newbox->addButton(QMessageBox::Yes);
    QPushButton *N = newbox->addButton(QMessageBox::No);
    newbox->exec();
    newbox->setDefaultButton(N);
    if(newbox->clickedButton() == Y){
        emit delete_noti(this->noti);
        this->close();
    }
    else if(newbox->clickedButton() == N){
        this->close();
        newbox->close();
    }
}
