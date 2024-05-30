#include <iostream>
#include <cstring>
using namespace std;

class Zichara{
private:
    char *mesto;
    float cena;
public:
    Zichara(){
        this->mesto = new char[6];
        strcpy(mesto,"mesto");
        cena=0;
    }
    Zichara(char *mesto,float cena){
        this->mesto=new char[strlen(mesto)+1];
        strcpy(this->mesto,mesto);
        this->cena=cena;
    }
    Zichara(const Zichara&other){
        this->mesto=new char[strlen(other.mesto)+1];
        strcpy(this->mesto,other.mesto);
        this->cena=other.cena;

    }
    Zichara &operator=(const Zichara&other){
        if(this==&other){
            return *this;
        }
        delete[]mesto;
        this->mesto=new char[strlen(other.mesto)+1];
        strcpy(this->mesto,other.mesto);
        this->cena=other.cena;
        return *this;

    }
    float getCena() const {
        return cena;
    }

    ~Zichara (){
        delete []mesto;

    }

};
class PlaninarskiDom{
private:
     char ime[15];
     int ceni[2];
     char klasa;
     bool imaZhichara;
     Zichara *zhicara;

public:
     PlaninarskiDom(){
        this->ceni[0] = this->ceni[1] = 0;
        strcpy(this->ime, "dom");
        this->klasa = 'F';
        this->imaZhichara = false;
        this->zhicara = nullptr;
     }
     PlaninarskiDom(char *ime,const int *ceni,char klasa){
         strcpy(this->ime,ime);
         for (int i = 0; i < 2; ++i) {
             this->ceni[i]=ceni[i];
         }
         this->klasa=klasa;
         imaZhichara= false;
         zhicara= nullptr;
     }
     PlaninarskiDom(const PlaninarskiDom&other){
         strcpy(this->ime,other.ime);
         this->ceni[0] = other.ceni[0];
         this->ceni[1] = other.ceni[1];
         this->klasa = other.klasa;
         this->imaZhichara = other.imaZhichara;
         this->zhicara = other.zhicara;
     }

     PlaninarskiDom&operator=(const PlaninarskiDom&other){
         if(this==&other){
             return *this;
         }
         strcpy(this->ime,other.ime);
         this->ceni[0] = other.ceni[0];
         this->ceni[1] = other.ceni[1];
         this->klasa = other.klasa;
         this->imaZhichara = other.imaZhichara;
         this->zhicara = other.zhicara;
         return *this;
     }
     PlaninarskiDom &operator--(){
         if(klasa<'F'){
             klasa++;
         }
         return *this;
     }
     bool operator<=(char c)const{
         return klasa>=c;
     }
     friend ostream&operator<<(ostream&o,const PlaninarskiDom&p){
         o<<p.ime<<" klasa:"<<p.klasa;
         if(p.imaZhichara){
             o<<" so Zichara"<<endl;
         }
         else{
             o<<endl;
         }
         return o;
     }
    void setZichara(Zichara zichara) {
        this->zhicara = &zichara;
        imaZhichara = true;
    }
    void presmetajDnevenPrestoj(int d,int m,int &c){
         c=0;
         if(zhicara){
             c+=zhicara->getCena();
         }
         if(m<1||m>12 ||d<1||d>31){
             throw -1;
         }
        if( (m >= 4 && m <= 8) || (m == 9 && m == 1)){
            c += ceni[0];
        }
        else{
        c += ceni[1];
        }

     }
};

int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
   if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}
