#include "algorithms.h"

int LevenshteinDistance::get_differences_between_2_strings(QString s, QString t)
{
    //degenerate cases
    if (s == t) return 0;
    else if (s.length() == 0) return t.length();
    else if (t.length() == 0) return s.length();
    int m = s.length() + 1;
    int n = t.length() + 1;
    QVector<QVector<int>> d;
    QVector<int> first_row, temp;

    for(int i = 0; i < n; ++i){
        first_row.push_back(i);
        temp.push_back(i-i);
    }
    d.push_back(first_row);

    for(int j = 1; j < m; ++j){
        temp[0] = j;
        d.push_back(temp);
    }

    for(int j = 1; j < n; ++j){
        for(int i = 1; i < m; ++i){
            int cost = 0;
            if(s[i-1] == t[j-1])
                cost = 0;
            else cost = 1;
            int a = d[i-1][j] + 1, b = d[i][j - 1] + 1, c = d[i-1][j-1] + cost;
            if(a <= b && b <= c)
                d[i][j] = a;
            else if(b <= a && b <= c)
                d[i][j] = b;
            else if(c <= a && c <= b)
                d[i][j] = c;
        }
    }
    return d[s.length()][t.length()];
}


Search::Search(QVector<Books_c> b)
{
    this->Books = b;
}

Search::Search(QVector<Account_c> a)
{
    this->Accounts = a;
}

Search::Search(QVector<User_c> u)
{
    this->Users = u;
}

void Search::setBookData(QVector<Books_c> b)
{
    this->Books = b;
}
void Search::setAccountData(QVector<Account_c> a)
{
    this->Accounts = a;
}

void Search::setUserData(QVector<User_c> u)
{
    this->Users = u;
}

QVector<Books_c> Search::getBookData()
{
    return this->Books;
}

QVector<Account_c> Search::getAccountData()
{
    return this->Accounts;
}

QVector<User_c> Search::getUserData()
{
    return this->Users;
}

void Search::findBookName(QString BName)
{
    if(BName.isEmpty() == false){
        QVector<int> number;
        QVector<Books_c> temp = this->Books;
        for(int i = 0; i < temp.size(); ++i){
            if(temp[i].BName.contains(BName) == false){
                temp.erase(temp.begin() + i);
                i--;
            }
        }
        this->Books = temp;
        for(int i = 0; i < this->Books.size(); ++i)
            number.append(LevenshteinDistance::get_differences_between_2_strings(BName,this->Books[i].BName));
        for(int i = 0; i < number.size(); ++i){
            int min = number[i];
            for(int j = i; j < number.size(); ++j){
                if(number[j] < min){
                    min = number[j];
                }
            }
            //swap
            for(int j = 0; j < number.size(); ++j){
                if(number[j] == min){
                    int temp = number[i];
                    number[i] = number[j];
                    number[j] = temp;
                    Books_c t = this->Books[i];
                    this->Books[i] = this->Books[j];
                    this->Books[j] = t;
                }
            }
        }
    }
}

void Search::findBookGenre(QString Genre)
{
    if(Genre.isEmpty() == false){
        QVector<int> number;
        QVector<Books_c> temp = this->Books;
        for(int i = 0; i < temp.size(); ++i){
            if(temp[i].Kind.contains(Genre) == false){
                temp.erase(temp.begin() + i);
                i--;
            }
        }
        this->Books = temp;
        for(int i = 0; i < this->Books.size(); ++i)
            number.append(LevenshteinDistance::get_differences_between_2_strings(Genre,this->Books[i].Kind));
        for(int i = 0; i < number.size(); ++i){
            int min = number[i];
            for(int j = i; j < number.size(); ++j){
                if(number[j] < min){
                    min = number[j];
                }
            }
            //swap
            for(int j = 0; j < number.size(); ++j){
                if(number[j] == min){
                    int temp = number[i];
                    number[i] = number[j];
                    number[j] = temp;
                    Books_c t = this->Books[i];
                    this->Books[i] = this->Books[j];
                    this->Books[j] = t;
                }
            }
        }
    }
}

void Search::findBookAuthor(QString Author)
{
    if(Author.isEmpty() == false){
        QVector<int> number;
        QVector<Books_c> temp = this->Books;
        for(int i = 0; i < temp.size(); ++i){
            if(temp[i].Author.contains(Author) == false){
                temp.erase(temp.begin() + i);
                i--;
            }
        }
        this->Books = temp;
        for(int i = 0; i < this->Books.size(); ++i)
            number.append(LevenshteinDistance::get_differences_between_2_strings(Author,this->Books[i].Author));
        for(int i = 0; i < number.size(); ++i){
            int min = number[i];
            for(int j = i; j < number.size(); ++j){
                if(number[j] < min){
                    min = number[j];
                }
            }
            //swap
            for(int j = 0; j < number.size(); ++j){
                if(number[j] == min){
                    int temp = number[i];
                    number[i] = number[j];
                    number[j] = temp;
                    Books_c t = this->Books[i];
                    this->Books[i] = this->Books[j];
                    this->Books[j] = t;
                }
            }
        }
    }
}

void Search::findBookPublisher(QString Publisher)
{
    if(Publisher.isEmpty() == false){
        QVector<int> number;
        QVector<Books_c> temp = this->Books;
        for(int i = 0; i < temp.size(); ++i){
            if(temp[i].Publisher.contains(Publisher) == false){
                temp.erase(temp.begin() + i);
                i--;
            }
        }
        this->Books = temp;
        for(int i = 0; i < this->Books.size(); ++i)
            number.append(LevenshteinDistance::get_differences_between_2_strings(Publisher,this->Books[i].Publisher));
        for(int i = 0; i < number.size(); ++i){
            int min = number[i];
            for(int j = i; j < number.size(); ++j){
                if(number[j] < min){
                    min = number[j];
                }
            }
            //swap
            for(int j = 0; j < number.size(); ++j){
                if(number[j] == min){
                    int temp = number[i];
                    number[i] = number[j];
                    number[j] = temp;
                    Books_c t = this->Books[i];
                    this->Books[i] = this->Books[j];
                    this->Books[j] = t;
                }
            }
        }
    }
}

void Search::findAccountName(QString accountName)
{

}

void Search::findUserName(QString UserName)
{

}

void Search::findUserGender(QString UserGender)
{

}

void Search::findUserEmail(QString email)
{

}

void Search::findUserRealID(QString RealID)
{

}

void Search::findUserCareer(QString Career)
{

}

void Search::findUserBirthday(QString birthday)
{

}
