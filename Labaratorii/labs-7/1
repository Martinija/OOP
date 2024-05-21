#include <iostream>
#include <cstring>
using namespace std;
class ZicanInstrument{
protected:
    char name[20];
    int brojzhici;
    double cena;
public:
    ZicanInstrument(char *name=" ", int brojzhici=0, double cena=0) : brojzhici(brojzhici), cena(cena) {
        strcpy(this->name, name);

    }
     virtual ~ZicanInstrument(){}
     virtual double price()=0;

    bool operator==(const ZicanInstrument &rhs) const {
        return brojzhici == rhs.brojzhici ;
    }
    friend ostream& operator<<(ostream &o,const ZicanInstrument &zi){
        o<<zi.name<<" "<<zi.brojzhici<<" "<<zi.cena<<endl;
        return o;
    }

    int getBrojzhici() const {
        return brojzhici;
    }

};
class Mandolina:public ZicanInstrument{
private:
    char forma[20];
public:
    Mandolina( char *name=" ", int brojzhici=0, double cena=0,char *forma=" "): ZicanInstrument(name,brojzhici,cena){
        strcpy(this->forma,forma);
    }
    ~Mandolina(){}
    double price(){
        if(strcmp(forma,"Neapolitan")==0){
            return cena*1.15;
        }
        else{
            return cena;
        }
    }
    friend ostream& operator<<(ostream &o,Mandolina &m){
        o << static_cast<const ZicanInstrument&>(m) << ", Form: " << m.forma;
        return o;
    }


};

class Violina:public ZicanInstrument{
private:
    double golemina;
public:
    Violina(char *name=" ", int brojzhici=0, double cena=0,double golemina=0):ZicanInstrument(name,brojzhici,cena){
        this->golemina=golemina;
    }
    double price(){
        if (golemina == 0.25) {
            return cena * 1.10;
        }
        else if (golemina == 1.00) {
            return cena * 1.20;
        }
        else {
            return cena;
        }
    }
    friend ostream& operator<<(ostream &o,Violina &v){
        o << static_cast<const ZicanInstrument&>(v) << ", Size: " << v.golemina;
        return o;

    }
    ~Violina(){}
};
void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n){
    for (int j = 0; j < n; j++) {
        if (zi.getBrojzhici() == i[j]->getBrojzhici()) {
            cout << i[j]->price() << endl;
        }
    }
}

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}
