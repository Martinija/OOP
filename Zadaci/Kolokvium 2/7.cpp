#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException{
public:
    void message(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};
class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;

    void copy(const Karticka&other){
        strcpy(smetka,other.smetka);
        pin=other.pin;
        povekjePin=other.povekjePin;
    }
public:
    Karticka(){
        strcpy(this->smetka," ");
        this->pin=0;
        this->povekjePin=false;
    }
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    Karticka(const Karticka&other){
        copy(other);
    }
    friend ostream& operator<<(ostream& out, Karticka& k) {
        out << k.smetka << ": " << k.tezinaProbivanje() << "\n";
        return out;
    }
    // дополниете ја класата
    virtual int tezinaProbivanje(){
        int sum=0,c=pin;
        while (c){
            sum++;
            c/=10;
        }
        return sum;
    }
    bool getDopolnitelenPin() {
        return povekjePin;
    }

     char *getSmetka()  {
        return smetka;
    }
};

//вметнете го кодот за SpecijalnaKarticka
class SpecijalnaKarticka:public Karticka{
private:
    int *dopolnitelni;
    int brojPin;
public:
    SpecijalnaKarticka(char* smetka,int pin): Karticka(smetka,pin){
        povekjePin=true;
        dopolnitelni= nullptr;
        brojPin=0;
    }
    SpecijalnaKarticka(const SpecijalnaKarticka&other):Karticka(other){
        strcpy(this->smetka, other.smetka);
        this->pin = other.pin;
        this->povekjePin = other.povekjePin;
        this->dopolnitelni = new int[other.brojPin];
        for(int i = 0; i < other.brojPin; i++) {
            this->dopolnitelni[i] = other.dopolnitelni[i];
        }
        this->brojPin = other.brojPin;
    }
    SpecijalnaKarticka &operator=(const SpecijalnaKarticka&other){
        if(this!=&other){
            delete []dopolnitelni;
            strcpy(this->smetka, other.smetka);
            this->pin = other.pin;
            this->povekjePin = other.povekjePin;
            this->dopolnitelni = new int[other.brojPin];
            for(int i = 0; i < other.brojPin; i++) {
                this->dopolnitelni[i] = other.dopolnitelni[i];
            }
            this->brojPin = other.brojPin;
        }
        return *this;
    }
    int tezinaProbivanje(){
        return Karticka::tezinaProbivanje()+brojPin;
    }
    ~SpecijalnaKarticka(){
        delete []dopolnitelni;
    }
    SpecijalnaKarticka &operator+=(int pin){
        if(brojPin>=4){
            throw OutOfBoundException();
        }
        int *tmp=new int[brojPin];
        for (int i = 0; i < brojPin; ++i) {
            tmp[i]=dopolnitelni[i];
        }
        tmp[brojPin++]=pin;
        delete []dopolnitelni;
        dopolnitelni=tmp;
        return *this;
    }

};


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }
    static void setLIMIT(int _limit) {
        LIMIT = _limit;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for (int i = 0; i < broj; ++i) {
            if(karticki[i]->tezinaProbivanje()<=LIMIT){
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin){
        for (int i = 0; i < broj; ++i) {
            if(karticki[i]->getDopolnitelenPin() && !strcmp(karticki[i]->getSmetka(),smetka)){
                *dynamic_cast<SpecijalnaKarticka*>(karticki[i])+=novPin;
            }
        }
    }

    //да се дополни класата

};
int Banka::LIMIT=7;


int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;
        try {
            komercijalna.dodadiDopolnitelenPin(smetka, pin);

        }
        catch(OutOfBoundException e){
            e.message();
        }

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
