#include "advancedsearch.h"
#include "ui_advancedsearch.h"

AdvancedSearch::AdvancedSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedSearch)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowIcon(QIcon(":/images/search.png"));
    setWindowTitle("Advanced Search");
}

AdvancedSearch::~AdvancedSearch()
{
    delete ui;
}

void AdvancedSearch::set_book_search()
{
    ui->stackedWidget->setCurrentWidget(ui->book_search);
}

void AdvancedSearch::on_ok_book_search_clicked()
{
    QString BName = ui->book_title->text();
    QString Genre = ui->genre->text();
    QString Author = ui->author->text();
    QString Publisher = ui->publisher->text();
    emit send_advanced_book_search(BName, Genre, Author, Publisher);
    this->close();
}

void AdvancedSearch::on_cancel_book_search_clicked()
{
    this->close();
}
