#include<iostream>
using namespace std;

class Animal{
public:
    Animal(){
        category = "Animal";
    }
    virtual ~Animal(){}
    void speak(){
        cout << "I am a kind of " << category << endl;
    }
    char const *category;
};

class Dog : public Animal{
public:
    Dog(){
        category = "Four leg";
    }
    void speak(){
        cout << "I am a Dog" << endl;
    }
};

int main(){
    Animal animal;
    Dog dog;
    Dog dogb;
    Animal* animalb = &dogb; 
    animalb->speak();
    dog.speak();
}