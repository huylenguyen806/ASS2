#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ////////////////////////////////////////////////
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
        displaybook->book_info->bookID = book_info->bookID;
        displaybook->book_info->genre = book_info->genre;
        displaybook->book_info->publishedDate = book_info->publishedDate;
        displaybook->book_info->publisher = book_info->publisher;
        displaybook->set_displaying_book();
        displaybook->hideButton();
        displaybook->hideRButton();
        newitem->setSizeHint(QSize(0,150));
        ui->list_book_in_basket->addItem(newitem);
        ui->list_book_in_basket->setItemWidget(newitem,displaybook);
        //put in vector basketData
        Books_c tempBook;
        tempBook.BName = book_info->title;
        tempBook.Author = book_info->author;
        tempBook.BookID = book_info->bookID;
        tempBook.Kind = book_info->genre;
        tempBook.PublishedDate = book_info->publishedDate;
        tempBook.Publisher = book_info->publisher;
        user.BasketData.append(tempBook);
    }
}

void MainWindow::createBookManagerWidget()
{
    for(int i = 0; i < data.BookData.size(); ++i){
        //get data
        DisplayBookWidget* displaybook = new DisplayBookWidget();
        displaybook->book_info->title = data.BookData[i].BName;
        displaybook->book_info->bookID = data.BookData[i].BookID;
        displaybook->book_info->author = data.BookData[i].Author;
        displaybook->book_info->publisher = data.BookData[i].Publisher;
        displaybook->book_info->genre = data.BookData[i].Kind;
        displaybook->book_info->publishedDate = data.BookData[i].PublishedDate;
        displaybook->set_displaying_book();
        displaybook->hideButton();
        displaybook->hideRButton();
        QListWidgetItem *newitem = new QListWidgetItem();
        newitem->setSizeHint(QSize(0,150));
        ui->manage_book_area->addItem(newitem);
        ui->manage_book_area->setItemWidget(newitem,displaybook);
    }
}

void MainWindow::createDisplayBookWidget()
{
    //vertical layout in book_scoll_area
    QVBoxLayout *vlayout = new QVBoxLayout(ui->book_scoll_area);
    for(int i = 0; i < data.BookData.size(); ++i){
        //get data
        DisplayBookWidget* displaybook = new DisplayBookWidget();
        displaybook->book_info->title = data.BookData[i].BName;
        displaybook->book_info->bookID = data.BookData[i].BookID;
        displaybook->book_info->author = data.BookData[i].Author;
        displaybook->book_info->publisher = data.BookData[i].Publisher;
        displaybook->book_info->genre = data.BookData[i].Kind;
        displaybook->book_info->publishedDate = data.BookData[i].PublishedDate;
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
        //set
        ui->user_name->setText(user.currentName);
        ui->email->setText(user.currentEmail);
        ui->account_name->setText(user.currentAccount_name);
        ui->libID->setText(user.currentUserID);
        ui->birthday->setText(user.currentBirthday);
        ui->ID->setText(user.currentID);
        ui->career->setText(user.currentCareer);
        if(user.currentGender == "Male")
            ui->male->setChecked(true);
        else if(user.currentGender == "Female")
            ui->female->setChecked(true);
        else ui->other->setChecked(true);
        //readonly state
        ui->user_name->setReadOnly(true);
        ui->email->setReadOnly(true);
        ui->account_name->setReadOnly(true);
        ui->libID->setReadOnly(true);
        ui->birthday->setReadOnly(true);
        ui->ID->setReadOnly(true);
        ui->career->setReadOnly(true);
        //set widget
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
    ui->login_button->setText("Login");
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
    if(ui->list_book_in_basket->selectedItems().size() == 0)
        createMessageBox("Error", "Please choose a book to borrow.");
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Are you sure you want to borrow this book?");
        alert->setWindowIcon(QIcon(":/images/warning.png"));
        alert->setWindowTitle("Warning");
        QPushButton *Y = alert->addButton(QMessageBox::Yes);
        QPushButton *N = alert->addButton(QMessageBox::No);
        alert->exec();
        if(alert->clickedButton() == Y){
            int idrow = ui->list_book_in_basket->currentRow();
            for(int i = 0; i < user.BasketData.size(); ++i){
                if(idrow == i){
                    data.write_into_userdemand_data(user.currentUserID, user.BasketData[i].BookID);
                    user.BasketData.erase(user.BasketData.begin() + i);
                    delete ui->list_book_in_basket->currentItem();
                    ui->list_book_in_basket->clearSelection();
                    break;
                }
            }
        }
        else if(alert->clickedButton() == N)
            alert->close();
    }
}

void MainWindow::on_other_login_button_clicked()
{
    login();
}

void MainWindow::set_reader()
{
    ui->main_ui_2->setCurrentWidget(ui->reader);
    ui->main_ui->setCurrentWidget(ui->find_books);
}

void MainWindow::set_usermanager()
{
    ui->main_ui_2->setCurrentWidget(ui->usermanager);
    ui->main_ui->setCurrentWidget(ui->account_manage);
}

void MainWindow::set_librarian()
{
    ui->main_ui_2->setCurrentWidget(ui->librarian);
    ui->main_ui->setCurrentWidget(ui->books_info);
}

void MainWindow::on_role_select_currentTextChanged()
{
    QString arg1 = ui->role_select->currentText();
    if(arg1 == "Reader"){
        set_reader();
    }
    else if (arg1 == "UserManager"){
        set_usermanager();
    }
    else if(arg1 == "Librarian"){
        set_librarian();
    }
}

void MainWindow::login()
{
    QString account = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if(account.isEmpty() == true || password.isEmpty() == true){
        if(account.isEmpty() == true && password.isEmpty() == false)
            createMessageBox("Error", "Please enter your username.");
        else if(password.isEmpty() == true && account.isEmpty() == false)
            createMessageBox("Error", "Please enter your password.");
        else createMessageBox("Error", "Please enter your username and password.");
    }
    else {
        bool check = 0;
        for(int i = 0; i < data.AccountData.size(); ++i){
            if(data.AccountData[i].Username == account && data.AccountData[i].Password == password){
                if(data.AccountData[i].active == true){
                    ui->lineEdit_username->clear();
                    ui->lineEdit_password->clear();
                    ui->mainStack->setCurrentWidget(ui->rolePage);
                    ui->role_select->clear();
                    ui->login_button->setText("Logout");
                    user.currentUserID = data.AccountData[i].ID;
                    get_current_user(user.currentUserID);
                    for(int j = 0; j < data.AccountRoleMapData.size(); ++j){
                        if(data.AccountRoleMapData[j].Account_No == data.AccountData[i].Username){
                            for(int k = 0; k < data.RoleData.size(); ++k){
                                if(data.RoleData[k].Role_ID == data.AccountRoleMapData[j].roles){
                                    user.currentRole = data.RoleData[k].Role_Desc;
                                    get_user_role(data.RoleData[k].Role_Desc);
                                }
                            }
                        }
                    }
                    check = 1;
                    break;
                }
                else {
                    createMessageBox("Error", "Your account has been locked");
                }
            }
            else check = 0;
        }
        if(check == 0)
            createMessageBox("Error", "Wrong username or password.");
    }
}

void MainWindow::on_lineEdit_username_returnPressed()
{
    login();
}

void MainWindow::on_lineEdit_password_returnPressed()
{
    login();
}

void MainWindow::get_user_role(QString role)
{
    if(role.contains('&')){
        QVector<QString> role_vec;
        QString temp;
        for(int i = 0; i < role.length(); ++i){
            if(role[i] != '&'){
                temp.append(role[i]);
            }
            if(role[i] == '&' || i == role.length() - 1){
                role_vec.append(temp);
                temp.clear();
                continue;
            }
        }
        for(int i = 0; i < role_vec.size(); ++i){
            if(role_vec[i] == "READER")
                ui->role_select->addItem("Reader");
            else if(role_vec[i] == "USER_MANAGER")
                ui->role_select->addItem("UserManager");
            else if(role_vec[i] == "LIBRARIAN")
                ui->role_select->addItem("Librarian");
        }
    }
    else {
        if(role == "READER")
            ui->role_select->addItem("Reader");
        else if(role == "USER_MANAGER")
            ui->role_select->addItem("UserManager");
        else if(role == "LIBRARIAN")
            ui->role_select->addItem("Librarian");
    }
}

void MainWindow::get_current_user(QString userID)
{
    for(int i = 0; i < data.UserData.size(); ++i){
        if(userID == data.UserData[i].UserID){
            user.currentName = data.UserData[i].Name;
            user.currentGender = data.UserData[i].Gender;
            user.currentCareer = data.UserData[i].Career;
            user.currentBirthday = data.UserData[i].DayOfBirth;
            user.currentID = data.UserData[i].ID_StudentID;
            user.currentEmail = data.UserData[i].email;
        }
    }
    for(int i = 0; i < data.AccountData.size(); ++i){
        if(userID == data.AccountData[i].ID){
            user.currentAccount_name = data.AccountData[i].Username;
            user.currentActive = data.AccountData[i].active;
            user.currentPass = data.AccountData[i].Password;
        }
    }
}

void MainWindow::on_ok_change_pass_button_clicked()
{
    QString oldpass = ui->change_current_pass->text();
    //add code for encryption here // encrypt to oldpass
    if(oldpass == user.currentPass){
        if(ui->new_pass->text().isEmpty() == true || ui->confirm_new_pass->text().isEmpty() == true){
            if(ui->confirm_new_pass->text().isEmpty() == false)
                createMessageBox("Error", "Please enter your new password.");
            else if(ui->new_pass->text().isEmpty() == false)
                createMessageBox("Error", "Please confirm your new password.");
            else createMessageBox("Error", "Please enter and confirm your new password.");
        }
        else if(ui->new_pass->text() == ui->confirm_new_pass->text()){
            //change password in data here
        }
    }
    else createMessageBox("Error", "Wrong current password.");
}

void MainWindow::on_remove_allbook_button_clicked()
{
    QMessageBox *noti = new QMessageBox();
    noti->setWindowTitle("Warning");
    noti->setWindowIcon(QIcon(":/images/warning.png"));
    noti->setText("Are you sure you want to remove all books from your basket?");
    QPushButton *Y = noti->addButton(QMessageBox::Yes);
    QPushButton *N = noti->addButton(QMessageBox::No);
    noti->setDefaultButton(N);
    noti->exec();
    if(noti->clickedButton() == Y)
        ui->list_book_in_basket->clear();
    else if(noti->clickedButton() == N)
        noti->close();
}

void MainWindow::on_borrow_all_button_clicked()
{
    QMessageBox *alert = new QMessageBox();
    alert->setText("Are you sure you want to borrow all?");
    alert->setWindowIcon(QIcon(":/images/warning.png"));
    alert->setWindowTitle("Warning");
    QPushButton *Y = alert->addButton(QMessageBox::Yes);
    QPushButton *N = alert->addButton(QMessageBox::No);
    alert->exec();
    if(alert->clickedButton() == Y){
        for(int i = 0; i < user.BasketData.size(); ++i){
            data.write_into_userdemand_data(user.currentUserID, user.BasketData[i].BookID);
        }
        ui->list_book_in_basket->clear();
        user.BasketData.clear();
    }
    else if(alert->clickedButton() == N)
        alert->close();
}
