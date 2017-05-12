#include "bookmanagement.h"
#include "ui_bookmanagement.h"

BookManagement::BookManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookManagement)
{
    ui->setupUi(this);
}

BookManagement::~BookManagement()
{
    delete ui;
}
