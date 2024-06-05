#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

//место за вашиот код

class NegativnaVrednost{
public:
    void print(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};
class Oglas{
private:
    string naslov;
    string kategorija;
    string opis;
    double cena;
public:
    Oglas(string naslov=" ",string kategorija=" ",string opis=" ",double cena=0){
        this->naslov=naslov;
        this->kategorija=kategorija;
        this->opis=opis;
        this->cena=cena;
    }
    bool operator>(Oglas &other){
        return cena>other.cena;
    }
    friend ostream &operator<<(ostream &o,Oglas&og){
        o<<og.naslov<<endl;
        o<<og.opis<<endl;
        o<<og.cena<<" evra"<<endl;
    }

    const string &getNaslov() const {
        return naslov;
    }

    const string &getKategorija() const {
        return kategorija;
    }

    const string &getOpis() const {
        return opis;
    }

    double getCena() const {
        return cena;
    }
};

class Oglasnik{
private:
    string ime;
    Oglas *niza;
    int n;

    void copy(const Oglasnik&other){
        ime=other.ime;
        this->niza=new Oglas[other.n];
        for (int i = 0; i < other.n; ++i) {
            niza[i]=other.niza[i];
        }
        this->n=other.n;
    }
public:
    Oglasnik(string ime=""){
        this->ime=ime;
        niza= nullptr;
        n=0;
    }
    Oglasnik(const Oglasnik&other){
        copy(other);
    }
    Oglasnik &operator=(const Oglasnik &other){
        if(this!=&other){
            delete []niza;
            copy(other);
        }
        return *this;
    }
    ~Oglasnik(){
        delete []niza;
    }
    Oglasnik &operator+=(Oglas &other){
       if(other.getCena()<0){
           throw NegativnaVrednost();

       }
       Oglas *tmp=new Oglas[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=niza[i];
        }
        tmp[n++]=other;
        delete[] niza;
        niza=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &o,Oglasnik&ogl){
        o<<ogl.ime<<endl;
        for (int i = 0; i < ogl.n; ++i) {
            o<<ogl.niza[i]<<endl;
        }
        return o;
    }
    void oglasiOdKategorija(const char *k){
        for (int i = 0; i < n; ++i) {
            if(niza[i].getKategorija()==k){
                cout<<niza[i]<<endl;
            }
        }
    }
    void najniskaCena(){
        int idx = 0;
        float najmala=0;
        for(int i = 0; i < n; i++) {
            if(niza[i].getCena()<najmala) {
                idx=i;
                najmala=niza[i].getCena();
            }
        }
        cout << niza[idx] << "\n";
    }

};
int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost e){
                e.print();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost e){
                e.print();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
            ogl+=o;
            }
            catch (NegativnaVrednost e){
                e.print();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }
            catch (NegativnaVrednost e){
                e.print();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost e){
                e.print();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
