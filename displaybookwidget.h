#ifndef DISPLAYBOOKWIDGET_H
#define DISPLAYBOOKWIDGET_H

#include <QWidget>
#include <QByteArray>
#include <QPixmap>
#include <QImage>

class books
{
public:
    books();
    ~books();
    QString title;
    QString author;
    QString bookID;
    QString publisher;
    QString genre;
    QString publishedDate;
    QByteArray Image;
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
    void hideDuration();
    explicit DisplayBookWidget(QWidget *parent = 0);
    ~DisplayBookWidget();
signals:
    void put_in_basket_button_clicked(books* book_info);
private slots:
    void on_put_in_basket_button_clicked();
    void set_all_duration_signal(int duration);
private:
    Ui::DisplayBookWidget *ui;
};

#endif // DISPLAYBOOKWIDGET_H
