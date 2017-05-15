#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/Libpro_icon.ico"));
    show_viewer();
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

void MainWindow::put_in_basket_click()
{
    if(ui->login_button->text() == "Login")
    {
        createMessageBox("Error", "Please login to continue.");
    }
    else{
        createMessageBox("OK", "The book is now in your basket.");
    }
}

void MainWindow::createBookManagerWidget()
{
    for(int i = 0 ; i < 10; ++i){
    QListWidgetItem *newitem = new QListWidgetItem();
    BookWidget *book = new BookWidget();
    QWidget *bookwidget = book->createBookWidget("Object Oriented Cpp Programming 4th edition."
                                                 ,"good programming book for programmers."
                                                 ,"Someone","Something","Science/Programming book");
    newitem->setSizeHint(QSize(0,150));
    newitem->setIcon(QIcon(":/images/OK.png"));
    ui->manage_book_area->addItem(newitem);
    ui->manage_book_area->setItemWidget(newitem,bookwidget);
    }
}

void MainWindow::createDisplayBookWidget()
{
    //vertical layout in book_scoll_area
    QVBoxLayout *vlayout = new QVBoxLayout(ui->book_scoll_area);
    QString book_ID;
    for(int i = 0; i < 10; ++i){
    //create widget contains books' info and button
    BookWidget *book = new BookWidget();
    QWidget *newbook = new QWidget();
    QWidget *bookwidget = book->createBookWidget("Object Oriented Cpp Programming 4th edition."
                                                 ,"good programming book for programmers."
                                                 ,"Someone","Something","Science/Programming book");
    QPushButton *newbutton = new QPushButton();
    book->createBookButton(newbutton);
    QHBoxLayout *hlayout = new QHBoxLayout(newbook);
    hlayout->addWidget(bookwidget,6,0);
    hlayout->addWidget(newbutton,1,0);
    //book_ID =  book->get_book_info(book_ID);
    //create line
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    //add widgets
    vlayout->addWidget(newbook,0,0);
    vlayout->addWidget(line,0,0);
    //connect to slot
    connect(newbutton,SIGNAL(clicked()),this,SLOT(put_in_basket_click()));
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
