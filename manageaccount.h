#ifndef MANAGEACCOUNT_H
#define MANAGEACCOUNT_H

#include <QWidget>

namespace Ui {
class ManageAccount;
}

class ManageAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ManageAccount(QWidget *parent = 0);
    ~ManageAccount();


public slots:
    void on_Cancel_reset_pass_clicked();

    void on_Cancel_edit_account_clicked();

    void on_Cancel_add_account_clicked();

    void showedit();

    void showadd();

    void showresetpass();

private:
    Ui::ManageAccount *ui;
};

#endif // MANAGEACCOUNT_H
