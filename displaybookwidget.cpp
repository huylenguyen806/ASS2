#include "displaybookwidget.h"
#include "ui_displaybookwidget.h"

books::books()
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
    ui->content_author->setText("<b>Content: </b>" + book_info->content +
                                "<br />" + "<b>Author: </b>" + book_info->author);
    ui->content_author->setFont(QFont("Myriad Pro",12));
    ui->content_author->setWordWrap(true);
    ui->publisher_genre_language->setTextFormat(Qt::RichText);
    ui->publisher_genre_language->setText("<b>Publisher: </b>" + book_info->publisher + "<br />"
                                          + "<b>Genre: </b>" + book_info->genre +
                                          "<br /><b>Language: </b>" + book_info->language);
    ui->publisher_genre_language->setFont(QFont("Myriad Pro",12));
    ui->publisher_genre_language->setWordWrap(true);
}
