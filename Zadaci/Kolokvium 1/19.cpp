//Partially correct
#include <iostream>
#include <cstring>
using namespace std;
class IceCream{
private:
    char *ime;
    char sostav[100];
    float cena;
    float popust;

    void copy(const IceCream&other){
        this->ime=new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        strcpy(this->sostav,other.sostav);
        this->cena=other.cena;
        this->popust=other.popust;

    }
public:
    IceCream(){
        this->ime = new char[5];
        strcpy(this->ime, "name");
        this->cena = 0;
        this->popust = 0;
    }
    IceCream(char *ime,char *sostav,float cena,float popust=0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->sostav,sostav);
        this->cena=cena;
        this->popust=popust;
    }
    IceCream(const IceCream&other){
        copy(other);
    }
    ~IceCream(){
        delete[]ime;
    }
    IceCream& operator=(const IceCream &other){
        if(this==&other){
            return *this;
        }
        delete[]ime;
        copy(other);
        return *this;
    }
    friend ostream& operator<<(ostream&o,const IceCream&i){
        o<<i.ime<<": "<<i.sostav<<" "<<i.cena<<" ";
        if(i.popust!=0){
            o<<"("<<(i.cena-((i.popust/100.0)*i.cena))<<")";
        }
        return o;
    }
    IceCream&operator++(){
        popust+=5;
        return*this;
    }
    IceCream&operator+(const char*add){
        char *tmp=new char[strlen(ime)+ strlen(add)+1];
        strcat(tmp,ime);
        strcat(tmp," + ");
        strcat(tmp,add);
        strcpy(this->ime,tmp);
        cena+=10;
        return *this;
    }
    void setDiscount(float discount){
        if(discount>=0&&discount<101)
        {popust= discount;}
    }
    void setName(char *name){
        strcpy(ime,name);
    }

};
class IceCreamShop{
private:
    char ime[50];
    IceCream *sladoledi;
    int n;
    void copy(const IceCreamShop&other){
        strcpy(this->ime,other.ime);
        this->sladoledi=new IceCream[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->sladoledi[i]=other.sladoledi[i];
        }
        this->n=other.n;
    }
public:
    IceCreamShop() {
        strcpy(this->ime, "name");
        sladoledi = nullptr;
        this->n = 0;
    }
    IceCreamShop(char *name){
        strcpy(ime,name);
        sladoledi= nullptr;
        n=0;
    }
    IceCreamShop(const IceCreamShop&other){
        copy(other);
    }
    ~IceCreamShop(){
        delete[]sladoledi;
    }
    IceCreamShop&operator=(const IceCreamShop&other){
        if(this==&other){
            return *this;
        }
        delete[]sladoledi;
        copy(other);
        return *this;
    }
    IceCreamShop& operator+=(const IceCream&other){
        IceCream*tmp=new IceCream[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=sladoledi[i];
        }
        tmp[n++]=other;
        delete[]sladoledi;
       sladoledi=tmp;
      return *this;

    }
    friend ostream&operator<<(ostream &o,IceCreamShop &ic){
        o<<ic.ime<<endl;
        for (int i = 0; i < ic.n; ++i) {
            o<<ic.sladoledi[i]<<endl;
        }
        return o;
    }
};
int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}

