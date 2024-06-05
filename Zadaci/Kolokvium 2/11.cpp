#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo{
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(char *ime=" ",int godina=0,char *zemja=" "){
        strcpy(this->ime,ime);
        strcpy(this->zemja,zemja);
        this->godina=godina;
    }
    bool operator==(Delo &other){
        return!strcmp( ime,other.ime);
    }

    const char *getIme() const {
        return ime;
    }

    int getGodina() const {
        return godina;
    }

    const char *getZemja() const {
        return zemja;
    }
};

class Pretstava{
protected:
    Delo object;
    int n;
    char data[15];
public:
    Pretstava(Delo object, int n, char *data) {
        this->object = object;
        this->n = n;
        strcpy(this->data,data);
    }
    virtual double cena(){
        int m,n;
        if(object.getGodina()>1900){
            m=50;
        }
        else if(object.getGodina()>1800){
            m=75;
        }
        else{
            m=100;
        }
        if(!strcmp(object.getZemja(),"Italija")){
            n=100;
        }
        else if(!strcmp(object.getZemja(),"Rusija")){
            n=150;
        }
        else{
            n=80;
        }
        return m+n;
    }

     Delo &getDelo()  {
        return object;
    }

    int getN() const {
        return n;
    }

    const char *getData() const {
        return data;
    }
};
class Opera:public Pretstava{
public:
    Opera(Delo object, int n, char *data): Pretstava(object,n,data){ }
    ~Opera(){ }

};

class Balet:public Pretstava{
private:
  static double price;
public:
    Balet(Delo object, int n, char *data): Pretstava(object,n,data){

    }
    double cena(){
        return Pretstava::cena()+price;
    }
    static void setCenaBalet(double newCena){
        price=newCena;
    }
};
double Balet::price=150;
int prihod(Pretstava **niza,int n){
    int cena=0;
    for (int i = 0; i < n; ++i) {
        cena+=niza[i]->cena()*niza[i]->getN();
    }
    return cena;
}
int brojPretstaviNaDelo(Pretstava **niza,int n,Delo d){
    int brojach=0;
    for (int i = 0; i < n; ++i) {
        if(niza[i]->getDelo()==d){
            brojach++;
        }
    }
    return brojach;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
