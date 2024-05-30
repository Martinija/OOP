#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

class Ucesnik{
private:
    char *ime;
    bool pol;
    int vozrast;
    void copy(const Ucesnik &other){
        this->ime=new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->pol=other.pol;
        this->vozrast=other.vozrast;
    }
public:
    Ucesnik(){
        this->ime=new char[5];
        strcpy(this->ime,"ime");
        this->pol=false;
        this->vozrast=0;
    }
    Ucesnik(char *ime, bool pol, int vozrast){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->pol=pol;
        this->vozrast=vozrast;
    }
    Ucesnik(const Ucesnik &other){
        copy(other);
    }
    ~Ucesnik(){
        delete []ime;
    }
    Ucesnik& operator=(const Ucesnik &other){
        if(this==&other){
            return *this;
        }
        delete []ime;
        copy(other);
        return *this;
    }
    bool operator >( const Ucesnik &p)
    {
        return p.vozrast >this->vozrast;
    }
    friend ostream &operator<<(ostream &o,Ucesnik &u){
        o << u.ime << "\n" << (u.pol ? "mashki" : "zhenski") << "\n" << u.vozrast << "\n";
        return o;
    }

    int getVozrast()  {
        return vozrast;
    }
};
class Maraton{
private:
    char lokacija[100];
    Ucesnik *niza;
    int n;
    void copy(const Maraton &other){
        strcpy(lokacija,other.lokacija);
        this->niza=new Ucesnik[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->niza[i]=other.niza[i];
        }
        this->n=other.n;
    }
public:
    Maraton() {
        strcpy(this->lokacija, " ");
        this->niza = nullptr;
        this->n = 0;
    }
    Maraton(char *lokacija){
        strcpy(this->lokacija,lokacija);
        this->niza = nullptr;
        this->n = 0;
    }
    Maraton(const Maraton& other){
        copy(other);
    }
    ~Maraton(){
        delete []niza;
    }
    Maraton& operator=( const Maraton&other){
        if(this==&other){
            return *this;
        }
        delete []niza;
        copy(other);
        return *this;
    }
    Maraton& operator+=(const Ucesnik& other) {
        Ucesnik* tmp = new Ucesnik[n + 1];
        for(int i = 0; i < n; i++) {
            tmp[i] = this->niza[i];
        }
        tmp[n++] = other;

        delete [] niza;
        this->niza = new Ucesnik[n];
        for(int i = 0; i < n; i++) {
            this->niza[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }
    double prosecnoVozrast(){
        double avg=0;
        for (int i = 0; i < n; ++i) {
            avg+=niza[i].getVozrast();
        }
        return avg/(double)n;
    }
    void pecatiPomladi(Ucesnik &u){
        for(int i=0;i<n;i++){
            if(this->niza[i]>u){
                cout<<niza[i];
            }
        }
    }
};

// vashiot kod ovde


int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);

    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
