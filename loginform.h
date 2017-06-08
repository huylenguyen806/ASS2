#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class loginform;
}

class loginform : public QWidget
{
    Q_OBJECT

public:
    explicit loginform(QWidget *parent = 0);
    ~loginform();

private slots:
    void on_close_login_form_button_clicked();

private:
    Ui::loginform *ui;
};

#endif // LOGINFORM_H
