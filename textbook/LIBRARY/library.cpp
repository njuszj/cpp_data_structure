#include<iostream>
#include<string>
#include<list>
#include<algorithm>
#include<cstring>

using namespace std;

class Patron;  // 预先定义

class Book{
public:
    Book(){
        patron = 0;
    }
    bool operator==(const Book& bk) const{
        return strcmp(title, bk.title) == 0;
    }
private:
    char *title;
    Patron *patron;
    ostream& printBook(ostream&) const;
    friend ostream& operator<<(ostream& out, const Book& bk){
        return bk.printBook(out);
    }
    friend class CheckedOutBook;
    friend Patron;
    friend void includeBook();
    friend void checkOutBook();
    friend void returnBook();
};

class Author{
public:
    Author(){}
    bool operator==(const Author& ar) const
}