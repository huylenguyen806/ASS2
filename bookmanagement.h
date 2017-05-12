#ifndef BOOKMANAGEMENT_H
#define BOOKMANAGEMENT_H

#include <QWidget>

namespace Ui {
class BookManagement;
}

class BookManagement : public QWidget
{
    Q_OBJECT

public:
    explicit BookManagement(QWidget *parent = 0);
    ~BookManagement();

private:
    Ui::BookManagement *ui;
};

#endif // BOOKMANAGEMENT_H
