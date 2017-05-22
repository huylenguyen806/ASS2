#include "displaybookwidget.h"
#include "ui_displaybookwidget.h"

books::books()
{

}
books::~books()
{

}

void DisplayBookWidget::hideButton()
{
    ui->put_in_basket_button->hide();
}

void DisplayBookWidget::hideRButton()
{
    ui->read_button->hide();
    ui->Return_button->hide();
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

void DisplayBookWidget::on_put_in_basket_button_clicked()
{
    emit put_in_basket_button_clicked(this->book_info);
}

void DisplayBookWidget::set_displaying_book()
{
    ui->title->setTextFormat(Qt::RichText);
    ui->title->setFont(QFont("Myriad Pro",15,QFont::Bold));
    ui->title->setText(book_info->title);
    ui->title->setWordWrap(true);
    ui->content_author->setTextFormat(Qt::RichText);
    ui->content_author->setText("<b>ID: </b>" + book_info->bookID +
                                "<br />" + "<b>Author: </b>" + book_info->author);
    ui->content_author->setFont(QFont("Myriad Pro",12));
    ui->content_author->setWordWrap(true);
    ui->publisher_genre_language->setTextFormat(Qt::RichText);
    ui->publisher_genre_language->setText("<b>Publisher: </b>" + book_info->publisher + "<br />"
                                          + "<b>Genre: </b>" + book_info->genre +
                                          "<br /><b>Publish Date: </b>" + book_info->publishedDate);
    ui->publisher_genre_language->setFont(QFont("Myriad Pro",12));
    ui->publisher_genre_language->setWordWrap(true);
    QPixmap pix;
    pix.loadFromData(book_info->Image);
    pix.scaledToWidth(50);
    ui->image->setPixmap(pix);
}

void DisplayBookWidget::hideDuration()
{
    ui->duration->hide();
    ui->label->hide();
}

void DisplayBookWidget::on_set_all_duration_signal(int duration)
{
    ui->duration->setValue(duration);
}
