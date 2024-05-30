#include <iostream>
#include <cstring>
using namespace std;
class Pica{
private:
    char ime[15];
    float cena;
    char *sostojki;
    int namalenaCena;

    void copy(const Pica&other){
        strcpy(this->ime,other.ime);
        this->cena=other.cena;
        this->sostojki=new char [strlen(other.sostojki)+1];
        strcpy(this->sostojki,other.sostojki);
        this->namalenaCena=other.namalenaCena;
    }
public:
    Pica(){
        strcpy(ime,"ime");
        cena=0;
        sostojki= nullptr;
        namalenaCena=0;
    }
    Pica(char *ime,float cena,  char *sostojki, int namalenaCena){
        strcpy(this->ime,ime);
        this->cena=cena;
        this->sostojki=new char[strlen(sostojki)+1];
        strcpy(this->sostojki, sostojki);
        this->namalenaCena=namalenaCena;

    }
    Pica(const Pica &other){
        copy(other);
    }
    Pica &operator=(const Pica&other){
        if(this==&other){
            return *this;
        }
        delete []sostojki;
        copy(other);
        return *this;
    }
    ~Pica(){
        delete[] sostojki;
    }
    bool istiSe(Pica p){
        if(strcmp(sostojki,p.sostojki)==0){
            return true;
        }
        return false;
    }
    void pecati(){
        cout<<ime<<" - "<<sostojki<<", "<<cena;
    }

    float getCena() const {
        return cena;
    }

    int getNamalenaCena() const {
        return namalenaCena;
    }
};
class Picerija{
private:
    char ime[15];
    Pica *pici;
    int n;

    void copy(const Picerija&other){
        strcpy(this->ime,other.ime);
        this->pici=new Pica[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->pici[i]=other.pici[i];
        }
        this->n=other.n;
    }
public:
    Picerija(){
        strcpy(ime,"ime");
        pici= nullptr;
        n=0;
    }
    Picerija(char *ime){
        strcpy(this->ime,ime);
        pici= nullptr;
        n=0;
    }
    Picerija(const Picerija&other){
        copy(other);
    }
    ~Picerija(){
        delete []pici;
    }
    Picerija& operator=(const Picerija &other){
        if(this==&other){
            return *this;
        }
        delete []pici;
        copy(other);
        return *this;
    }
    Picerija& operator+=(const Pica&other){
       bool isti=false;
        for (int i = 0; i < n; ++i) {
            if(pici[i].istiSe(other)){
                isti=true;
            }
        }
        if(!isti){
            Pica *tmp=new Pica[n+1];
            for (int i = 0; i < n; ++i) {
                tmp[i]=pici[i];
            }
            tmp[n++]=other;
            delete[]pici;
            pici=tmp;

        }
        return *this;
    }

    void setIme(char *ime){
        strcpy(this->ime,ime);
    }
    const char *getIme() const {
        return ime;
    }
    void piciNaPromocija(){
        for (int i = 0; i < n; ++i) {
            if(pici[i].getNamalenaCena()!=0){
                pici[i].pecati();
                cout<<" "<<pici[i].getCena()*(1-pici[i].getNamalenaCena()/100.0)<<endl;
            }
        }
    }
};
int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}



