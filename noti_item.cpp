#include "noti_item.h"
#include "ui_noti_item.h"

noti_item::noti_item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::noti_item)
{
    ui->setupUi(this);
}

noti_item::~noti_item()
{
    delete ui;
}

void noti_item::set_info(QString info)
{
    ui->info->setTextFormat(Qt::RichText);
    ui->info->setFont(QFont("Myriad Pro",14));
    ui->info->setText(info);
    ui->info->setWordWrap(true);
}

void noti_item::hide_reader_noti_detail()
{
    ui->pushButton->hide();
}

void noti_item::hide_lost_book_detail()
{
    ui->lostbook_detail->hide();
}

void noti_item::on_pushButton_clicked()
{
    emit show_detail(this->noti,this->book);
    emit selectItem(this->item);
}

void noti_item::set_lost_book_info(QString UserID, QString UserName, QString BookID, QString BName)
{
    ui->info->setTextFormat(Qt::RichText);
    ui->info->setFont(QFont("Myriad Pro",14));
    ui->info->setText(UserID + " : " + UserName + "<br />" + BookID + " : " + BName);
    ui->info->setWordWrap(true);
}

void noti_item::on_lostbook_detail_clicked()
{
    emit lost_book_detail(this->user, this->book);
}
