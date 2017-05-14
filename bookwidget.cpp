#include "bookwidget.h"

BookWidget::BookWidget()
{

}

void BookWidget::createBookWidget(QWidget *book)
{
    book->setMaximumHeight(150);
    book->setMinimumHeight(150);
    QHBoxLayout *hbox = new QHBoxLayout();
    QVBoxLayout *vbox = new QVBoxLayout(book);
    QLabel *book_name = new QLabel();
    QLabel *content = new QLabel();
    QLabel *artist = new QLabel();

    //add book's info here
    content->setText("Content: bla bla bla");
    content->setFont(QFont("Myriad Pro",12));
    content->setWordWrap(true);
    book_name->setText("flajhlgkjgafhflsfhsafjg");
    book_name->setFont(QFont("Myriad Pro",15,QFont::Bold));
    book_name->setWordWrap(true);
    artist->setText("Artist: blabla bla\nPublishing house: Blaflsh\nGenre: flafsjflsfs");
    artist->setFont(QFont("Myriad Pro",12));
    artist->setWordWrap(true);

    hbox->addWidget(content,3,0);
    hbox->addWidget(artist,2,0);
    vbox->addWidget(book_name,0,0);
    vbox->addLayout(hbox,1);
}

void BookWidget::createBookButton(QPushButton *button)
{
    button->setText("Put in basket");
    button->setStyleSheet("QPushButton {height: 75px;"
                                 "background-color: rgb(199,237,252);"
                                 "border-style: outset;"
                                 "border-width: 1px;"
                                 "border-radius: 20px;"
                                 "border-color: white;"
                                 "font:normal 200 12pt Myriad Pro;"
                                 "min-width: 5em;"
                                 "padding: 2px;}"
                                 "QPushButton:pressed {background-color: rgb(178,231,250);"
                                 "border-style: outset;"
                                 "border-style: inset;}"
                                 "QPushButton:hover {background-color: rgb(178,231,250);"
                                 "border-style: inset;}");
}

QWidget *BookWidget::createWidgetForDisplayingBook()
{
    QWidget *newbook = new QWidget();
    QWidget *book = new QWidget();
    createBookWidget(book);
    QPushButton *newbutton = new QPushButton();
    createBookButton(newbutton);
    QHBoxLayout *hlayout = new QHBoxLayout(newbook);
    hlayout->addWidget(book,6,0);
    hlayout->addWidget(newbutton,1,0);
    return newbook;
}

QString BookWidget::get_book_info(QString chose_info)
{
    QString book_ID;
    QString book_name;
    QString artist;
    QString publishing_house;
    QString genre;
    QString content;
    //add code get book from database here
    if(chose_info == "book_ID")
        return book_ID;
    else if(chose_info == "book_name")
        return book_name;
    else if(chose_info == "artist")
        return artist;
    else if(chose_info == "publishing_house")
        return publishing_house;
    else if(chose_info == "genre")
        return genre;
    else if(chose_info == "content")
        return content;
}
