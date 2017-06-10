#ifndef ADVANCEDSEARCH_H
#define ADVANCEDSEARCH_H

#include <QDialog>

namespace Ui {
class AdvancedSearch;
}

class AdvancedSearch : public QDialog
{
    Q_OBJECT

public:
    void set_book_search();
    explicit AdvancedSearch(QWidget *parent = 0);
    ~AdvancedSearch();

signals:
    void send_advanced_book_search(QString BName, QString Genre, QString Author, QString Publisher);

private slots:
    void on_ok_book_search_clicked();

    void on_cancel_book_search_clicked();

private:
    Ui::AdvancedSearch *ui;
};

#endif // ADVANCEDSEARCH_H
