#ifndef PERSONAL
#define PERSONAL
// ifndef...define...endif 防止重复编译

#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;
class Personal{
public:
    Personal();
    Personal(char*,char*,char*,int,long);
    void writeToFile(fstream&) const;
    void readFromFile(fstream&);
    void readKey();
    int size() const{
        return 9 + nameLen + cityLen + sizeof(year) + sizeof(salary);
    }
    bool operator==(const Personal& pr) const{
        return strncmp(pr.SSN, SSN, 9) == 0;
    }
protected:
    const int nameLen, cityLen;
    char SSN[10], *name, *city;
    int year;
    long salary;
    ostream& writeLegibly(ostream&);
    istream& readFromConsole(istream&);
    friend ostream& operator<<(ostream& out, Personal& pr){
        return pr.writeLegibly(out);
    }
    friend istream& operator>>(istream& in, Personal& pr){
        return pr.readFromConsole(in);
    }
};

#endif