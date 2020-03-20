# include<iostream>
# include<fstream>
# include<cctype>
# include<cstring>
# include<cstdlib>
# include "genSplay.h"

using namespace std;

class Word{
public:
    Word(){
        freq = 1;
    }
    int operator==(const Word& ir){
        return strcmp(word, ir, word) < 0;
    }
private:
    char* word;
    int freq;
    friend class WordSplay;
    friend ostream& operator<< (ostream&, const Word&);
};

class WordSplay : public SplayTree<Word>{
public:
    WordSplay(){ diffrentWords = wordCnt = 0; }
    void run(ifstream&, char*);
private:
    int diffrentWords, wordCnt;
    void visit(SplayingNode<Word>*);
};

void WordSplay::visit(SplayingNode<Word> *p){
    diffrentWords += 1;
    wordCnt += p->info.freq;
}

void WordSplay::run(ifstream& fIn, char* filaname){
    char ch = ' ', i;
    char s[100];
    Word rec;
    while(!fIn.eof()){
        while(1){
            if(!fIn.eof() && !isalpha(ch))
                fIn.get(ch);
            else
                break;
        }
        for(i=0;!fIn.eof()&&isalpha(ch);i++){
            // s[i] = toupper(ch);
            fIn.get(ch);
        }
        s[i] = '\0';
        if(!(rec.word = new char[strlen(s)+1])){
            cerr << "no room for new words.\n";
            exit(1);
        }
        strcpy(rec.word, s);
        Word *p = search(rec);
        if(p==0){
            insert(rec);
        }       
        else p->freq++;
    }
    inorder();
    cout << "\n\nFile" << filaname <<
    "contains" << wordCnt << "words among which "<<
    diffrentWords << "are diffrent\n";
}

int main(int argc, char* argv[]){
    char filename[80];
    WordSplay splayTree;
    if( argc != 2){
        cout << "Enter a filename: ";
        cin >> filename;
    }
    else strcpy(filename, argv[1]);
    ifstream fIn(filename);
    if(fIn.fail()){
        cerr << "Cannot open!" << filename << endl;
        return 0;
    }
    splayTree.run(fIn, filename);
    fIn.close();
    return 0;
}