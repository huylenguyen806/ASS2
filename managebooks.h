#ifndef MANAGEBOOKS_H
#define MANAGEBOOKS_H
#include<QSqlDatabase>
#include <QWidget>
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include<QFileDialog>
#include"mainwindow.h"
namespace Ui {
class managebooks;
}

class managebooks : public QWidget
{
    Q_OBJECT

public:
    explicit managebooks(QWidget *parent = 0);
    ~managebooks();
    void show_book_to_edit(QString);
    void create_new_book();
    void connect_database();
    void disconnect_database();
    void finish_edit_book();
    QSqlDatabase mydb;
    QString browse_image();
    QString browse_pdf();
    void finish_add_book();
    void automaticlly_create_bookid();
    void show_book_to_add();
    void show_table_manage_book_widget();
    QByteArray convert_label_image_to_bytearray(QPixmap const *);

private slots:
    void on_pushButton_browse_image_2_clicked();

    void on_pushButton_browse_content_2_clicked();

    void on_pushButton_browse_content_3_clicked();

    void on_pushButton_browse_image_3_clicked();

    void on_pushButton_OK_2_clicked();

    void on_pushButton_Cancel_2_clicked();

    void on_pushButton_OK_3_clicked();

    void on_pushButton_Cancel_3_clicked();

private:
    Ui::managebooks *ui;
};

#endif // MANAGEBOOKS_H
