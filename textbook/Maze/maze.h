// 经典的迷宫问题
// 使用栈进行解决

#ifndef MAZE
#define MAZE

#include<iostream>
#include<string>
#include<stack>
#include<cstring>

using namespace std;

// 重载一下stack的pop函数
template<class T>
class Stack : public stack<T> {
public:
    T pop(){
        T tmp = stack<T>::top();
        stack<T>::pop();
        return tmp;
    }
};

// 表示迷宫单位的类
class Cell {
public:
    Cell(int i = 0, int j = 0){
        x = i;
        y = j;
    }
    bool operator==(const Cell& c) const{
        return x == c.x && y == c.y;
    }
private:
    int x, y;
    friend class Maze;
};

class Maze{
public:
    Maze();
    void exitMaze();
private:
    Cell currentCell, exitCell, entryCell;
    const char exitMarker, entryMarker, visited, passage, wall; 
    // 表示开始位置、出口等的字符
    Stack<Cell> mazeStack;
    char **store; // 字符串数组
    void pushUnvisited(int, int);
    friend ostream& operator<<(ostream&, const Maze&);
    int rows, cols;
};

#endif