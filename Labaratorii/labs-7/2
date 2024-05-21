#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
class Shape{
protected:
    int a;
public:
    Shape(){
        a=0;
    }
    Shape(int a){
        this->a=a;
    }
    virtual double plostina()=0;
    virtual void pecati()=0;
    virtual int getType()=0;
};

class Square:public Shape{
public:
    Square():Shape(){}
    Square(int a):Shape(a){}
    double plostina(){
        return a*a;
    }
    int getType(){
        return 1;
    }
    void pecati(){
        cout<<"Kvadrat so plostina = "<<plostina()<<endl;
    }


};
class Circle:public Shape{
public:
    Circle():Shape(){}
    Circle(int a):Shape(a){}
    double plostina(){
        return 3.14*a*a;
    }
    int getType(){
        return 2;
    }
    void pecati(){
        cout<<"Krug so plostina = "<<plostina()<<endl;
    }

};
class Triangle:public Shape{
public:
    Triangle():Shape(){}
    Triangle(int a):Shape(a){}
    double plostina(){
        return (sqrt(3)/4) * a * a;
    }
    int getType(){
        return 3;
    }
    void pecati(){
        cout<<"Triagolnik so plostina = "<<plostina()<<endl;
    }

};
void checkNumTypes(Shape** niza, int n){
    int brojachK,brojachT,brojachC;
    brojachC=brojachK=brojachT=0;
    for (int i = 0; i < n; ++i) {
        Square *s=dynamic_cast<Square*>(niza[i]);
        if(s){
            brojachK++;
        }
        else{
            Circle *c=dynamic_cast<Circle*>(niza[i]);
            if(c){
                brojachC++;
            }
            else
            {
                Triangle *t=dynamic_cast<Triangle*>(niza[i]);
                if(t){
                    brojachT++;
                }
            }
        }
    }
    cout<<"Broj na kvadrati vo nizata = "<<brojachK<<endl;
    cout<<"Broj na krugovi vo nizata = "<<brojachC<<endl;
    cout<<"Broj na triagolnici vo nizata = "<<brojachT<<endl;
}

int main(){


    int n;
    cin >> n;

    //TODO: inicijaliziraj niza od pokazuvachi kon klasata Shape
    Shape **niza=new Shape * [n];
    //TODO: alociraj memorija so golemina n za prethodno navedenata niza
    int classType;
    int side;

    //TODO: konstruiraj for ciklus so chija pomosh ke ja popolnish nizata
    for(int i = 0; i < n; ++i){

        cin >> classType;
        cin >> side;
        if(classType == 1)
            niza[i] = new Square(side);
        else if(classType == 2)
            niza[i] = new Circle(side);
        else if(classType == 3)
            niza[i] = new Triangle(side);
    }


    for(int i = 0; i < n; ++i){

        niza[i]->pecati();
    }

    checkNumTypes(niza, n);


    return 0;
}
