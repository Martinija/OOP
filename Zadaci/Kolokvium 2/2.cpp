#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
class Vozac{
protected:
    char ime[100];
    int vozrast;
    double brTrki;
    bool veteran;

    void copy(const Vozac&other){
        strcpy(ime,other.ime);
        vozrast=other.vozrast;
        brTrki=other.brTrki;
        veteran=other.veteran;

    }
public:
    Vozac(char *ime=" ",int vozrast=0,double brTrki=0,bool veteran= false){
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->brTrki=brTrki;
        this->veteran=veteran;
    }
    ~Vozac(){}
    friend ostream&operator<<(ostream &o,Vozac&v){
        o<<v.ime<<"\n"<<v.vozrast<<"\n"<<v.brTrki<<"\n";
        if(v.veteran){
            o<<"VETERAN"<<endl;
        }
        
    }
    bool operator==(const Vozac&other){
        return brTrki==other.brTrki;
    }
    virtual double zarabotuvacka()=0;
    virtual double danok()=0;
};

class Avtomobilist:public Vozac{
private:
    double cena;
public:
    Avtomobilist(char *ime=" ",int vozrast=0,double brTrki=0,bool veteran= false,double cena=0): Vozac(ime,vozrast,brTrki,veteran){
        this->cena=cena;
    }
    bool operator==(Avtomobilist&other){
        return zarabotuvacka()==other.zarabotuvacka();
    }

    double zarabotuvacka(){
        return cena/5;
    }
    double danok(){
        if(brTrki>10){
            return zarabotuvacka()*0.15;
        }
        else{
            return zarabotuvacka()*0.1;
        }
    }


};

class Motociklist:public Vozac{
private:
    double moknost;
public:
    Motociklist(char *ime=" ",int vozrast=0,double brTrki=0,bool veteran= false,double moknost=0): Vozac(ime,vozrast,brTrki,veteran){
        this->moknost=moknost;
    }
    ~Motociklist(){}
    double zarabotuvacka(){
        return moknost*20;
    }
    bool operator==(Avtomobilist&other){
        return zarabotuvacka()==other.zarabotuvacka();
    }
    double danok(){
        if(veteran){
            return zarabotuvacka()*0.25;
        }
        else{
            return zarabotuvacka()*0.2;
        }
    }

};
 int soIstaZarabotuvachka(Vozac **niza,int n,Vozac *other){
     int brojach=0;
    for (int i = 0; i < n; ++i) {
        if(niza[i]->zarabotuvacka()==other->zarabotuvacka()){
            brojach++;
        }
    }
     return brojach;
}
// vashiot kod ovde

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
