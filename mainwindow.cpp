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
    bookAmount = data.BookData.size();
    //createBookManagerWidget();
    ui->manage_user_label->setHidden(true);
    show_table_manage_book_first_time();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_lib_borrowed_books()
{
    data.add_data_to_lib_borrowedbooks();
    ui->lib_borrowed_books_list->clear();
    for(int i = 0; i < data.LibBorrowBooksData.size(); ++i){
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0,40));
        item->setText("UserID: " + data.LibBorrowBooksData[i].UserID + " - " + data.LibBorrowBooksData[i].UserName +
                      ". Number of borrowed books: " + QString::number(data.LibBorrowBooksData[i].BorrowedBooks.size()));
        item->setToolTip(data.LibBorrowBooksData[i].UserID);
        ui->lib_borrowed_books_list->addItem(item);
    }
    ui->lib_number_of_borrowed_books->display(data.LibBorrowBooksData.size());
}

void MainWindow::create_newbook_noti(books *newbook)
{
    DisplayBookWidget* displaybook = new DisplayBookWidget();
    displaybook->book_info  = newbook;
    displaybook->set_displaying_book();
    displaybook->hideRButton();
    displaybook->hideDuration();
    connect(displaybook,SIGNAL(put_in_basket_button_clicked(books*)),this,SLOT(put_in_basket_click(books*)));
    QListWidgetItem *newitem = new QListWidgetItem();
    newitem->setSizeHint(QSize(0,230));
    ui->new_books_list->addItem(newitem);
    ui->new_books_list->setItemWidget(newitem, displaybook);
}

void MainWindow::read_pdf_books(books *read_book)
{
    QByteArray pdf = read_book->Pdf;
    if(pdf.isEmpty() == true)
        createMessageBox("Error", "Sorry, this book doesn't have pdf file.");
    else {
        QFile file(qApp->applicationDirPath() + "/pdf_temp.pdf");
        file.open(QIODevice::WriteOnly);
        file.write(pdf);
        file.close();
        QDesktopServices::openUrl(QUrl(qApp->applicationDirPath() + "/pdf_temp.pdf"));
    }
}

void MainWindow::show_reader_borrowed_books()
{
    ui->borrowed_books_list->clear();
    user.currentNumberOfBorrowedBooks = 0;
    for(int i = 0; i < data.OrderListData.size(); ++i){
        if(data.OrderListData[i].UserID == user.currentUserID){
            for(int j = 0; j < data.BookData.size(); ++j){
                if(data.BookData[j].BookID == data.OrderListData[i].BookID){
                    user.currentNumberOfBorrowedBooks++;
                    QListWidgetItem *newitem = new QListWidgetItem();
                    DisplayBookWidget* displaybook = new DisplayBookWidget();
                    displaybook->book_info->title = data.BookData[j].BName;
                    displaybook->book_info->bookID = data.BookData[j].BookID;
                    displaybook->book_info->author = data.BookData[j].Author;
                    displaybook->book_info->publisher = data.BookData[j].Publisher;
                    displaybook->book_info->genre = data.BookData[j].Kind;
                    displaybook->book_info->publishedDate = data.BookData[j].PublishedDate;
                    displaybook->book_info->Image = data.BookData[j].Image;
                    displaybook->returndate = data.OrderListData[i].ReturnDay;
                    displaybook->book_info->Pdf = data.BookData[j].Pdf;
                    displaybook->set_displaying_borrowed_book();
                    displaybook->hideButton();
                    displaybook->hideDuration();
                    connect(displaybook,SIGNAL(return_book(books*)), this, SLOT(return_book(books*)));
                    connect(displaybook,SIGNAL(read_book(books*)),this,SLOT(read_pdf_books(books*)));
                    connect(displaybook,SIGNAL(lost_book(books*)),this,SLOT(send_lost_book(books*)));
                    newitem->setSizeHint(QSize(0,230));
                    ui->borrowed_books_list->addItem(newitem);
                    ui->borrowed_books_list->setItemWidget(newitem,displaybook);
                }
            }
        }
    }
    //show number of books
    ui->number_borrowed_books->display(user.currentNumberOfBorrowedBooks);
}

void MainWindow::send_lost_book(books *lost)
{
    QMessageBox *box = new QMessageBox();
    box->setText("Are you sure you want to inform librarian that this book is lost?");
    box->setWindowTitle("Warning");
    box->setWindowIcon(QIcon(":/images/warning.png"));
    QPushButton *Y = box->addButton(QMessageBox::Yes);
    QPushButton *N = box->addButton(QMessageBox::No);
    box->setDefaultButton(N);
    box->exec();
    if(box->clickedButton() == Y){
        if(data.write_into_lostbooks(user.currentUserID, lost->bookID, false)){
            createMessageBox("OK", "Send notification successfully.");
        }
    }
    else if(box->clickedButton() == N)
        box->close();
}

void MainWindow::show_lost_books()
{
    ui->lost_books_list->clear();
    int count = 0;
    for(int i = 0; i < data.LostBooksData.size(); ++i){
        for(int j = 0; j < data.UserData.size(); ++j){
            if(data.UserData[j].UserID == data.LostBooksData[i].UserID){
                for(int k = 0; k < data.BookData.size(); ++k){
                    if(data.BookData[k].BookID == data.LostBooksData[i].BookID){
                        noti_item *newitem = new noti_item();
                        QListWidgetItem *item = new QListWidgetItem();
                        newitem->hide_reader_noti_detail();
                        newitem->user = data.UserData[j];
                        newitem->book = data.BookData[k];
                        newitem->set_lost_book_info(data.UserData[j].UserID, data.UserData[j].Name,
                                                    data.BookData[k].BookID, data.BookData[k].BName);
                        if(data.LostBooksData[i].CheckState == true){
                            newitem->change_background_color_to_green();
                            item->setBackgroundColor(QColor("#00ff9b"));
                        }
                        else if(data.LostBooksData[i].CheckState == false){
                            newitem->change_background_color_to_red();
                            item->setBackgroundColor(QColor("#ff3737"));
                        }
                        connect(newitem,SIGNAL(lost_book_detail(User_c,Books_c)),
                                this, SLOT(show_lost_book_detail(User_c,Books_c)));
                        item->setSizeHint(QSize(0,65));
                        ui->lost_books_list->addItem(item);
                        ui->lost_books_list->setItemWidget(item,newitem);
                        count++;
                    }
                }
            }
        }
    }
    ui->number_of_lost_books->display(count);
}

void MainWindow::show_lost_book_detail(User_c user, Books_c book)
{
    BookManagement *noti = new BookManagement();
    noti->show_lost_book_widget(user,book);
    noti->setWindowTitle("Lost book management");
    noti->setWindowIcon(QIcon(":/images/detail_icon.ico"));
    connect(noti,SIGNAL(send_lost_book_punishment(QString,QString,QString,QString)),
            this,SLOT(receive_lostbook_punishment(QString,QString,QString,QString)));
    connect(noti,SIGNAL(delete_lost_book(QString,QString)), this, SLOT(delete_lost_book(QString,QString)));
    noti->show();
}

void MainWindow::delete_lost_book(QString UserID, QString BookID)
{
    QMessageBox *box = new QMessageBox();
    box->setText("Are you sure you want to delete this lost book notification?");
    box->setWindowTitle("Warning");
    box->setWindowIcon(QIcon(":/images/warning.png"));
    QPushButton *Y = box->addButton(QMessageBox::Yes);
    QPushButton *N = box->addButton(QMessageBox::No);
    box->setDefaultButton(N);
    box->exec();
    if(box->clickedButton() == Y){
        if(data.delete_data_in_lostbooks(UserID,BookID)){
            show_lost_books();
        }
    }
    else if(box->clickedButton() == N)
        box->close();
}

void MainWindow::receive_lostbook_punishment(QString UserID, QString BookID, QString message, QString money)
{
    QString content;
    for(int i = 0; i < data.BookData.size(); ++i){
        if(data.BookData[i].BookID == BookID){
            content = "You've lost : " + data.BookData[i].BName + "<br />Message : "
                    + message + "<br />Punishment : pay " + money + " VND";
            break;
        }
    }
    int on = 0;
    if(data.ReaderNotiData.isEmpty() == false)
        on = data.ReaderNotiData[data.ReaderNotiData.size() - 1].ON + 1;
    if(data.write_into_readernoti(UserID,BookID,content,on)){
        LostBooks_c lost;
        lost.UserID = UserID;
        lost.BookID = BookID;
        lost.CheckState = 1;
        if(data.change_lostbook_checkstate(lost)){
            createMessageBox("OK", "Punishment message has been sent.");
            show_lost_books();
        }
    }
}

void MainWindow::return_book(books *return_book)
{
    QMessageBox *box = new QMessageBox();
    box->setText("Are you sure you want to return this book?");
    box->setWindowTitle("Warning");
    box->setWindowIcon(QIcon(":/images/warning.png"));
    QPushButton *Y = box->addButton(QMessageBox::Yes);
    QPushButton *N = box->addButton(QMessageBox::No);
    box->exec();
    if(box->clickedButton() == Y){
        if(data.delete_book_from_orderlist(user.currentUserID, return_book->bookID)){
            createMessageBox("OK", "Return successfully.");
            show_reader_borrowed_books();
            for(int i = 0; i < data.BookData.size(); ++i){
                if(data.BookData[i].BookID == return_book->bookID){
                    data.BookData[i].realAmmount++;
                    break;
                }
            }
        }
    }
    else if(box->clickedButton() == N)
        box->close();
}

void MainWindow::show_reader_noti()
{
    int count = 0;
    ui->reader_noti_list->clear();
    for(int i = 0; i < data.ReaderNotiData.size(); ++i){
        if(data.ReaderNotiData[i].UserID == user.currentUserID){
            QListWidgetItem *item = new QListWidgetItem();
            noti_item *newitem = new noti_item();
            newitem->hide_lost_book_detail();
            newitem->noti = data.ReaderNotiData[i];
            newitem->item = item;
            for(int j = 0; j < data.BookData.size(); ++j){
                if(data.BookData[j].BookID == data.ReaderNotiData[i].BookID){
                    newitem->book = data.BookData[j];
                    break;
                }
            }
            newitem->set_info("On the date : " + data.ReaderNotiData[i].date + "<br />" + data.ReaderNotiData[i].content);
            connect(newitem,SIGNAL(show_detail(ReaderNoti_c,Books_c)),
                    this, SLOT(show_reader_noti_detail(ReaderNoti_c,Books_c)));
            item->setSizeHint(QSize(0,65));
            ui->reader_noti_list->addItem(item);
            ui->reader_noti_list->setItemWidget(item, newitem);
            count++;
        }
    }
    ui->number_of_reader_notifications->display(count);
}

void MainWindow::show_reader_noti_detail(ReaderNoti_c noti, Books_c book)
{
    ReaderNotifications *notix = new ReaderNotifications();
    notix->noti = noti;
    notix->Create(noti,book);
    connect(notix,SIGNAL(delete_noti(ReaderNoti_c)),this, SLOT(delete_readernoti_indata(ReaderNoti_c)));
    notix->show();
}

void MainWindow::delete_readernoti_indata(ReaderNoti_c noti)
{
    if(data.delete_reader_noti_indata(noti)){
        show_reader_noti();
    }
    else createMessageBox("Error", "Unexpected issue occurs, process fails successfully.");
}

void MainWindow::show_accounts()
{
    for(int i = 0; i < data.AccountData.size(); ++i){
        ui->list_Accounts->addItem(data.AccountData[i].ID + " " + data.AccountData[i].Username);
    }
}

void MainWindow::put_in_basket_click(books* book_info)
{
    if(ui->login_button->text() == "Login")
    {
        createMessageBox("Error", "Please login to continue.");
    }
    else if(book_info->realAmount >= 1){
        createMessageBox("OK", "The book is now in your basket.");
        //put in vector basketData
        Books_c tempBook;
        tempBook.Image = book_info->Image;
        tempBook.BName = book_info->title;
        tempBook.Author = book_info->author;
        tempBook.BookID = book_info->bookID;
        tempBook.Kind = book_info->genre;
        tempBook.PublishedDate = book_info->publishedDate;
        tempBook.Publisher = book_info->publisher;
        tempBook.Amount = book_info->amount;
        tempBook.realAmmount = book_info->realAmount;
        tempBook.duration = 1;
        user.BasketData.append(tempBook);
        QListWidgetItem *newitem = new QListWidgetItem();
        DisplayBookWidget* displaybook = new DisplayBookWidget();
        displaybook->book_info->title = book_info->title;
        displaybook->book_info->author = book_info->author;
        displaybook->book_info->bookID = book_info->bookID;
        displaybook->book_info->genre = book_info->genre;
        displaybook->book_info->publishedDate = book_info->publishedDate;
        displaybook->book_info->publisher = book_info->publisher;
        displaybook->book_info->Image = book_info->Image;
        displaybook->book_info->amount = book_info->amount;
        displaybook->book_info->realAmount = book_info->realAmount;
        displaybook->set_displaying_book();
        displaybook->hideButton();
        displaybook->hideRButton();
        //edit each duration after changing the value in the set_all_duration_spinbox
        connect(this, SIGNAL(set_duration_button_clicked(int)), displaybook, SLOT(set_all_duration_signal(int)));
        newitem->setSizeHint(QSize(0,230));
        ui->list_book_in_basket->addItem(newitem);
        ui->list_book_in_basket->setItemWidget(newitem,displaybook);
        //get duration after editing in basket
        connect(displaybook, SIGNAL(send_each_duration(QString,int)), this, SLOT(get_each_duration(QString,int)));
    }
    else createMessageBox("Error", "This book isn't available due to being out of stock.");
}

void MainWindow::get_each_duration(QString bookID, int duration)
{
    for(int i = 0; i < user.BasketData.size(); ++i){
        if(bookID == user.BasketData[i].BookID){
            user.BasketData[i].duration = duration;
            break;
        }
    }
}

/*void MainWindow::createBookManagerWidget()
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
        displaybook->book_info->Image = data.BookData[i].Image;
        displaybook->book_info->amount = data.BookData[i].Amount;
        displaybook->book_info->realAmount = data.BookData[i].realAmmount;
        displaybook->set_displaying_book();
        displaybook->hideButton();
        displaybook->hideRButton();
        displaybook->hideDuration();
        QListWidgetItem *newitem = new QListWidgetItem();
        newitem->setSizeHint(QSize(0,230));
        ui->manage_book_area->addItem(newitem);
        ui->manage_book_area->setItemWidget(newitem,displaybook);
    }ok ok got it z xó luón hay óó // cu comment di okie
}*/

void MainWindow::createDisplayBookWidget()
{
    ui->book_list->clear();
    for(int i = 0; i < data.BookData.size(); ++i){
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0,235));
        //get data
        DisplayBookWidget* displaybook = new DisplayBookWidget();
        displaybook->book_info->title = data.BookData[i].BName;
        displaybook->book_info->bookID = data.BookData[i].BookID;
        displaybook->book_info->author = data.BookData[i].Author;
        displaybook->book_info->publisher = data.BookData[i].Publisher;
        displaybook->book_info->genre = data.BookData[i].Kind;
        displaybook->book_info->publishedDate = data.BookData[i].PublishedDate;
        displaybook->book_info->Image = data.BookData[i].Image;
        displaybook->book_info->amount = data.BookData[i].Amount;
        displaybook->book_info->realAmount = data.BookData[i].realAmmount;
        displaybook->set_displaying_book();
        displaybook->hideRButton();
        displaybook->hideDuration();
        //connect to slot
        connect(displaybook,SIGNAL(put_in_basket_button_clicked(books*)),this,SLOT(put_in_basket_click(books*)));
        ui->book_list->addItem(item);
        ui->book_list->setItemWidget(item,displaybook);
    }
}

void MainWindow::resetRealAmountOfBooks()
{
    //reset amount
    foreach (DisplayBookWidget *item, findChildren<DisplayBookWidget* >()) {
        for(int i = 0; i < data.BookData.size(); ++i){
            if(data.BookData[i].BookID == item->book_info->bookID)
            {
                item->book_info->realAmount = data.BookData[i].realAmmount;
                item->resetRealAmount();
            }
        }
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
    if(ui->table_manage_book->currentIndex().isValid())
    {
        QString id=ui->table_manage_book->item(ui->table_manage_book->currentRow(),0)->text();
        this->close();
        managebooks *edit_books= new managebooks;
        edit_books->show();
        edit_books->show_book_to_edit(id);
    }
    else
    {
         QMessageBox msgbox(QMessageBox::Warning,"No book is selected","Please select a book to edit");
         msgbox.exec();
    }
}

void MainWindow::on_add_account_button_clicked()
{
    ManageAccount *add = new ManageAccount();
    add->showadd();
    add->show();
}

void MainWindow::on_add_book_button_clicked()
{
    this->close();
   managebooks *addbook=new managebooks;
   addbook->show();
   addbook->show_book_to_add();
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
    resetRealAmountOfBooks();
    if(bookAmount != data.BookData.size())
        createDisplayBookWidget();
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
    show_reader_noti();
    show_reader_borrowed_books();
    ui->reader_noti_tab->setCurrentWidget(ui->newbooks_noti);
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
    ui->librarian_tab->setCurrentWidget(ui->lib_borrowed_book);
    show_lib_borrowed_books();
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
        //for(int i = 0; i < data.AccountData.size(); ++i){
        //if(data.AccountData[i].)
        ManageAccount *edit = new ManageAccount();
        edit->showedit();
        edit->show();
        //}
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
    connect_database();
    if(!ui->table_manage_book->currentIndex().isValid())
    {
        QMessageBox msgbox(QMessageBox::Warning,"No book to remove","Please select a book to remove");
        msgbox.exec();
    }
    else
    {
        QMessageBox askbox(QMessageBox::Question,"Remove book","Do you want to remove this book?",
                           QMessageBox::Yes|QMessageBox::No);
        if(askbox.exec()==QMessageBox::Yes)
        {
            QString temp_bookid=ui->table_manage_book->item(ui->table_manage_book->currentRow(),0)->text();
            QSqlQuery qry(mydb);
            qry.prepare("DELETE from BOOKS where BOOKID=:id");
            qry.bindValue(":id",temp_bookid);
            qry.exec();
            show_table_manage_book();
        }
    }

    disconnect_database();
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
                    bool check = 0;
                    for(int j = 0; j < data.OrderListData.size(); ++j){
                        if(data.OrderListData[i].UserID == user.currentUserID &&
                                data.OrderListData[i].BookID == user.BasketData[i].BookID){
                            check = 1;
                            break;
                        }
                    }
                    if(check == 1)
                        createMessageBox("Error", "You have borrowed this book.");
                    else if(check == 0){
                        //write in to database
                        data.write_into_userdemand_data(user.currentUserID, user.BasketData[i].BookID, user.BasketData[i].duration);
                        //send request to librarian
                        send_request_to_librarian(user.currentUserID, user.BasketData[i].BookID);
                        //erase from basket
                        user.BasketData.erase(user.BasketData.begin() + i);
                        delete ui->list_book_in_basket->currentItem();
                        //clear selection in basket
                        ui->list_book_in_basket->clearSelection();
                        break;
                    }
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
    resetRealAmountOfBooks();
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
        //encode
        QCryptographicHash md5(QCryptographicHash::Md5);
        QByteArray input;
        input.append(password);
        md5.addData(input);
        password = md5.result().toHex();
        //check
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
                    ui->aloha->setTextFormat(Qt::RichText);
                    ui->aloha->setText("Aloha, " + user.currentName + " !!");
                    ui->aloha->setAlignment(Qt::AlignCenter);
                    for(int j = 0; j < data.AccountRoleMapData.size(); ++j){
                        if(data.AccountRoleMapData[j].Account_No == data.AccountData[i].Username){
                            get_user_role(data.AccountRoleMapData[j].roles);
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

void MainWindow::get_user_role(QString roleid)
{
    if(roleid.contains(' ')){
        QVector<QString> role_vec;
        QString temp;
        for(int i = 0; i < roleid.length(); ++i){
            if(roleid[i] != ' '){
                temp.append(roleid[i]);
            }
            if(roleid[i] == ' ' || i == roleid.length() - 1){
                role_vec.append(temp);
                temp.clear();
                continue;
            }
        }
        for(int i = 0; i < role_vec.size(); ++i){
            for(int j = 0; j < data.RoleData.size(); ++j){
                if(role_vec[i] == data.RoleData[j].Role_ID){
                    if(data.RoleData[j].Role_Desc == "READER"){
                        ui->role_select->addItem("Reader");
                    }
                    else if(data.RoleData[j].Role_Desc == "USER_MANAGER"){
                        ui->role_select->addItem("UserManager");
                    }
                    else if(data.RoleData[j].Role_Desc == "LIBRARIAN"){
                        ui->role_select->addItem("Librarian");

                    }
                }
            }
        }
    }
    else {
        for(int j = 0; j < data.RoleData.size(); ++j){
            if(roleid == data.RoleData[j].Role_ID){
                if(data.RoleData[j].Role_Desc == "READER"){
                    ui->role_select->addItem("Reader");
                }
                else if(data.RoleData[j].Role_Desc == "USER_MANAGER"){
                    ui->role_select->addItem("UserManager");
                }
                else if(data.RoleData[j].Role_Desc == "LIBRARIAN"){
                    ui->role_select->addItem("Librarian");
                }
            }
        }
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
            data.change_password(user.currentUserID, ui->new_pass->text());
            clear_all_lineEdit();
        }
        else if(ui->new_pass->text() != ui->confirm_new_pass->text())
            createMessageBox("Error", "Wrong confirmed password.");
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
            bool check = 0;
            for(int j = 0; j < data.OrderListData.size(); ++j){
                if(data.OrderListData[j].UserID == user.currentUserID &&
                        data.OrderListData[j].BookID == user.BasketData[i].BookID){
                    check = 1;
                    break;
                }
            }
            if(check == 0){
                //write in to database
                data.write_into_userdemand_data(user.currentUserID, user.BasketData[i].BookID, user.BasketData[i].duration);
                //send request to librarian
                send_request_to_librarian(user.currentUserID, user.BasketData[i].BookID);
                //erase from basket
                user.BasketData.erase(user.BasketData.begin() + i);
                i--;
            }
        }
        ui->list_book_in_basket->clear();
        if(user.BasketData.isEmpty() == false){
            createMessageBox("Warning", "The remains are already borrowed by you.");
            for(int i = 0; i < user.BasketData.size(); ++i){
                QListWidgetItem *newitem = new QListWidgetItem();
                DisplayBookWidget* displaybook = new DisplayBookWidget();
                displaybook->book_info->title = user.BasketData[i].BName;
                displaybook->book_info->author = user.BasketData[i].Author;
                displaybook->book_info->bookID = user.BasketData[i].BookID;
                displaybook->book_info->genre = user.BasketData[i].Kind;
                displaybook->book_info->publishedDate = user.BasketData[i].PublishedDate;
                displaybook->book_info->publisher = user.BasketData[i].Publisher;
                displaybook->book_info->Image = user.BasketData[i].Image;
                displaybook->book_info->amount = user.BasketData[i].Amount;
                displaybook->book_info->realAmount = user.BasketData[i].realAmmount;
                displaybook->set_displaying_book();
                displaybook->hideButton();
                displaybook->hideRButton();
                //edit each duration after changing the value in the set_all_duration_spinbox
                connect(this, SIGNAL(set_duration_button_clicked(int)), displaybook, SLOT(set_all_duration_signal(int)));
                newitem->setSizeHint(QSize(0,230));
                ui->list_book_in_basket->addItem(newitem);
                ui->list_book_in_basket->setItemWidget(newitem,displaybook);
                //get duration after editing in basket
                connect(displaybook, SIGNAL(send_each_duration(QString,int)), this, SLOT(get_each_duration(QString,int)));
            }
        }
    }
    else if(alert->clickedButton() == N)
        alert->close();
}

void MainWindow::on_confirm_new_pass_returnPressed()
{
    on_ok_change_pass_button_clicked();
}

void MainWindow::on_new_pass_returnPressed()
{
    on_ok_change_pass_button_clicked();
}

void MainWindow::on_change_current_pass_returnPressed()
{
    on_ok_change_pass_button_clicked();
}

void MainWindow::send_request_to_librarian(QString userID, QString borrowBookID)
{
    QString name;
    QString bookname;
    for(int i = 0 ; i < data.UserData.size(); ++i){
        if(data.UserData[i].UserID == userID){
            name = data.UserData[i].Name;
        }
    }
    for(int i = 0; i < user.BasketData.size(); ++i){
        if(user.BasketData[i].BookID == borrowBookID){
            bookname = user.BasketData[i].BName;
        }
    }
    QListWidgetItem *newitem = new QListWidgetItem();
    newitem->setText(name + " (ID: " + userID + ") want to borrow " + bookname + " (BookID: " + borrowBookID + ")");
    ui->librarian_noti_list->addItem(newitem);
}

void MainWindow::get_librarian_noti()
{
    ui->librarian_noti_list->clear();
    for(int i = 0; i < data.UserDemandData.size(); ++i){
        QString name;
        QString bookname;
        for(int j = 0 ; j < data.UserData.size(); ++j){
            if(data.UserData[j].UserID == data.UserDemandData[i].UserID){
                name = data.UserData[j].Name;
            }
        }
        for(int j = 0; j < data.BookData.size(); ++j){
            if(data.BookData[j].BookID == data.UserDemandData[i].BorrowBookID)
                bookname = data.BookData[j].BName;
        }
        QListWidgetItem *newitem = new QListWidgetItem();
        newitem->setText(name + " (ID: " + data.UserDemandData[i].UserID +
                         ") want to borrow " + bookname + " (BookID: " + data.UserDemandData[i].BorrowBookID + ")");
        newitem->setToolTip(data.UserDemandData[i].UserID + " " + data.UserDemandData[i].BorrowBookID);
        ui->librarian_noti_list->addItem(newitem);
    }
}

void MainWindow::on_Detail_clicked()
{
    if(ui->librarian_noti_list->selectedItems().size() == 0){
        createMessageBox("Error", "Please choose an item to see its detail.");
    }
    else {
        for(int i = 0; i < data.UserDemandData.size(); ++i){
            if(ui->librarian_noti_list->currentRow() == i){
                BookManagement *widget = new BookManagement();
                User_c user;
                Books_c book;
                for(int j = 0; j < data.UserData.size(); ++j){
                    if(data.UserDemandData[i].UserID == data.UserData[j].UserID){
                        user = data.UserData[j];
                        break;
                    }
                }
                for(int j = 0; j < data.BookData.size(); ++j){
                    if(data.UserDemandData[i].BorrowBookID == data.BookData[j].BookID){
                        book = data.BookData[j];
                        break;
                    }
                }
                widget->showBorrowBookInfo(user, book , data.UserDemandData[i].Duration);
                if(data.ReaderNotiData.isEmpty() == true)
                    widget->on = 0;
                else widget->on = data.ReaderNotiData[data.ReaderNotiData.size() - 1].ON + 1;
                widget->show();
                //write into data (when borrowing successfully)
                connect(widget, SIGNAL(accept_button_signals(UserDemand_c*)),
                        this, SLOT(accept_reader_request_about_borrowing_book(UserDemand_c*)));
                connect(widget, SIGNAL(send_reason_for_denial(QString,QString,QString,int)),
                        this, SLOT(get_reason_for_denial(QString,QString,QString,int)));
            }
        }
    }
}

void MainWindow::get_reason_for_denial(QString UserID, QString BookID, QString content, int on)
{
    if(data.write_into_readernoti(UserID, BookID, content, on)){
        createMessageBox("OK", "Message has been sent.");
        delete ui->librarian_noti_list->currentItem();
    }
}

void MainWindow::accept_reader_request_about_borrowing_book(UserDemand_c *request)
{
    if(data.write_into_orderlist(request)){
        delete ui->librarian_noti_list->currentItem();
        ui->librarian_noti_list->clearSelection();
        for(int i = 0; i < data.BookData.size(); ++i){
            if(data.BookData[i].BookID == request->BorrowBookID){
                data.BookData[i].realAmmount--;
                QString content = "Your request for borrowing " + data.BookData[i].BName + " has been accepted.";
                int on = 0;
                if(data.ReaderNotiData.isEmpty() == false)
                    on = data.ReaderNotiData[data.ReaderNotiData.size() - 1].ON + 1;
                data.write_into_readernoti(request->UserID, request->BorrowBookID, content, on);
                break;
            }
        }
    }
}

void MainWindow::on_set_duration_button_clicked()
{
    emit set_duration_button_clicked(ui->set_all_duration->value());
}

void MainWindow::on_reader_clearall_button_clicked()
{
    if(!data.ReaderNotiData.isEmpty()){
        QMessageBox *noti = new QMessageBox();
        noti->setText("Are you sure you want to clear all?");
        noti->setWindowIcon(QIcon(":/images/warning.png"));
        noti->setWindowTitle("Warning");
        QPushButton *Y = noti->addButton(QMessageBox::Yes);
        QPushButton *N = noti->addButton(QMessageBox::No);
        noti->setDefaultButton(N);
        noti->exec();
        if(noti->clickedButton() == Y){
            for(int i = 0; i < data.ReaderNotiData.size(); ++i){
                if(data.ReaderNotiData[i].UserID == user.currentUserID){
                    data.delete_all_reader_noti(data.ReaderNotiData[i]);
                    data.ReaderNotiData.erase(data.ReaderNotiData.begin() + i);
                    i--;
                }
            }
        }
        else if(noti->clickedButton() == N)
            noti->close();
        show_reader_noti();
    }
    else createMessageBox("Error", "There is no reader notification to clear.");
}

void MainWindow::on_librarian_tab_tabBarClicked(int index)
{
    if(index == 0)
        show_lib_borrowed_books();
    else if(index == 1)
        show_lost_books();
    else if(index == 2)
        get_librarian_noti();
}

void MainWindow::on_clear_all_lost_book_clicked()
{
    if(!data.LostBooksData.isEmpty()){
        QMessageBox *noti = new QMessageBox();
        noti->setWindowIcon(QIcon(":/images/warning.png"));
        noti->setWindowTitle("Warning");
        noti->setText("Are you sure you want to clear all lost books?");
        QPushButton *Y = noti->addButton(QMessageBox::Yes);
        QPushButton *N = noti->addButton(QMessageBox::No);
        noti->setDefaultButton(N);
        noti->exec();
        if(noti->clickedButton() == Y){
            QSqlQuery qry;
            for(int i = 0; i < data.LostBooksData.size(); ++i){
                QString UserID = data.LostBooksData[i].UserID;
                QString BookID = data.LostBooksData[i].BookID;
                qry.prepare("DELETE FROM LostBooks WHERE UserID = '"+UserID+"' and BookID = '"+BookID+"'");
                if(qry.exec()){
                    data.LostBooksData.erase(data.LostBooksData.begin() + i);
                    i--;
                }
                else {
                    QMessageBox *alert = new QMessageBox();
                    alert->setText("Unexpected issues occur, process has failed.");
                    alert->setWindowIcon(QIcon(":/images/error.png"));
                    alert->setWindowTitle("Error");
                    alert->show();
                }
                qry.clear();
            }
        }
        else if(noti->clickedButton() == N)
            noti->close();
        show_lost_books();
    }
    else createMessageBox("Error", "There is no lost book notification to clear.");
}

void MainWindow::on_lib_borrowed_books_detail_clicked()
{
    if(ui->lib_borrowed_books_list->selectedItems().size() == 0)
        createMessageBox("Error", "No record is selected.");
    else {
        for(int i = 0; i < data.LibBorrowBooksData.size(); ++i){
            if(data.LibBorrowBooksData[i].UserID == ui->lib_borrowed_books_list->currentItem()->toolTip()){
                BookManagement *noti = new BookManagement();
                noti->setMaximumWidth(600);
                noti->setMinimumWidth(600);
                noti->setMaximumHeight(500);
                noti->setMinimumHeight(500);
                noti->show_borrowed_books(data.LibBorrowBooksData[i]);
                noti->show();
                break;
            }
        }
    }
}

void MainWindow::on_clear_noti_librarian_button_clicked()
{
    if(ui->librarian_noti_list->selectedItems().size() == 0)
        createMessageBox("Error", "No record is selected.");
    else {
        QMessageBox *noti = new QMessageBox();
        noti->setWindowIcon(QIcon(":/images/warning.png"));
        noti->setWindowTitle("Warning");
        noti->setText("Are you sure you want to clear this notification?");
        QPushButton *Y = noti->addButton(QMessageBox::Yes);
        QPushButton *N = noti->addButton(QMessageBox::No);
        noti->setDefaultButton(N);
        noti->exec();
        if(noti->clickedButton() == Y){
            QString *temp = new QString(ui->librarian_noti_list->currentItem()->toolTip());
            QTextStream in(temp,QIODevice::ReadOnly);
            QString UserID, BorrowedBookID;
            in >> UserID >> BorrowedBookID;
            if(data.delete_from_userdemand_data(UserID, BorrowedBookID)){
                get_librarian_noti();
                createMessageBox("OK", "Delete successfully.");
            }
        }
        else if(noti->clickedButton() == N)
            noti->close();
    }
}

void MainWindow::on_clear_all_noti_librarian_button_clicked()
{
    QMessageBox *noti = new QMessageBox();
    noti->setWindowIcon(QIcon(":/images/warning.png"));
    noti->setWindowTitle("Warning");
    noti->setText("Are you sure you want to clear this notification?");
    QPushButton *Y = noti->addButton(QMessageBox::Yes);
    QPushButton *N = noti->addButton(QMessageBox::No);
    noti->setDefaultButton(N);
    noti->exec();
    if(noti->clickedButton() == Y){
        for(int i = 0; i < data.UserDemandData.size(); ++i){
            QString UserID = data.UserDemandData[i].UserID;
            QString BorrowBookID = data.UserDemandData[i].BorrowBookID;
            QSqlQuery qry;
            qry.prepare("DELETE FROM UserDemand WHERE UserID = '"+UserID+"' and BorrowBookID = '"+BorrowBookID+"'");
            if(qry.exec()){
                data.UserDemandData.erase(data.UserDemandData.begin() + i);
                i--;
            }
            else {
                QMessageBox *alert = new QMessageBox();
                alert->setText("Unexpected issues occur, process has failed.");
                alert->setWindowIcon(QIcon(":/images/error.png"));
                alert->setWindowTitle("Error");
                alert->show();
            }
            qry.clear();
        }
        get_librarian_noti();
    }
    else if(noti->clickedButton() == N)
        noti->close();
}

void MainWindow::on_search_books_returnPressed()
{
    Search booktitle(data.BookData);
    booktitle.findBookName(ui->search_books->text());
    QVector<Books_c> tempdata = booktitle.getBookData();
    ui->book_list->clear();
    if(tempdata.isEmpty() == false){
        for(int i = 0; i < tempdata.size(); ++i){
            QListWidgetItem *item = new QListWidgetItem();
            item->setSizeHint(QSize(0,235));
            //get data
            DisplayBookWidget* displaybook = new DisplayBookWidget();
            displaybook->book_info->title = tempdata[i].BName;
            displaybook->book_info->bookID = tempdata[i].BookID;
            displaybook->book_info->author = tempdata[i].Author;
            displaybook->book_info->publisher = tempdata[i].Publisher;
            displaybook->book_info->genre = tempdata[i].Kind;
            displaybook->book_info->publishedDate = tempdata[i].PublishedDate;
            displaybook->book_info->Image = tempdata[i].Image;
            displaybook->book_info->amount = tempdata[i].Amount;
            displaybook->book_info->realAmount = tempdata[i].realAmmount;
            displaybook->set_displaying_book();
            displaybook->hideRButton();
            displaybook->hideDuration();
            //connect to slot
            connect(displaybook,SIGNAL(put_in_basket_button_clicked(books*)),this,SLOT(put_in_basket_click(books*)));
            ui->book_list->addItem(item);
            ui->book_list->setItemWidget(item,displaybook);
        }
    }
}

void MainWindow::on_refresh_book_button_clicked()
{
    ui->search_books->clear();
    createDisplayBookWidget();
}

void MainWindow::advanced_book_search(QString BName, QString Genre, QString Author, QString Publisher)
{
    Search find(data.BookData);
    find.findBookName(BName);
    find.findBookGenre(Genre);
    find.findBookAuthor(Author);
    find.findBookPublisher(Publisher);
    QVector<Books_c> tempdata = find.getBookData();
    ui->book_list->clear();
    if(tempdata.isEmpty() == false){
        for(int i = 0; i < tempdata.size(); ++i){
            QListWidgetItem *item = new QListWidgetItem();
            item->setSizeHint(QSize(0,235));
            //get data
            DisplayBookWidget* displaybook = new DisplayBookWidget();
            displaybook->book_info->title = tempdata[i].BName;
            displaybook->book_info->bookID = tempdata[i].BookID;
            displaybook->book_info->author = tempdata[i].Author;
            displaybook->book_info->publisher = tempdata[i].Publisher;
            displaybook->book_info->genre = tempdata[i].Kind;
            displaybook->book_info->publishedDate = tempdata[i].PublishedDate;
            displaybook->book_info->Image = tempdata[i].Image;
            displaybook->book_info->amount = tempdata[i].Amount;
            displaybook->book_info->realAmount = tempdata[i].realAmmount;
            displaybook->set_displaying_book();
            displaybook->hideRButton();
            displaybook->hideDuration();
            //connect to slot
            connect(displaybook,SIGNAL(put_in_basket_button_clicked(books*)),this,SLOT(put_in_basket_click(books*)));
            ui->book_list->addItem(item);
            ui->book_list->setItemWidget(item,displaybook);
        }
    }
}

void MainWindow::on_find_book_button_clicked()
{
    ui->search_books->clear();
    AdvancedSearch *search = new AdvancedSearch();
    search->set_book_search();
    connect(search,SIGNAL(send_advanced_book_search(QString,QString,QString,QString)),
            this,SLOT(advanced_book_search(QString,QString,QString,QString)));
    search->show();
}
void MainWindow::connect_database()
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
void MainWindow::disconnect_database()
{
    mydb.close();
    mydb=QSqlDatabase();
    mydb.removeDatabase(mydb.connectionName());
}
void MainWindow::show_table_manage_book()
{
    ui->main_ui->setCurrentWidget(ui->books_info);
    show_table_manage_book_first_time();
}

void MainWindow::show_table_manage_book_first_time()
{
     connect_database();
     int num_rows,r,c;
     QSqlQuery qry(mydb);
     if(!qry.exec("SELECT count(BOOKID) as num_rows FROM BOOKS")) qDebug()<<qry.lastError().text();
     qry.first();
     num_rows=qry.value(0).toInt();
     ui->table_manage_book->setRowCount(num_rows);
     ui->table_manage_book->setIconSize(QSize(32,32));
     if(!qry.exec("SELECT BOOKID, BNAME, PUBLISHEDDATE, AUTHOR, PUBLISHER, KIND, IMAGE,AMOUNT FROM BOOKS ORDER BY BOOKID")) qDebug()<<qry.lastError().text();
     for(r=0,qry.first();qry.isValid();qry.next(),++r)
     {
         ui->table_manage_book->setItem(r,0,new QTableWidgetItem(qry.value(0).toString()));
         QPixmap pix;
         QByteArray temp_image=qry.value(6).toByteArray();
         pix.loadFromData(temp_image);
         QLabel *label_icon= new QLabel;
         label_icon->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
         label_icon->setAlignment(Qt::AlignHCenter);
         ui->table_manage_book->setCellWidget(r,1,label_icon);
         for(c=2;c<7;++c)
         {
             ui->table_manage_book->setItem(r,c,new QTableWidgetItem(qry.value(c-1).toString()));
         }
         ui->table_manage_book->setItem(r,7,new QTableWidgetItem(qry.value(7).toString()));
     }
     ui->table_manage_book->resizeColumnToContents(1);
     ui->table_manage_book->resizeRowsToContents();
     disconnect_database();
}

void MainWindow::on_pushbutton_open_book_clicked()
{
    connect_database();
    if(ui->table_manage_book->currentIndex().isValid())
    {
        QString temp_bookid=ui->table_manage_book->item(ui->table_manage_book->currentRow(),0)->text();
        QSqlQuery qry(mydb);
        qry.prepare("SELECT * FROM BOOKS WHERE BOOKID='"+temp_bookid+"'");
        qry.exec();
        qry.first();
        QByteArray bytearray_pdf=qry.value(8).toByteArray();
        if(bytearray_pdf.isNull())
        {
            QMessageBox msgbox(QMessageBox::Information,"No content","This book doesn't include any contents. Please insert its content in <b>Edit book</b>");
            msgbox.exec();
        }
        else
        {
            QFile file_pdf(qApp->applicationDirPath() + "/pdf_temp.pdf");
            file_pdf.open(QIODevice::WriteOnly);
            file_pdf.write(bytearray_pdf);
            file_pdf.close();
            QDesktopServices op;
            op.openUrl(QUrl(qApp->applicationDirPath() + "/pdf_temp.pdf"));
        }
    }
    else
    {
        QMessageBox msgbox(QMessageBox::Warning,"Error","Please choose book to open");
        msgbox.exec();
    }
    disconnect_database();
}


void MainWindow::on_search_book_manage_textChanged(const QString &arg1)
{
    connect_database();
    int num_rows;
    num_rows=ui->table_manage_book->rowCount();
    QSqlQuery qry(mydb);
    if(arg1!="")
    {
        for(int i=0;i<num_rows;++i)
            if(!ui->table_manage_book->isHidden())
                ui->table_manage_book->hideRow(i);
       if(!qry.exec("select * from BOOKS where BNAME LIKE '%"+arg1+"%' or AUTHOR LIKE '%"+arg1+"%' or PUBLISHER LIKE '%"+arg1+"%'")) qDebug()<<qry.lastError().text();
       while(qry.next())
       {
            QString temp_bookid=qry.value(0).toString();
            for(int i=0;i<ui->table_manage_book->rowCount();++i)
            {
                if(ui->table_manage_book->item(i,0)->text()==temp_bookid)
                    ui->table_manage_book->showRow(i);
            }
       }
    }
    else
    {
        for(int i=0;i<num_rows;++i)
            if(!ui->table_manage_book->isHidden())
                ui->table_manage_book->showRow(i);
    }
    disconnect_database();
}


void MainWindow::on_box_search_book_manage_textChanged(const QString &arg1)
{
    connect_database();
    int num_rows;
    num_rows=ui->table_manage_book->rowCount();
    QSqlQuery qry(mydb);
    if(arg1!="")
    {
        for(int i=0;i<num_rows;++i)
            if(!ui->table_manage_book->isHidden())
                ui->table_manage_book->hideRow(i);
       if(!qry.exec("select * from BOOKS where BNAME LIKE '%"+arg1+"%' or AUTHOR LIKE '%"+arg1+"%' or PUBLISHER LIKE '%"+arg1+"%'")) qDebug()<<qry.lastError().text();
       while(qry.next())
       {
            QString temp_bookid=qry.value(0).toString();
            for(int i=0;i<ui->table_manage_book->rowCount();++i)
            {
                if(ui->table_manage_book->item(i,0)->text()==temp_bookid)
                    ui->table_manage_book->showRow(i);
            }
       }
    }
    else
    {
        for(int i=0;i<num_rows;++i)
            if(!ui->table_manage_book->isHidden())
                ui->table_manage_book->showRow(i);
    }
    disconnect_database();
}
