#include "maze.h"

//构造函数
Maze::Maze() : exitMarker('e'), entryMarker('m'),visited('.'),
                passage('0'), wall('1'){
    Stack<char*> mazeRows;
    char str[80], *s;
    int col, row=0;
    cout << "Enter a rectangular maze using the following "
         << "characters:\nm-entry\ne-exit\n1-wall\n0-passage\n"
         << "Enter one line at time; end with Ctrl-z:\n";
    while(cin >> str){
        row++;
        cols = strlen(str);
        s = new char[cols+3]; // 构造最外面的墙需要额外的长度

        mazeRows.push(s);
        strcpy(s+1, str);  //做移位，第一位要留作外部围墙
        s[0] = s[cols + 1] = wall; //构造围墙
        s[cols+2] = '\0';
        // 构造出口, strchr是一个查找函数
        if (strchr(s, exitMarker) != 0){
            exitCell.x = row;
            exitCell.y = strchr(s, exitMarker) - s;
        }
        // 构造起点
        if (strchr(s, entryMarker) != 0){
            entryCell.x = row;
            entryCell.y = strchr(s, entryMarker) -s;
        }
    }
    rows = row;
    store = new char*[row+2]; //给最上面加墙
    store[0] = new char[cols+3];
    for(;!mazeRows.empty();row--){
        store[row] = mazeRows.pop();
    }
    store[rows+1] = new char[cols+3]; //给最下面加墙
    for(col=0;col<=cols+1;col++){
        store[0][col] = wall;  //墙
        store[row+1][col] = wall; //墙
    }
}

void Maze::pushUnvisited(int row, int col){
    if(store[row][col] == passage || store[row][col] == exitMarker){
        mazeStack.push(Cell(row,col));
    }
}

void Maze::exitMaze(){
    int row, col;
    currentCell = entryCell;
    while(!(currentCell == exitCell)){
        row = currentCell.x;
        col = currentCell.y;
        cout << *this;
        if(!(currentCell == entryCell))
            store[row][col] = visited;
        pushUnvisited(row-1,col);
        pushUnvisited(row+1,col);
        pushUnvisited(row,col-1);
        pushUnvisited(row,col+1);
        if(mazeStack.empty()){
            cout << *this;
            cout << "Failure";
            return;
        }
        else currentCell = mazeStack.pop();
    }
    cout << *this;
    cout << "Success!\n";
}

ostream& operator<<(ostream& out, const Maze& maze){
    for(int row=0;row<=maze.rows+1;row++){
        out << maze.store[row] << endl;
    }
    out << endl;
    return out;
}


int main(){
    Maze().exitMaze();
    return 0;
}
