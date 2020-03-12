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