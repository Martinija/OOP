#include <iostream>
#include <cstring>
using namespace std;
#define MAX 100
enum typeC{
    standard,loyal,vip
};
char Tip[100][100]={"standard","loyal","vip"};
class Customer{
private:
    char ime[50];
    char adresa[50];
    typeC type;
    static double osnovenPopust;
    static double dopolnitelenPopust;
    int kupeniProizvodi;

    void copy(const Customer&other){
        strcpy(this->ime,other.ime);
        strcpy(this->adresa,other.adresa);
        this->type=other.type;
        kupeniProizvodi=other.kupeniProizvodi;
    }
public:
    Customer(){
        strcpy(this->ime," ");
        strcpy(this->adresa," ");
//        osnovenPopust=10;
//        dopolnitelenPopust=20;
        this->type=standard;
        this->kupeniProizvodi=0;
    }
    Customer(char *ime,char *adresa,typeC type,int kupeniProizvodi){
        strcpy(this->ime,ime);
        strcpy(this->adresa,adresa);
        this->type=type;
        this->kupeniProizvodi=kupeniProizvodi;
//        osnovenPopust=10;
//        dopolnitelenPopust=20;
    }
    ~Customer(){}
    friend ostream &operator<<(ostream &o,Customer&c){
        o<<c.ime<<endl;
        o<<c.adresa<<endl;
        o<<c.kupeniProizvodi<<endl;
        if(c.type==standard){
            o<<"standard 0"<<endl;
        }
        else if(c.type==loyal){
            o<<"loyal "<<c.osnovenPopust<<endl;
        }
        else if(c.type==vip){
            o<<"vip "<<c.osnovenPopust+c.dopolnitelenPopust<<endl;
        }
        return o;
    }
     void setDiscount1(double discount){
        osnovenPopust=discount;
    }

     char *getIme() {
         return ime;
    }

    typeC getType() {
        return type;
    }

     static double getOsnovenPopust(){
        return osnovenPopust;
    }

     static double getDopolnitelenPopust(){
        return dopolnitelenPopust;
    }

    int getKupeniProizvodi() const{
        return kupeniProizvodi;
    }

     char *getAdresa() {
         return adresa;
     }

    void setType(typeC type){
        Customer::type = type;
    }
};
double Customer::osnovenPopust=10;
double Customer::dopolnitelenPopust=20;
class UserExistsException{
public:
    void print(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

class FINKI_bookstore{
private:
    Customer *kupuvaci;
    int n;
public:
    FINKI_bookstore(){
        kupuvaci= nullptr;
        n=0;
    }
    FINKI_bookstore(const FINKI_bookstore&other){
        this->n=other.n;
        this->kupuvaci=new Customer[n];
        for (int i = 0; i < other.n; ++i) {
            this->kupuvaci[i]=other.kupuvaci[i];
        }
    }
    FINKI_bookstore &operator=(const FINKI_bookstore &other){
        if(this!=&other){
            delete []kupuvaci;
            this->n=other.n;
            for (int i = 0; i < other.n; ++i) {
                this->kupuvaci[i]=other.kupuvaci[i];
            }
        }
        return *this;
    }
    FINKI_bookstore &operator+=(Customer &other){
        for (int i = 0; i < n; ++i) {
            if(strcmp(kupuvaci[i].getAdresa(),other.getAdresa())==0){
                throw UserExistsException();
            }
        }
        Customer *tmp=new Customer[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=kupuvaci[i];
        }
        tmp[n]=other;
        delete []kupuvaci;
        this->kupuvaci=tmp;
        n++;
        return *this;
    }
    void update(){
        for (int i = 0; i < n; ++i) {
            if(kupuvaci[i].getKupeniProizvodi()>5 && kupuvaci[i].getType()==standard){
                kupuvaci[i].setType(loyal);
            }
            else if(kupuvaci[i].getKupeniProizvodi()>10 && kupuvaci[i].getType()==loyal){
                kupuvaci[i].setType(vip);
            }
        }
    }
    friend ostream &operator<<(ostream &o,FINKI_bookstore&f){
        for (int i = 0; i < f.n; ++i) {
            o<<f.kupuvaci[i];
        }
        return o;
    }
     void setCustomers(Customer *kupuvachi,int n){
        this->n=n;
        this->kupuvaci=new Customer[n];
         for (int i = 0; i < n; ++i) {
             this->kupuvaci[i]=kupuvachi[i];
         }
    }
    ~FINKI_bookstore(){
        delete []kupuvaci;
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc += c;
        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;
        }
        catch (UserExistsException e){
            e.print();
        }
        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
