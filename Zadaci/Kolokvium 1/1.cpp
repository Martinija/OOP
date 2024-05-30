#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
enum tip{
    pop,rap,rock
};
class Pesna {
private:
    char ime[50];
    int minuti;
    tip type;

public:
    Pesna() {}

    Pesna(char *i, int m, tip t) {
        strcpy(ime, i);
        minuti = m;
        type = t;
    }
    ~Pesna() {}
    int getMinuti() const {
        return minuti;
    }

    void setMinuti(int minuti) {
        Pesna::minuti = minuti;
    }

    const char *getIme() const {
        return ime;
    }

    tip getType() const {
        return type;
    }

    void setType(tip type) {
        Pesna::type = type;
    }

    void pecati() {
        cout << "\"" << ime << "\"-" << minuti << "min" << endl;
    }

};
class CD{
private:
    Pesna song[10];
    int broj;
    int vreme;
public:
    CD(int vreme) : broj(0), vreme(vreme) {}
    ~CD(){}
    int getBroj() const {
        return broj;
    }

    void setBroj(int numPesni) {
        CD::broj = numPesni;
    }

    Pesna& getPesna(int i) {
        return song[i];
    }

    int getVreme() const {
        return vreme;
    }

    void setVreme(int vreme) {
        CD::vreme = vreme;
    }
    int vremetraenjePesni(){
        int vkupno=0;
        for(int i=0; i<broj;i++){
            vkupno+=song[i].getMinuti();
        }
        return vkupno;
    }
    void dodadiPesna(Pesna &p){
        if(broj<10 && (vremetraenjePesni()+p.getMinuti()<=vreme)){
            song[broj++]=p;
        }
    }
    void pecatiPesniPoTip(tip t){
        for(int i=0;i<broj;i++){
            if(song[i].getType()==t){
                song[i].pecati();
            }
        }
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}
