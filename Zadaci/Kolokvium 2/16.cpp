#include <iostream>
#include <cstring>
using namespace std;
class Transport{
protected:
    char destinacija[100];
    double cena;
    double rastojanie;

public:
    Transport(char * destinicija=" ", double cena=0, double rastojanie=0): cena(cena), rastojanie(rastojanie) {
        strcpy(this->destinacija,destinicija);
    }
    ~Transport(){}

    virtual double cenaTransport()=0;

    bool operator<(const Transport &other)const{
        return rastojanie<other.rastojanie;
    }

    double getRastojanie() const {
        return rastojanie;
    }
    friend ostream&operator<<(ostream &o,Transport&t){
        o<<t.destinacija<<" "<<t.rastojanie<<" "<<t.cenaTransport();
        return o;
    }
};

class AvtomobilTransport:public Transport{
private:
    bool plshofer;

public:
    AvtomobilTransport(  char * destinicija, double cena, double rastojanie,bool plshofer=false): Transport(destinicija,cena,rastojanie){
        this->plshofer=plshofer;
    }

    double cenaTransport(){
        if(plshofer){
            return cena+cena*0.2;
        }else{
            return cena;
        }
    }

};
class KombeTransport:public Transport{
private:
    double brLugje;
public:
    KombeTransport( char * destinicija, double cena, double rastojanie,double brLugje=0):Transport(destinicija,cena,rastojanie){
        this->brLugje=brLugje;
    }
    double getBrLugje() const {
        return brLugje;
    }

    void setBrLugje(double brLugje) {
        KombeTransport::brLugje = brLugje;
    }
    double cenaTransport(){
        return cena-brLugje*200;
    }
};
void pecatiPoloshiPonudi(Transport **tr,int n, Transport &t){
    for(int i=0;i<n;i++){
        for (int j = 0; j < n-i-1; ++j) {
            if(tr[j]->getRastojanie()>tr[j+1]->getRastojanie()){
                swap(tr[j],tr[j+1]);
            }
        }
    }

    for(int i=0;i<n;i++){
        if(tr[i]->cenaTransport()>t.cenaTransport()){
            cout<<*tr[i]<<endl;
        }
    }

}
int main(){

    char destinacija[100];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];
    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }
    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
