#include "personal.h"

// 默认构造函数
Personal::Personal():nameLen(10), cityLen(10) {
    name = new char[nameLen + 1];
    city = new char[cityLen + 1];
}

// 构造函数
Personal::Personal(char* ssn, char* n, char* c, int y, long s):nameLen(10),cityLen(10){
    name = new char[nameLen + 1];
    city = new char[cityLen + 1];
    strcpy(SSN, ssn);
    strcpy(name,n);
    strcpy(city,c);
    year = y;
    salary = s;
}

// 写入文件
void Personal::writeToFile(fstream& out) const {
    out.write(SSN, 9);
    out.write(name, nameLen);
    out.write(city, cityLen);
    out.write(reinterpret_cast<const char*>(&year),sizeof(int));  // C++标准转换运算符
    out.write(reinterpret_cast<const char*>(&salary),sizeof(int));
}

// 读取文件
void Personal::readFromFile(fstream& in){
    in.read(SSN, 9);
    in.read(name, nameLen);
    in.read(city, cityLen);
    in.read(reinterpret_cast<char*>(&year),sizeof(int));  // C++标准转换运算符
    in.read(reinterpret_cast<char*>(&salary),sizeof(int));  // 将salary强制转换为字节类型
}

//读取键值
void Personal::readKey() {
    char s[80];
    cout << "Enter SSN: ";
    cin.getline(s, 80);
    strncpy(SSN,s,9);
}

ostream& Personal::writeLegibly(ostream& out) {
    // 解决可读性的问题
    SSN[9] = name[nameLen] = city[cityLen] = '\0';
    out << "SSN= " << SSN << ", name= " << name
    << ", city= " << city << ", year= " << year
    << ", salary= " << salary;
    return out;
}

istream& Personal::readFromConsole(istream& in) {
    SSN[9] = name[nameLen] = city[cityLen] = '\0';
    char s[80];
    cout << "SSN: ";
    in.getline(s, 80);
    strncpy(SSN, s, 9);
    cout << "Name: ";
    in.getline(s, 80);
    strncpy(name, s, nameLen);
    cout << "City: ";
    in.getline(s, 80);
    strncpy(city, s, cityLen);
    cout << "Birthyear: ";
    in >> year;
    cout << "Salary: ";
    in >> salary;
    in.ignore();
    /*
        istream& ignore (streamsize n = 1, int delim = EOF);
        Extract and discard characters
        1. Extracts characters from the input sequence and discards them, until either n characters have been extracted, or one compares equal to delim.
        2. The function also stops extracting characters if the end-of-file is reached.
    */
    return in;
}


