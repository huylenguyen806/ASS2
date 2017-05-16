#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bookdata = QSqlDatabase::addDatabase("QSQLITE");
    bookdata.setDatabaseName(qApp->applicationDirPath().append("/Books.db"));
    if(!bookdata.open())
    {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Failed to open database of books !");
        alert->show();
    }
    setWindowIcon(QIcon(":/images/Libpro_icon.ico"));
    //show_viewer();
    createDisplayBookWidget();
    createBookManagerWidget();
    ui->manage_user_label->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{

}

void MainWindow::put_in_basket_click(books* book_info)
{
    if(ui->login_button->text() == "Login")
    {
        createMessageBox("Error", "Please login to continue.");
    }
    else{
        createMessageBox("OK", "The book is now in your basket.");
        QListWidgetItem *newitem = new QListWidgetItem();
        DisplayBookWidget* displaybook = new DisplayBookWidget();
        displaybook->book_info->title = book_info->title;
        displaybook->book_info->author = book_info->author;
        displaybook->book_info->content = book_info->content;
        displaybook->book_info->genre = book_info->genre;
        displaybook->book_info->language = book_info->language;
        displaybook->book_info->publisher = book_info->publisher;
        displaybook->set_displaying_book();
        displaybook->hideButton();
        displaybook->hideRButton();
        newitem->setSizeHint(QSize(0,150));
        ui->list_book_in_basket->addItem(newitem);
        ui->list_book_in_basket->setItemWidget(newitem,displaybook);
    }
}

void MainWindow::createBookManagerWidget()
{
    QSqlQuery qry;
    if(qry.exec("SELECT * FROM DATA")){
        int titleIndex = qry.record().indexOf("TITLE");
        int contentIndex = qry.record().indexOf("CONTENT");
        int authorIndex = qry.record().indexOf("AUTHOR");
        int publisherIndex = qry.record().indexOf("PUBLISHER");
        int genreIndex = qry.record().indexOf("GENRE");
        int languageIndex = qry.record().indexOf("LANGUAGE");
        while(qry.next()){
            //get data
            DisplayBookWidget* displaybook = new DisplayBookWidget();
            displaybook->book_info->title = qry.value(titleIndex).toString();
            displaybook->book_info->content = qry.value(contentIndex).toString();
            displaybook->book_info->author = qry.value(authorIndex).toString();
            displaybook->book_info->publisher = qry.value(publisherIndex).toString();
            displaybook->book_info->genre = qry.value(genreIndex).toString();
            displaybook->book_info->language = qry.value(languageIndex).toString();
            displaybook->set_displaying_book();
            displaybook->hideButton();
            displaybook->hideRButton();
            QListWidgetItem *newitem = new QListWidgetItem();
            newitem->setSizeHint(QSize(0,150));
            ui->manage_book_area->addItem(newitem);
            ui->manage_book_area->setItemWidget(newitem,displaybook);
        }
    }
}

void MainWindow::createDisplayBookWidget()
{
    //vertical layout in book_scoll_area
    QVBoxLayout *vlayout = new QVBoxLayout(ui->book_scoll_area);
    QSqlQuery qry;
    if(qry.exec("SELECT * FROM DATA")){
        int titleIndex = qry.record().indexOf("TITLE");
        int contentIndex = qry.record().indexOf("CONTENT");
        int authorIndex = qry.record().indexOf("AUTHOR");
        int publisherIndex = qry.record().indexOf("PUBLISHER");
        int genreIndex = qry.record().indexOf("GENRE");
        int languageIndex = qry.record().indexOf("LANGUAGE");
        while(qry.next()){
            //get data
            DisplayBookWidget* displaybook = new DisplayBookWidget();
            displaybook->book_info->title = qry.value(titleIndex).toString();
            displaybook->book_info->content = qry.value(contentIndex).toString();
            displaybook->book_info->author = qry.value(authorIndex).toString();
            displaybook->book_info->publisher = qry.value(publisherIndex).toString();
            displaybook->book_info->genre = qry.value(genreIndex).toString();
            displaybook->book_info->language = qry.value(languageIndex).toString();
            displaybook->set_displaying_book();
            displaybook->hideRButton();
            vlayout->addWidget(displaybook,0,0);
            //connect to slot
            connect(displaybook,SIGNAL(put_in_basket_button_clicked(books*)),this,SLOT(put_in_basket_click(books*)));
        }
        //create spacer
        QSpacerItem *newspacer = new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
        vlayout->addSpacerItem(newspacer);
    }
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
    show_viewer();
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
    if(ui->list_Accounts->selectedItems().size() != 0)
    {
        ManageAccount *reset = new ManageAccount();
        reset->showresetpass();
        reset->show();
    }
    else {
        createMessageBox("Error", "Please choose an account to reset password.");
    }
}

void MainWindow::ListItemClicked(QWidget *widget)
{
    widget->setStyleSheet("background-color: green");
}

void MainWindow::on_edit_account_button_clicked()
{
    if(ui->list_Accounts->selectedItems().size() != 0)
    {
        ManageAccount *edit = new ManageAccount();
        edit->showedit();
        edit->show();
        //add code show info and edit info in database here
    }
    else {
        createMessageBox("Error","Please choose an account to edit.");
    }
}

void MainWindow::on_remove_account_button_clicked()
{
    if(ui->list_Accounts->selectedItems().size() != 0)
    {
        delete ui->list_Accounts->currentItem();
        //add code delete in database here
    }
    else {
        createMessageBox("Error","Please choose an account to remove.");
    }
}

void MainWindow::on_lock_account_button_clicked()
{
    if(ui->list_Accounts->selectedItems().size() != 0)
    {
        //add code lock account in database here
        //if currentItem is locked, show messagebox "This account is already locked."
    }
    else {
        createMessageBox("Error", "Please choose an account to lock");
    }
}

void MainWindow::on_unlock_account_button_clicked()
{
    if(ui->list_Accounts->selectedItems().size() != 0)
    {
        //if currentItem is not locked, show messagebox "This account is already unlocked."
    }
    else{
        createMessageBox("Error", "Please choose an account to unlock.");
    }
}

void MainWindow::on_remove_info_button_clicked()
{
    if(ui->list_Users->selectedItems().size() != 0)
    {
        //add code remove user in database here.
        // if remove success, show messagebox "The account has been removed."
    }
    else {
        createMessageBox("Error", "Please choose an user to remove.");
    }
}

void MainWindow::on_add_info_button_clicked()
{
    clear_all_lineEdit();
    ui->manage_user_label->setText("ADD USER'S INFO");
    ui->manage_user_label->setFont(QFont("Arial",16,QFont::Bold));
    ui->manage_user_label->setVisible(true);
}

void MainWindow::on_edit_info_button_clicked()
{
    if(ui->list_Users->selectedItems().size() != 0)
    {
        ui->manage_user_label->setText("EDIT USER'S INFO");
        ui->manage_user_label->setFont(QFont("Arial",16,QFont::Bold));
        ui->manage_user_label->setVisible(true);
    }
    else {
        createMessageBox("Error", "Please choose an user to edit.");
    }
}

void MainWindow::on_cancel_change_pass_button_clicked()
{
    clear_all_lineEdit();
}

void MainWindow::on_remove_frome_basket_button_clicked()
{
    if(ui->list_book_in_basket->selectedItems().size() != 0)
    {
        QMessageBox *alert = new QMessageBox();
        alert->setWindowIcon(QIcon(":/images/warning.png"));
        alert->setText("Are you sure you want to remove this item out of your basket?");
        alert->setWindowTitle("Warning");
        QPushButton *Yes = alert->addButton(QMessageBox::Yes);
        QPushButton *No = alert->addButton(QMessageBox::No);
        alert->setDefaultButton(No);
        alert->exec();
        if(alert->clickedButton() == Yes)
            delete ui->list_book_in_basket->currentItem();
        else if(alert->clickedButton() == No)
            alert->close();
    }
    else {
        createMessageBox("Error","Please choose an item.");
    }
}

void MainWindow::on_remove_book_button_clicked()
{

}

void MainWindow::on_borrow_button_clicked()
{

}
