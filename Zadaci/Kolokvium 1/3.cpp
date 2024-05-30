#include <iostream>
#include <cstring>
using namespace std;
class StockRecord{
private:
    char id[12];
    char ime[50];
    double cena;
    double cenaAkcija;
    int akcii;

public:
    StockRecord(char* id=" ", char* ime=" ", double cena=0, int akcii=0,double cenaAkcija=0) {
        strcpy(this->id, id);
        strcpy(this->ime, ime);
        this->cena = cena;
        this->akcii = akcii;
        this->cenaAkcija=cenaAkcija;

    }
    StockRecord(const StockRecord &other){
        strcpy(this->id,other.id);
        strcpy(this->ime,other.ime);
        this->cena=other.cena;
        this->cenaAkcija=other.cenaAkcija;
        this->akcii=other.akcii;
    }
    ~StockRecord(){}
    /*StockRecord& operator=(const StockRecord& other) {
        if(this == &other) {
            return *this;
        }
        strcpy(this->id,other.id);
        strcpy(this->ime,other.ime);
        this->cena=other.cena;
        this->cenaAkcija=other.cenaAkcija;
        this->akcii=other.akcii;
        return *this;
    }
     */
    void setNewPrice(double c){
        cenaAkcija=c;
    }
    double value() const{
        return akcii*cenaAkcija;

    }
    double profit()const{
        return akcii*(cenaAkcija-cena);
    }
     friend ostream &operator<<(ostream &o,StockRecord &s){
        o<<s.ime<<" "<<s.akcii<<" "<<s.cena<<" "<<s.cenaAkcija<<" "<<s.profit();
        o<<endl;
        return o;
    }
     friend class Client;
};
class Client{
private:
    char ime[60];
    int id;
    StockRecord *niza;
    int n;
public:
    friend class StockRecord;
    Client(char* ime=" ", int id=0,int n=0) {
        strcpy(this->ime, ime);
        this->id = id;
        this->niza = new StockRecord[n];
        this->n = n;
    }
    /*
    Client& operator=(const Client &other){
        if(this == &other){
            return *this;
        }
        delete []this->niza;
            strcpy(this->ime, other.ime);
            this->id = other.id;
            this->niza = new StockRecord[other.n];
            for(int i = 0; i < other.n; i++) {
                this->niza[i] = other.niza[i];
            }
            this->n = other.n;

        return *this;
    }
*/
  Client &operator+=( const StockRecord &s){
        StockRecord *pomosna= new StockRecord[n+1];
        for(int i=0;i<n;i++){
            pomosna[i]= this->niza[i];
        }
        pomosna[n++]=s;
        delete[]niza;
        this->niza=new StockRecord[n];
        for(int i=0;i<n;i++){
            this->niza[i]=pomosna[i];
        }
        delete[] pomosna;
        return  *this;
    }
    
    double totalValue(){
        double value=0;
        for (int i = 0; i < n; ++i) {
            value+=niza[i].value();
        }
        return value;
    }
     friend ostream& operator<<(ostream &o,  Client &c){
        o<<c.id<<" "<<c.totalValue()<<endl;
        for (int i = 0; i < c.n; ++i) {
            o<<c.niza[i];
        }
        return o;
    }
    ~Client(){
        delete []niza;
    }
};


int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
