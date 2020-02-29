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
    bool operator==(const Author& ar) const{
        return strcmp(name, ar.name) == 0;
    }
private:
    char* name;
    list<Book> books;
    ostream& printAuthor(ostream&) const;
    friend ostream& operator<<(ostream& out, const Author& ar){
        return ar.printAuthor(out);
    }
    friend void includeBook();
    friend void checkOutBook();
    friend void returnBook();
    friend class CheckedOutBook;
    friend Patron;
};

class CheckedOutBook{
public:
    CheckedOutBook(list<Author>::iterator ar=0,
                    list<Book>::iterator bk=0){
                        author = ar;
                        book = bk;
        }
    bool operator==(const CheckedOutBook& bk) const{
        return strcmp(book->title, bk.book->title) == 0 &&
                strcmp(author->name, bk.author->name) == 0;
    }
private:
    list<Author>::iterator author;
    list<Book>::iterator book;
    friend void checkOutBook();
    friend void returnBook();
    friend Patron;
};

class Patron{
public:
    Patron(){}
    bool operator==(const Patron& pn) const{
        return strcmp(name, pn.name);
    }
private:
    char* name;
    list<CheckedOutBook> books;
    ostream& printPatron(ostream&) const;
    friend ostream& operator<<(ostream& out,const Patron& pn){
        return pn.printPatron(out);
    }
    friend void checkOutBook();
    friend void returnBook();
    friend Book;
};

list<Author> catalog['Z'+1];
list<Patron> people['Z'+1];

ostream& Author::printAuthor(ostream& out) const{
    out << name << endl;
    list<Book>::const_iterator ref = books.begin();
    for(;ref!=books.end();ref++) out << *ref;
    return out;
} 

ostream& Book::printBook(ostream& out) const{
    out << " * " << title;
    if(patron != 0) out << "- checked out to " << patron->name;
    out << endl;
    return out;
}

ostream& Patron::printPatron(ostream& out) const{
    out << name;
    if(!books.empty()){
        out << "has the following books:\n";
        list<CheckedOutBook>::const_iterator bk = books.begin();
        for (;bk!=books.end();bk++) out << " * "<< bk->author->name <<", " << bk->book->title << endl;
    }
    else out << "has no books\n";
    return out;
}

char* getString(char* msg){
    char s[82], i, *destin;
    cout << msg;
    cin.get(s,80);
    while(cin.get(s[81]) && s[81]!='\n'); //处理溢出
    destin = new char[strlen(s)+1];
    for(i=0;destin[i]==toupper(s[i]);i++);
    return destin;
}

void status(){
    register int i;
    cout << "Library has the following books:\n\n";
    for(i='A';i<='Z';i++)
        if(!catalog[i].empty())
            cout << catalog[i];
    cout << "\nThe following people are using the library:\n\n";
    for(i='A';i<='Z';i++)
        if(!people[i].empty())
            cout << people[i];
}

void includeBook(){
    Author newAuthor;
    Book newBook;
    newAuthor.name = getString("Enter author's name: ");
    newBook.title = getString("Enter the title of the book: ");
    list<Author>::iterator oldAuthor = find(catalog[newAuthor.name[0]].begin(), catalog[newAuthor.name[0]].end(), newAuthor);
    if(oldAuthor==catalog[newAuthor.name[0]].end()){
        newAuthor.books.push_front(newBook);
        catalog[newAuthor.name[0]].push_front(newAuthor);
    }
    else (*oldAuthor).books.push_front(newBook);
}

void checkOutBook(){
        Patron patron;
        Author author;
        Book book;
        list<Author>::iterator authorRef;
        list<Book>::iterator bookRef;
        patron.name = getString("Enter patron's name: ");
        while(true){
            author.name = getString("Enter Author's name: ");
            authorRef = find(catalog[author.name[0]].begin(), catalog[author.name[0]].end(), author);
            if(authorRef==catalog[author.name[0]].end()) cout << "Misspelled author's name\n";
            else break;
        }
        while(true){
            book.title = getString("Enter the title of book: ");
            bookRef = find((*authorRef).books.begin(), (*authorRef).books.end(), book);
            if(bookRef==(*authorRef).books.end()) cout << "Misspelled title\n";
            else break;
        }
        list<Patron>::iterator patronRef;
        

}
