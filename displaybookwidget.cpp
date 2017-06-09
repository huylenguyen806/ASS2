#include "displaybookwidget.h"
#include "ui_displaybookwidget.h"

books::books()
{

}
books::~books()
{

}

void DisplayBookWidget::show_only_book_info()
{
    hideButton();
    hideRButton();
    hideDuration();
}

void DisplayBookWidget::hideButton()
{
    ui->put_in_basket_button->hide();
}

void DisplayBookWidget::hideRButton()
{
    ui->read_button->hide();
    ui->Return_button->hide();
    ui->lost_book_button->hide();
}

DisplayBookWidget::DisplayBookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayBookWidget)
{
    ui->setupUi(this);
}

DisplayBookWidget::~DisplayBookWidget()
{
    delete ui;
}

void DisplayBookWidget::resetRealAmount()
{
    ui->content_author->setTextFormat(Qt::RichText);
    ui->content_author->setText("<b>ID: </b>" + book_info->bookID +
                                "<br />" + "<b>Author: </b>" + book_info->author +
                                "<br /><b>Amount: </b>" + QString::number(book_info->realAmount) +
                                "/" +QString::number(book_info->amount));
    ui->content_author->setFont(QFont("Myriad Pro",14));
    ui->content_author->setWordWrap(true);
}

void DisplayBookWidget::on_put_in_basket_button_clicked()
{
    emit put_in_basket_button_clicked(this->book_info);
}

void DisplayBookWidget::set_displaying_borrowed_book()
{
    ui->title->setTextFormat(Qt::RichText);
    ui->title->setFont(QFont("Myriad Pro",16,QFont::Bold));
    ui->title->setText(book_info->title);
    ui->title->setWordWrap(true);
    ui->content_author->setTextFormat(Qt::RichText);
    ui->content_author->setText("<b>ID: </b>" + book_info->bookID +
                                "<br />" + "<b>Author: </b>" + book_info->author +
                                "<br /><b>Return date: </b>" + returndate);
    ui->content_author->setFont(QFont("Myriad Pro",14));
    ui->content_author->setWordWrap(true);
    ui->publisher_genre_language->setTextFormat(Qt::RichText);
    ui->publisher_genre_language->setText("<b>Publisher: </b>" + book_info->publisher + "<br />"
                                          + "<b>Genre: </b>" + book_info->genre +
                                          "<br /><b>Publish Date: </b>" + book_info->publishedDate);
    ui->publisher_genre_language->setFont(QFont("Myriad Pro",14));
    ui->publisher_genre_language->setWordWrap(true);
    QPixmap pix;
    pix.loadFromData(book_info->Image);
    ui->image->setPixmap(pix);
}

void DisplayBookWidget::set_displaying_book()
{
    ui->title->setTextFormat(Qt::RichText);
    ui->title->setFont(QFont("Myriad Pro",16,QFont::Bold));
    ui->title->setText(book_info->title);
    ui->title->setWordWrap(true);
    ui->content_author->setTextFormat(Qt::RichText);
    ui->content_author->setText("<b>ID: </b>" + book_info->bookID +
                                "<br />" + "<b>Author: </b>" + book_info->author +
                                "<br /><b>Real amount: </b>" + QString::number(book_info->realAmount) +
                                "/" +QString::number(book_info->amount));
    ui->content_author->setFont(QFont("Myriad Pro",14));
    ui->content_author->setWordWrap(true);
    ui->publisher_genre_language->setTextFormat(Qt::RichText);
    ui->publisher_genre_language->setText("<b>Publisher: </b>" + book_info->publisher + "<br />"
                                          + "<b>Genre: </b>" + book_info->genre +
                                          "<br /><b>Publish Date: </b>" + book_info->publishedDate);
    ui->publisher_genre_language->setFont(QFont("Myriad Pro",14));
    ui->publisher_genre_language->setWordWrap(true);
    QPixmap pix;
    pix.loadFromData(book_info->Image);
    ui->image->setPixmap(pix);
}

void DisplayBookWidget::hideDuration()
{
    ui->duration->hide();
    ui->label->hide();
    ui->duration_label->hide();
}

void DisplayBookWidget::set_all_duration_signal(int duration)
{
    ui->duration->setValue(duration);
}


void DisplayBookWidget::on_duration_valueChanged(int arg1)
{
    emit send_each_duration(this->book_info->bookID, arg1);
}

void DisplayBookWidget::on_Return_button_clicked()
{
    emit return_book(this->book_info);
}

void DisplayBookWidget::on_read_button_clicked()
{
    emit read_book(this->book_info);
}

void DisplayBookWidget::on_lost_book_button_clicked()
{
    emit lost_book(this->book_info);
}
