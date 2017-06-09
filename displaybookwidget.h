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
    int amount;
    int realAmount;
    QByteArray Pdf;
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
    void resetRealAmount();
    void show_only_book_info();
    QString returndate;
    void set_displaying_borrowed_book();
    explicit DisplayBookWidget(QWidget *parent = 0);
    ~DisplayBookWidget();
signals:
    void put_in_basket_button_clicked(books* book_info);
    void send_each_duration(QString bookID, int duration);
    void return_book(books *return_book);
    void read_book(books *read_book);
    void lost_book(books *lost);
private slots:
    void on_put_in_basket_button_clicked();
    void set_all_duration_signal(int duration);

    void on_duration_valueChanged(int arg1);

    void on_Return_button_clicked();

    void on_read_button_clicked();

    void on_lost_book_button_clicked();

private:
    Ui::DisplayBookWidget *ui;
};

#endif // DISPLAYBOOKWIDGET_H
