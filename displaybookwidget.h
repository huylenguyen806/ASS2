#ifndef DISPLAYBOOKWIDGET_H
#define DISPLAYBOOKWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

class books
{
public:
    books();
    QString title;
    QString author;
    QString content;
    QString publisher;
    QString genre;
    QString language;
};

namespace Ui {
class DisplayBookWidget;
}

class DisplayBookWidget : public QWidget
{
    Q_OBJECT

public:
    books* book_info = new books();
    void set_displaying_book();
    void hideButton();
    void hideRButton();
    explicit DisplayBookWidget(QWidget *parent = 0);
    ~DisplayBookWidget();
signals:
    void put_in_basket_button_clicked(books* book_info);
private slots:
    void on_put_in_basket_button_clicked();

private:
    Ui::DisplayBookWidget *ui;
};

#endif // DISPLAYBOOKWIDGET_H