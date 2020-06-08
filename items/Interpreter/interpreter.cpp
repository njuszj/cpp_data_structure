#include <cctype>
#include "interpreter.h"

//在链表中寻找变量，找不到抛出一个错误
double Statement::findValue(char* id){
    IdNode tmp(id);
    list<IdNode>::iterator i = find(idList.begin(), idList.end(), tmp);
    if(i != idList.end()){
        return i->value;
    }
    else issueError("Unknown variable");
}

//加入一个变量
void Statement::processNode(char* id, double e){
    IdNode tmp(id,e);
    list<IdNode>::iterator i = find(idList.begin(), idList.end(), tmp);
    if(i != idList.end()){
        i -> value = e;
    }
    else idList.push_front(tmp);
}

//读入变量名
void Statement::readId(char *id){
    int i = 0;
    if(isspace(ch))
        cin >> ch; //判断非0后传入
    if(isalpha(ch)){
        while (isalnum(ch)){
            id[i++] = ch;
            cin.get(ch);
        }
    id[i] = '\0';
    }
    else issueError("Identifier expected");
}

double Statement::factor(){
    double var, minus = 1.0;
    static char id[200];
    cin >> ch;
    while (ch == '+' || ch == '-'){
        if(ch=='-')
            minus *= -1.0;
        cin >> ch;
    }
    if (isdigit(ch) || ch=='.'){
        cin.putback(ch);
        cin >> var >> ch;
    }
    else if(ch == '('){
        var = expression();
        if(ch == ')')
            cin >> ch;
        else issueError("Right paren left out");
    }
    else{
        readId(id);
        if(isspace(ch))
            cin >> ch;
        var = findValue(id);
    }
    return minus * var;
}

double Statement::term(){
    double f = factor();
    while(true){
        switch(ch){
            case '*': f *= factor(); break;
            case '/': f /= factor(); break;
            default: return f;
        }
    }
}

double Statement::expression(){
    double t = term();
    while(true){
        switch(ch){
            case '+': t += term(); break;
            case '-': t -= term(); break;
            default : return t;
        }
    }
}

double Statement::getStatement(){
    char id[20], command[20];
    double e;
    cout << "Enter a statement: ";
    cin >> ch;
    readId(id);
    // strupr(strcpy(command, id)); gcc没有定义up函数
    if(strcmp(command, "STATUS")==0) cout << *this;
    else if(strcmp(command, "PRINT") == 0){
        readId(id);
        cout << id << " = " << findValue(id) << endl;
    }
    else if(strcmp(command, "END")==0) exit(0);
    else {
        if(isspace(ch))
            cin >> ch;
        if(ch == '='){
            e = expression();
            if(ch != ';')
                issueError("There are some extras");
            else processNode(id, e);
        }
        else issueError("'=' is missing");
    }
}

ostream& operator<<(ostream& out, const IdNode& r){
    out << r.id << " = " << r.value << endl;
    return out;
}

ostream& operator<<(ostream& out, const Statement& s){
    list<IdNode>::const_iterator i = s.idList.begin();
    for(;i!=s.idList.end();i++){
        out << *i;
    }
    out << endl;
    return out;
}