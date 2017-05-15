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
    QWidget* createBookWidget(QString name, QString content, QString artist, QString Publishing_house, QString genre);
    void createBookButton(QPushButton *button);
    QString get_book_info(QString chose_info);
};

#endif // BOOKWIDGET_H
