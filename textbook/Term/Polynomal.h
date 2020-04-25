// 多项式处理

# ifndef POLYNOMAL_H
# define POLYNOMAL_H

# include <iostream>
using std::ostream;
using std::istream;

struct Term{
    float coef;  // 系数
    int exp; // 指数
    Term *link;
    Term(float c, int e, Term *next=NULL){
        coef = c;
        exp = e;
        link = next;
    }
    Term* InsertAfter(float c, int e);
    friend ostream& operator << (ostream&, const Term&);
};

class Polynomal{
public:
    Polynomal(){ first = new Term(0, -1); }
    Polynomal(Polynomal& R);
    int maxOrder();
    Term* getHead() const { return first; }
private:
    Term* first;
    friend ostream& operator << (ostream&, const Polynomal&);
    friend ostream& operator >> (istream&, const Polynomal&);
    friend Polynomal operator+(Polynomal&, Polynomal&);
    friend Polynomal operator*(Polynomal&, Polynomal&);
};

# endif