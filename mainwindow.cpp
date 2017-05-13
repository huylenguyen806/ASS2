#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/Libpro_icon.ico"));
    show_viewer();
    createBookWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{

}

void MainWindow::createBookWidget()
{
    //vertical layout in book_scoll_area
    QVBoxLayout *vlayout = new QVBoxLayout(ui->book_scoll_area);
    for(int i = 0; i < 10; ++i){
    //create widget contains books' info and button
    QWidget *newbook = new QWidget();
    newbook->setMinimumHeight(100);
    newbook->setMaximumHeight(100);
    //create horizontal layout
    QHBoxLayout *newlayout = new QHBoxLayout(newbook);
    //create label contains books' info
    QLabel *newlabel = new QLabel();
    newlabel->setText("Newbook");
    //create button
    QPushButton *newbutton = new QPushButton();
    newbutton->setText("Put in basket");
    //create line
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    //add widgets
    newlayout->addWidget(newlabel,5,0);
    newlayout->addWidget(newbutton,1,0);
    vlayout->addWidget(newbook,0,0);
    vlayout->addWidget(line,0,0);
    }
    //create spacer
    QSpacerItem *newspacer = new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
    vlayout->addSpacerItem(newspacer);
}

void MainWindow::createMessageBox(QString type, QString text)
{
    QMessageBox *message = new QMessageBox();
    message->setText(text);
    if(type == "Error")
    {
        message->setWindowTitle("Error");
        message->setWindowIcon(QIcon(":/images/error.png"));
    }
    else if (type == "Warning")
    {
        message->setWindowTitle("Warning");
        message->setWindowIcon(QIcon(":/images/warning.png"));
    }
    else if(type == "OK")
    {
        message->setWindowTitle("Success");
        message->setWindowIcon(QIcon(":/images/OK.png"));
    }
    message->show();
}

void MainWindow::clear_all_lineEdit()
{
    foreach (QLineEdit *sth, findChildren<QLineEdit* >())
    {
        sth->clear();
    }
}

void MainWindow::show_viewer()
{
    ui->role_select->clear();
    ui->role_select->addItem("Viewer");
    ui->mainStack->setCurrentWidget(ui->rolePage);
    ui->main_ui_2->setCurrentWidget(ui->not_login);
    ui->main_ui->setCurrentWidget(ui->find_books);
}

void MainWindow::on_basket_clicked()
{
    if(ui->login_button->text() == "Login")
    {
        createMessageBox("Error", "Please login to continue.");
    }
    else{
        createMessageBox("OK", "The book is now in your basket.");
    }
}

void MainWindow::on_edit_book_manage_button_clicked()
{
    BookManagement *edit = new BookManagement();
    edit->showeditbook();
    edit->show();
}

void MainWindow::on_add_account_button_clicked()
{
    ManageAccount *add = new ManageAccount();
    add->showadd();
    add->show();
}

void MainWindow::on_add_book_button_clicked()
{
    BookManagement *add = new BookManagement();
    add->showaddbook();
    add->show();
}

void MainWindow::on_info_button_clicked()
{
    if(ui->login_button->text() == "Login")
    {
        createMessageBox("Error", "Please login to see your info.");
    }
    else if(ui->login_button->text() == "Logout")
    {
        ui->main_ui->setCurrentWidget(ui->info);
    }
}

void MainWindow::on_login_button_clicked()
{
    ui->mainStack->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_close_login_form_button_clicked()
{
    ui->mainStack->setCurrentWidget(ui->rolePage);
    clear_all_lineEdit();
}

void MainWindow::on_reader_find_book_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->find_books);
    clear_all_lineEdit();
}

void MainWindow::on_goto_basket_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->basket_stack);
}

void MainWindow::on_reader_change_pass_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->change_password);
    clear_all_lineEdit();
}

void MainWindow::on_manager_change_pass_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->change_password);
    clear_all_lineEdit();
}

void MainWindow::on_librarian_change_pass_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->change_password);
    clear_all_lineEdit();
}

void MainWindow::on_reader_noti_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->reader_noti);
}

void MainWindow::on_manage_account_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->account_manage);
}

void MainWindow::on_manage_info_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->user_info_manage);
}

void MainWindow::on_manage_book_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->books_info);
}

void MainWindow::on_manage_demand_button_clicked()
{
    ui->main_ui->setCurrentWidget(ui->reader_demand);
}

void MainWindow::on_reset_pass_button_clicked()
{
    ManageAccount *reset = new ManageAccount();
    reset->showresetpass();
    reset->show();
}
