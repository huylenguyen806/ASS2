#include "managebooks.h"
#include "ui_managebooks.h"
managebooks::managebooks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::managebooks)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
}
QByteArray world_bytearray_pdf;
managebooks::~managebooks()
{
    delete ui;
}
void managebooks::connect_database()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(qApp->applicationDirPath() + "/database/libpro.sqlite");
    if(!mydb.open())
           {
                QMessageBox *alert = new QMessageBox();
                alert->setText("Error: connection with database failed");
                alert->setWindowIcon(QIcon(":/images/error.png"));
                alert->setWindowTitle("Error");
                alert->show();
           }
           else
           {
              qDebug() << "Database: connection ok";
           }
}
void managebooks::disconnect_database()
{
    mydb.close();
    mydb=QSqlDatabase();
    mydb.removeDatabase(mydb.connectionName());
}
void managebooks::show_book_to_edit(QString bookid)
{
        ui->stackedWidget_manage_bok->setCurrentWidget(ui->page_edit_book_2);
        connect_database();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM BOOKS WHERE BOOKID='"+bookid+"' ");
        qry.exec();
        qry.first();
        ui->label_bookid->setText(qry.value(0).toString());
        ui->lineEdit_bookname_2->setText(qry.value(1).toString());
        ui->lineEdit_publisheddate_2->setText(qry.value(2).toString());
        ui->lineEdit_author_2->setText(qry.value(3).toString());
        ui->lineEdit_publisher_2->setText(qry.value(4).toString());
        ui->lineEdit_genre_2->setText(qry.value(5).toString());
        QByteArray byte=qry.value(6).toByteArray();
        QPixmap pix;
        pix.loadFromData(byte);
        ui->label_show_image->setPixmap(pix);
        ui->label_show_image->setScaledContents(true);
        ui->lineEdit_amount_2->setText(qry.value(7).toString());
        disconnect_database();
}
void managebooks::show_book_to_add()
{
    ui->stackedWidget_manage_bok->setCurrentWidget(ui->page_add_book);
    automaticlly_create_bookid();
    QPixmap p=NULL;
    ui->label_show_image_3->setPixmap(p);
}

void managebooks::finish_edit_book()
{
       QPixmap const *pix=ui->label_show_image->pixmap();
       QByteArray bArray=convert_label_image_to_bytearray(pix);
       QString temp_id=ui->label_bookid->text();
       connect_database();
       QSqlQuery qry;
       qry.prepare("UPDATE BOOKS SET BNAME=:name, PUBLISHEDDATE=:date, AUTHOR=:a, PUBLISHER=:pub, KIND=:k, IMAGE=:i, AMOUNT=:amount,PDF=:pdf WHERE BOOKID='"+temp_id+"'");
       qry.bindValue(":name",ui->lineEdit_bookname_2->text());
       qry.bindValue(":date",ui->lineEdit_publisheddate_2->text());
       qry.bindValue(":a",ui->lineEdit_author_2->text());
       qry.bindValue(":pub",ui->lineEdit_publisher_2->text());
       qry.bindValue(":k",ui->lineEdit_genre_2->text());
       qry.bindValue(":i",bArray,QSql::In | QSql::Binary);
       qry.bindValue(":amount",ui->lineEdit_amount_2->text());
       qry.bindValue(":pdf",world_bytearray_pdf,QSql::In|QSql::Binary);
       qry.exec();
       world_bytearray_pdf=NULL;
       disconnect_database();
}
QString managebooks::browse_image()
{
    QString file_image=QFileDialog::getOpenFileName(this,"Select Image",QString(),"Image File(*.png)");
    return file_image;
}
QString managebooks::browse_pdf()
{
    QString file_pdf=QFileDialog::getOpenFileName(this,"Select contents of book (file pdf)",QString(),"Pdf File(*.pdf)");
    return file_pdf;
}

void managebooks::on_pushButton_browse_image_2_clicked()
{
    QString fileimage=browse_image();
    QFile image(fileimage);
    if(!image.open(QIODevice::ReadOnly)) return;
    QByteArray byte_image=image.readAll();
    QPixmap pix;
     pix.loadFromData(byte_image);
     ui->label_show_image->setPixmap(pix);
}

void managebooks::on_pushButton_browse_content_2_clicked()
{
    QString filepdf=browse_pdf();
    QFile pdf(filepdf);
    if(!pdf.open(QIODevice::ReadOnly)) return;
    QByteArray bytearray_pdf=pdf.readAll();
    world_bytearray_pdf=bytearray_pdf;
    if(filepdf!="")
        ui->label_notification_of_browse_pdf->setText("Uploaded new contents");
}
void managebooks::finish_add_book()
{
        QPixmap const *pix=ui->label_show_image_3->pixmap();
        QByteArray bimage=convert_label_image_to_bytearray(pix);
        connect_database();
        QSqlQuery qry(mydb);
        qry.prepare("INSERT INTO BOOKS (BOOKID,BNAME,PUBLISHEDDATE,AUTHOR,PUBLISHER,KIND,IMAGE,AMOUNT,PDF) VALUES(:id,:name,:date,:a,:pub,:k,:i,:amount,:pdf)");
        qry.bindValue(":id",ui->label_bookid_3->text());
        qry.bindValue(":name",ui->lineEdit_bookname_3->text());
        qry.bindValue(":date",ui->lineEdit_publisheddate_3->text());
        qry.bindValue(":a",ui->lineEdit_author_3->text());
        qry.bindValue(":pub",ui->lineEdit_publisher_3->text());
        qry.bindValue(":k",ui->lineEdit_genre_3->text());
        qry.bindValue(":i",bimage,QSql::In | QSql::Binary);
        qry.bindValue(":amount",ui->lineEdit_amount_3->text());
        qry.bindValue(":pdf",world_bytearray_pdf,QSql::In|QSql::Binary);
        qry.exec();
        world_bytearray_pdf=NULL;
        disconnect_database();
}

void managebooks::on_pushButton_browse_content_3_clicked()
{
    QString file_add_pdf=browse_pdf();
    QFile add_pdf(file_add_pdf);
    if(!add_pdf.open(QIODevice::ReadOnly)) return;
    QByteArray pdf=add_pdf.readAll();
    world_bytearray_pdf=pdf;
    if(file_add_pdf!="")
        ui->label_notification_of_browse_pdf_3->setText("Uploaded content of book");
}

void managebooks::on_pushButton_browse_image_3_clicked()
{
    QString fileimage=browse_image();
    QFile image(fileimage);
    if(!image.open(QIODevice::ReadOnly)) return;
    QByteArray byte_image=image.readAll();
    QPixmap pix;
     pix.loadFromData(byte_image);
     ui->label_show_image_3->setPixmap(pix);
     ui->label_show_image_3->setScaledContents(true);
}
void managebooks::automaticlly_create_bookid()
{
    connect_database();
    QSqlQuery qry(mydb);
    qry.exec("SELECT BOOKID FROM BOOKS");
    qry.last();
    QString temp=qry.value(0).toString();
    QString last_bookid;
    int temp_bookid=0;
    for(int i=2;i<temp.length();++i)
        last_bookid.append(temp[i]);
    temp_bookid=last_bookid.toInt();
    ++temp_bookid;
    temp.clear();
    if(temp_bookid<10)
        temp="BK000"+QString::number(temp_bookid);
    else if(temp_bookid<100)
        temp="BK00"+QString::number(temp_bookid);
    else if(temp_bookid<1000)
        temp="BK0"+QString::number(temp_bookid);
    else
        temp="BK"+QString::number(temp_bookid);
    ui->label_bookid_3->setText(temp);
    disconnect_database();
}

void managebooks::on_pushButton_OK_2_clicked()
{
    bool flag=true;
    if(ui->lineEdit_bookname_2->text().isEmpty())
    {
        ui->notification_bookname_2->setText("<font color='red'>Please enter this book's name</font color>");
        flag=false;
    }
    if(ui->lineEdit_publisheddate_2->text().isEmpty())
    {
        ui->notification_publishedday_2->setText("<font color='red'>Please enter this book's published date</font color>");
        flag=false;
    }
    if(ui->lineEdit_author_2->text().isEmpty())
    {
        ui->notification_author_2->setText("<font color='red'>Please enter author's name</font color>");
        flag=false;
    }
    if(ui->lineEdit_genre_2->text().isEmpty())
    {
        ui->notification_kind_2->setText("<font color='red'>Please enter this book's genre</font color>");
        flag=false;
    }
    if(ui->label_show_image->pixmap()->isNull())
    {
        ui->notification_show_image_2->setText("<font color='red'>Please insert image of this book</font color>");
        flag=false;
    }
    if(flag)
    {
        finish_edit_book();
        this->close();
        show_table_manage_book_widget();
    }
}

void managebooks::on_pushButton_Cancel_2_clicked()
{
    world_bytearray_pdf=NULL;
    this->close();
    show_table_manage_book_widget();
}
void managebooks::show_table_manage_book_widget()
{
    MainWindow *table_manage_books=new MainWindow;
    table_manage_books->show();
    table_manage_books->show_table_manage_book();
}

void managebooks::on_pushButton_OK_3_clicked()
{
    bool flag=true;
    if(ui->lineEdit_bookname_3->text().isEmpty())
    {
        ui->notification_bookname3->setText("<font color='red'>Please enter this book's name</font color>");
        flag=false;
    }
    if(ui->lineEdit_publisheddate_3->text().isEmpty())
    {
        ui->notification_publisheddate_3->setText("<font color='red'>Please enter this book's published date</font color>");
        flag=false;
    }
    if(ui->lineEdit_author_3->text().isEmpty())
    {
        ui->notification_author_3->setText("<font color='red'>Please enter author's name</font color>");
        flag=false;
    }
    if(ui->lineEdit_genre_3->text().isEmpty())
    {
        ui->notification_kind_3->setText("<font color='red'>Please enter this book's genre</font color>");
        flag=false;
    }
    if(ui->label_show_image_3->pixmap()->isNull())
    {
        ui->notification_show_image_3->setText("<font color='red'>Please insert image of this book</font color>");
        flag=false;
    }
    if(flag)
    {
        finish_add_book();
        this->close();
        show_table_manage_book_widget();
    }
}

void managebooks::on_pushButton_Cancel_3_clicked()
{
    world_bytearray_pdf=NULL;
    this->close();
    show_table_manage_book_widget();
}
QByteArray managebooks::convert_label_image_to_bytearray(QPixmap const *p)
{
    QByteArray bytearray_image;
    QBuffer temp(&bytearray_image);
    temp.open(QIODevice::WriteOnly);
    p->save(&temp,"PNG");
    return bytearray_image;
}
