#include "database.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QIcon>
#include <QSqlQuery>
#include <QApplication>
UserDemand_c::UserDemand_c()
{

}
Database::Database()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
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

    // Lấy đống dữ liệu trong sql vào vector book
    QSqlQuery query1("SELECT * FROM BOOKS");
    int idIndex = query1.record().indexOf("BOOKID");
    int nameIndex = query1.record().indexOf("BNAME");
    int authorIndex = query1.record().indexOf("AUTHOR");
    int publisherIndex = query1.record().indexOf("PUBLISHER");
    int genreIndex = query1.record().indexOf("KIND");
    int dateIndex = query1.record().indexOf("PUBLISHEDDATE");
    int imageIndex = query1.record().indexOf("IMAGE");
    int amount = query1.record().indexOf("AMOUNT");
    int pdf = query1.record().indexOf("PDF");
    while (query1.next())
    {
        Books_c tempBooks;
        QString tempBookID = query1.value(idIndex).toString();
        QString tempBName = query1.value(nameIndex).toString();
        QString tempPublishedDate = query1.value(dateIndex).toString();
        QString tempAuthor = query1.value(authorIndex).toString();
        QString tempPublisher = query1.value(publisherIndex).toString();
        QString tempKind = query1.value(genreIndex).toString();
        QByteArray tempImage = query1.value(imageIndex).toByteArray();
        int tempAmount = query1.value(amount).toInt();
        QByteArray tempPDF = query1.value(pdf).toByteArray();
        tempBooks.BookID = tempBookID;
        tempBooks.BName = tempBName;
        tempBooks.PublishedDate = tempPublishedDate;
        tempBooks.Author = tempAuthor;
        tempBooks.Publisher = tempPublisher;
        tempBooks.Kind = tempKind;
        tempBooks.Image = tempImage;
        tempBooks.Amount = tempAmount;
        tempBooks.Pdf = tempPDF;
        BookData.append(tempBooks);
    }
    query1.clear();
    // Lấy đống dữ liệu trong sql vào vector user
    query1.exec("SELECT * FROM User");
    int IdUser = query1.record().indexOf("UserID");
    int usernameIndex = query1.record().indexOf("Name");
    int genderIndex = query1.record().indexOf("GENDER");
    int birthday = query1.record().indexOf("DAY OF BIRTH");
    int realID = query1.record().indexOf("ID/STUDENT ID");
    int career = query1.record().indexOf("CAREER");
    int email = query1.record().indexOf("Email");
    while (query1.next())
    {
        User_c tempUser;
        QString tempUserID = query1.value(IdUser).toString();
        QString tempName = query1.value(usernameIndex).toString();
        QString tempGender = query1.value(genderIndex).toString();
        QString tempDayOfBirth = query1.value(birthday).toString();
        QString tempID_StudentID = query1.value(realID).toString();
        QString tempCareer = query1.value(career).toString();
        QString tempEmail = query1.value(email).toString();
        tempUser.UserID=tempUserID;
        tempUser.Name=tempName;
        tempUser.Gender=tempGender;
        tempUser.DayOfBirth=tempDayOfBirth;
        tempUser.ID_StudentID=tempID_StudentID;
        tempUser.Career=tempCareer;
        tempUser.email=tempEmail;
        UserData.append(tempUser);
    }
    query1.clear();
    // Lấy đống dữ liệu trong sql vào vector account
    query1.exec("SELECT * FROM Account");
    int accountname = query1.record().indexOf("USERNAME");
    int pass = query1.record().indexOf("PASSWORD");
    int ID = query1.record().indexOf("ID");
    int active = query1.record().indexOf("ACTIVE");
    while (query1.next())
    {
        Account_c tempAccount;
        QString tempUsername = query1.value(accountname).toString();
        QString tempPassword = query1.value(pass).toString();
        QString tempID = query1.value(ID).toString();
        bool tempActive = query1.value(active).toBool();
        tempAccount.Username=tempUsername;
        tempAccount.Password=tempPassword;
        tempAccount.ID=tempID;
        tempAccount.active=tempActive;
        AccountData.append(tempAccount);
    }
    query1.clear();
    // Lấy đống dữ liệu trong sql vào vector Role
    query1.exec("SELECT * FROM ROLE");
    int idrowRole_ID = query1.record().indexOf("ROLE ID");
    int idrowRole_desc = query1.record().indexOf("ROLE DESC");
    while (query1.next())
    {
        Role_c tempRole;
        QString tempRole_ID = query1.value(idrowRole_ID).toString();
        QString tempRole_Desc = query1.value(idrowRole_desc).toString();
        tempRole.Role_ID=tempRole_ID;
        tempRole.Role_Desc=tempRole_Desc;
        RoleData.append(tempRole);
    }
    query1.clear();
    // Lấy đống dữ liệu trong sql vào vector AccountRoleMap
    query1.exec("SELECT * FROM AccountRoleMap");
    idrowRole_ID = query1.record().indexOf("ROLE ID");
    int account_no = query1.record().indexOf("ACCOUNT NO");
    while (query1.next())
    {
        AccountRoleMap_c tempAccountRoleMap;
        QString tempAccount_No = query1.value(account_no).toString();
        QString temproles = query1.value(idrowRole_ID).toString();
        tempAccountRoleMap.Account_No=tempAccount_No;
        tempAccountRoleMap.roles=temproles;
        AccountRoleMapData.append(tempAccountRoleMap);
    }
    query1.clear();
    query1.exec("SELECT * FROM UserDemand");
    IdUser = query1.record().indexOf("UserID");
    int BookId = query1.record().indexOf("BorrowBookID");
    int duration = query1.record().indexOf("Duration");
    while (query1.next())
    {
        UserDemand_c tempDemand;
        tempDemand.UserID = query1.value(IdUser).toString();
        tempDemand.BorrowBookID = query1.value(BookId).toString();
        tempDemand.Duration = query1.value(duration).toInt();
        UserDemandData.append(tempDemand);
    }
    query1.clear();
    query1.exec("SELECT * FROM OrderList");
    IdUser = query1.record().indexOf("UserID");
    BookId = query1.record().indexOf("BookID");
    int borrowday = query1.record().indexOf("BorrowDay");
    int returnday = query1.record().indexOf("ReturnDay");
    while(query1.next())
    {
        OrderList_c tempOrder;
        tempOrder.UserID = query1.value(IdUser).toString();
        tempOrder.BookID = query1.value(BookId).toString();
        tempOrder.BorrowDay = query1.value(borrowday).toString();
        tempOrder.ReturnDay = query1.value(returnday).toString();
        OrderListData.append(tempOrder);
    }
    query1.clear();
    //find real ammount of books
    for(int i = 0; i < BookData.size(); ++i){
        int count = 0;
        for(int j = 0; j < OrderListData.size(); ++j){
            if(OrderListData[j].BookID == BookData[i].BookID)
                count++;
        }
        BookData[i].realAmmount = BookData[i].Amount - count;
    }
    query1.exec("SELECT * FROM ReaderNoti");
    int on = query1.record().indexOf("OrdinalNumber");
    IdUser = query1.record().indexOf("UserID");
    int date = query1.record().indexOf("Date");
    int content = query1.record().indexOf("Content");
    BookId = query1.record().indexOf("BookID");
    account_no = query1.record().indexOf("Account_no");
    while(query1.next())
    {
        ReaderNoti_c temp;
        temp.ON = query1.value(on).toInt();
        temp.UserID = query1.value(IdUser).toString();
        temp.date = query1.value(date).toString();
        temp.content = query1.value(content).toString();
        temp.BookID = query1.value(BookId).toString();
        temp.account_no = query1.value(account_no).toString();
        ReaderNotiData.append(temp);
    }
    query1.clear();
    query1.exec("SELECT * FROM LostBooks");
    IdUser = query1.record().indexOf("UserID");
    BookId = query1.record().indexOf("BookId");
    int checkstate = query1.record().indexOf("CheckState");
    while(query1.next())
    {
        LostBooks_c temp;
        temp.UserID = query1.value(IdUser).toString();
        temp.BookID = query1.value(BookId).toString();
        temp.CheckState = query1.value(checkstate).toBool();
        LostBooksData.append(temp);
    }
    query1.clear();
    date = NULL;
    content = NULL;
    borrowday = NULL;
    returnday = NULL;
    BookId = NULL;
    idrowRole_ID = NULL;
    account_no = NULL;
    idrowRole_desc = NULL;
    active = NULL;
    idIndex = NULL;
    ID = NULL;
    accountname = NULL;
    pass = NULL;
    usernameIndex = NULL;
    genderIndex = NULL;
    genreIndex = NULL;
    realID = NULL;
    career = NULL;
    birthday = NULL;
    IdUser = NULL;
    nameIndex = NULL;
    authorIndex = NULL;
    publisherIndex = NULL;
    genreIndex = NULL;
    dateIndex = NULL;
    imageIndex = NULL;
}

bool Database::write_into_lostbooks(QString UserID, QString BookID, bool checkstate)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO LostBooks (UserID, BookID) VALUES (:UserID, :BookID)");
    qry.bindValue(":UserID", UserID);
    qry.bindValue(":BookID", BookID);
    if(qry.exec()){
        LostBooks_c temp;
        temp.UserID = UserID;
        temp.BookID = BookID;
        temp.CheckState = checkstate;
        LostBooksData.append(temp);
        return true;
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, process has failed.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
        return false;
    }
}

bool Database::delete_data_in_lostbooks(QString UserID, QString BookID)
{
    QSqlQuery qry;
    qry.prepare("DELETE FROM LostBooks WHERE UserID = '"+UserID+"' and BookID = '"+BookID+"'");
    if(qry.exec()){
        for(int i = 0; i < LostBooksData.size(); ++i){
            if(LostBooksData[i].UserID == UserID && LostBooksData[i].BookID == BookID)
                LostBooksData.erase(LostBooksData.begin() + i);
        }
        return true;
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, process has failed.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
        return false;
    }
}

bool Database::change_lostbook_checkstate(LostBooks_c lost)
{
    QSqlQuery qry;
    QString UserID = lost.UserID;
    QString BookID = lost.BookID;
    bool checkstate = lost.CheckState;
    qry.prepare("UPDATE LostBooks SET CheckState = ? WHERE UserID = '"+UserID+"' and BookID = '"+BookID+"'");
    qry.addBindValue(checkstate);
    if(qry.exec()){
        for(int i = 0; i < LostBooksData.size(); ++i){
            if(LostBooksData[i].UserID == UserID && LostBooksData[i].BookID == BookID)
                LostBooksData[i].CheckState = checkstate;
        }
        return true;
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, process has failed.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
        return false;
    }
}

bool Database::write_into_readernoti(QString UserID, QString BookID, QString content, int ON)
{
    QDate date = QDate::currentDate();
    QSqlQuery query;
    query.prepare("INSERT INTO ReaderNoti (UserID, Date, Content, BookID, Account_no, OrdinalNumber) "
                  "VALUES (:UserID, :Date, :Content, :BookID, :Account_no, :OrdinalNumber)");
    query.bindValue(":UserID", UserID);
    query.bindValue(":Date", date);
    query.bindValue(":Content", content);
    query.bindValue(":BookID", BookID);
    query.bindValue(":OrdinalNumber", ON);
    if(query.exec()){
        ReaderNoti_c temp;
        temp.ON = ON;
        temp.BookID = BookID;
        temp.UserID = UserID;
        temp.date = date.toString();
        temp.content = content;
        ReaderNotiData.append(temp);
        //delete frome userdemand
        QSqlQuery query1;
        query1.prepare("DELETE FROM UserDemand "
                       "WHERE UserID = '"+UserID+"' and BorrowBookID = '"+BookID+"'");
        if(query1.exec()){
            for(int i = 0; i < UserDemandData.size(); ++i){
                if(UserDemandData[i].UserID == UserID &&
                        UserDemandData[i].BorrowBookID == BookID){
                    UserDemandData.erase(UserDemandData.begin() + i);
                }
            }
            return true;
        }
        else {
            QMessageBox *alert = new QMessageBox();
            alert->setText("Unexpected issues occur, process has failed.");
            alert->setWindowIcon(QIcon(":/images/error.png"));
            alert->setWindowTitle("Error");
            alert->show();
            return false;
        }
        query1.clear();
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, process has failed.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
        return false;
    }
}

bool Database::delete_from_userdemand_data(QString UserID, QString BorrowedBookID)
{
    QSqlQuery qry;
    qry.prepare("DELETE FROM UserDemand WHERE UserID = '"+UserID+"' and BorrowBookID = '"+BorrowedBookID+"'");
    if(qry.exec()){
        for(int i = 0; i < UserDemandData.size(); ++i){
            if(UserDemandData[i].UserID == UserID && UserDemandData[i].BorrowBookID == BorrowedBookID)
                UserDemandData.erase(UserDemandData.begin() + i);
        }
        return true;
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, process has failed.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
        return false;
    }
}

bool Database::delete_reader_noti_indata(ReaderNoti_c noti)
{
    QSqlQuery query1;
    query1.prepare("DELETE FROM ReaderNoti "
                   "WHERE OrdinalNumber = ?");
    query1.addBindValue(noti.ON);
    if(query1.exec()){
        for(int i = 0; i < ReaderNotiData.size(); ++i){
            if(ReaderNotiData[i].ON == noti.ON){
                ReaderNotiData.erase(ReaderNotiData.begin() + i);
            }
        }
        return true;
    }
    else {
        return false;
    }
}

void Database::delete_all_reader_noti(ReaderNoti_c noti)
{
    QString id = noti.UserID;
    QSqlQuery query;
    query.prepare("DELETE FROM ReaderNoti WHERE UserID = '"+id+"'");
    if(query.exec()){
        return;
    }
    else return;
}

QVector<int> Database::set_next_date(QDate currentdate, int duration)
{
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int newday = currentdate.day(), newmonth = currentdate.month(), newyear = currentdate.year();
    if(currentdate.year()%100 != 0 && currentdate.year()%4 == 0){
        month[1] = 29;
    }
    for(int i = 0; i < 12; ++i){
        if(newmonth == i + 1){
            if(newday + duration > month[i]){
                newday = newday + duration;
                while(month[newmonth - 1] < newday){
                    if(newmonth == 12){
                        newyear = newyear + 1;
                        newmonth = 1;
                    }
                    else {
                        newmonth = newmonth + 1;
                    }
                    newday = newday - month[newmonth - 1];
                }
            }
            else {
                newday = newday + duration;
            }
            break;
        }
    }
    QVector<int> date;
    date.append(newday);
    date.append(newmonth);
    date.append(newyear);
    return date;
}

bool Database::write_into_orderlist(UserDemand_c *request)
{
    //write
    QDate borrowday = QDate::currentDate();
    QVector<int> date = set_next_date(borrowday, request->Duration);
    QDate returnday(date[2],date[1],date[0]);
    QSqlQuery query;
    query.prepare("INSERT INTO OrderList (UserID , BookID , BorrowDay , ReturnDay) "
                  "VALUES (:UserID , :BookID , :BorrowDay , :ReturnDay )");
    QString id = request->UserID;
    QString bookid = request->BorrowBookID;
    query.bindValue(":UserID",id);
    query.bindValue(":BookID",bookid);
    query.bindValue(":BorrowDay",borrowday);
    query.bindValue(":ReturnDay",returnday);
    if(query.exec()){
        OrderList_c temp;
        temp.UserID = request->UserID;
        temp.BookID = request->BorrowBookID;
        temp.BorrowDay = borrowday.toString();
        temp.ReturnDay = returnday.toString();
        OrderListData.append(temp);
        QSqlQuery query1;
        query1.prepare("DELETE FROM UserDemand "
                       "WHERE UserID = '"+request->UserID+"' and BorrowBookID = '"+request->BorrowBookID+"'");
        if(query1.exec()){
            for(int i = 0; i < UserDemandData.size(); ++i){
                if(UserDemandData[i].UserID == request->UserID && UserDemandData[i].Duration == request->Duration &&
                        UserDemandData[i].BorrowBookID == request->BorrowBookID){
                    UserDemandData.erase(UserDemandData.begin() + i);
                }
            }
            return true;
        }
        else {
            QMessageBox *alert = new QMessageBox();
            alert->setText("Unexpected issues occur, process has failed.");
            alert->setWindowIcon(QIcon(":/images/error.png"));
            alert->setWindowTitle("Error");
            alert->show();
            return false;
        }
        query1.clear();
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, process has failed.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
        return false;
    }
}

bool Database::delete_book_from_orderlist(QString UserID, QString BookID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM OrderList WHERE UserID = '"+UserID+"' and BookID = '"+BookID+"'");
    if(query.exec()){
        for(int i = 0; i < OrderListData.size(); ++i){
            if(OrderListData[i].UserID == UserID && OrderListData[i].BookID == BookID)
                OrderListData.erase(OrderListData.begin() + i);
        }
        return true;
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, process has failed.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
        return false;
    }
}

void Database::write_into_userdemand_data(QString userid, QString borrowBookId, int duration)
{
    QSqlQuery query;
    query.prepare("INSERT INTO UserDemand (UserID, BorrowBookID, Duration) "
                  "VALUES (:UserID, :BorrowBookID , :Duration)");
    query.bindValue(":UserID",userid);
    query.bindValue(":BorrowBookID",borrowBookId);
    query.bindValue(":Duration",duration);
    if(query.exec())
    {
        UserDemand_c temp;
        temp.UserID = userid;
        temp.BorrowBookID = borrowBookId;
        temp.Duration = duration;
        UserDemandData.append(temp);
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, fail to sent your request.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
    }
}

void Database::change_password(QString userID, QString newpassword)
{
    QSqlQuery query;
    query.prepare("UPDATE Account SET PASSWORD = '"+newpassword+"' WHERE ID='"+userID+"'");
    if(query.exec())
    {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Your password has been changed.");
        alert->setWindowIcon(QIcon(":/images/OK.png"));
        alert->setWindowTitle("Success");
        alert->show();
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Unexpected issues occur, fail to change your password.");
        alert->setWindowIcon(QIcon(":/images/error.png"));
        alert->setWindowTitle("Error");
        alert->show();
    }
}

void Database::add_data_to_lib_borrowedbooks()
{
    LibBorrowBooksData.clear();
    for(int i = 0; i < UserData.size(); ++i){
        LibBorrowedBooks_c temp;
        temp.UserID = UserData[i].UserID;
        temp.UserName = UserData[i].Name;
        for(int j = 0; j < OrderListData.size(); ++j){
            if(OrderListData[j].UserID == UserData[i].UserID){
                for(int k = 0; k < BookData.size(); ++k){
                    if(BookData[k].BookID == OrderListData[j].BookID)
                        temp.BorrowedBooks.append(BookData[k]);
                }
            }
        }
        if(temp.BorrowedBooks.isEmpty() == false)
            LibBorrowBooksData.append(temp);
    }
}

Database::~Database()
{

}
