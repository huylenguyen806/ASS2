#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QFont>
#include <QPushButton>
#include <QString>
class BookWidget
{
public:
    BookWidget();
    void createBookWidget(QWidget *book);
    void createBookButton(QPushButton *button);
    QWidget* createWidgetForDisplayingBook();
    QString get_book_info(QString chose_info);
};

#endif // BOOKWIDGET_H
