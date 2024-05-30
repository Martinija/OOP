#include <iostream>
#include <cstring>
using namespace std;
enum Tip{
    LINUX,UNIX,WINDOWS
};
char tip[100][100]={"LINUX","UNIX","WINDOWS"};
class OperativenSistem{
private:
    char *ime;
    Tip type;
    float verzija;
    float golemina;

    void copy(const OperativenSistem &other){
        this->ime=new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->type=other.type;
        this->verzija=other.verzija;
        this->golemina=other.golemina;
    }
public:
    OperativenSistem() {
        this->ime = new char[4];
        strcpy(this->ime, "os");
        this->verzija = 0.1;
        this->type = LINUX;
        this->golemina = 1.0;
    }
    OperativenSistem(char *ime,float verzija, Tip type, float golemina){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->type=type;
        this->verzija=verzija;
        this->golemina=golemina;
    }
    OperativenSistem(const OperativenSistem &other){
        copy(other);
    }
    ~OperativenSistem(){
        delete[]ime;
    }
    OperativenSistem& operator=(const OperativenSistem &other){
        if(this==&other){
            return *this;
        }
        delete[]ime;
        copy(other);
        return *this;
    }
    void pecati(){
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<type<<" Golemina:"<<golemina<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os){
        if((strcmp(ime,os.ime)==0)&&(type=os.type)&&(golemina==os.golemina)&&(verzija==os.verzija)){
            return true;
        }
        return false;
    }
    int sporediVerzija(const OperativenSistem &os){
        if(verzija==os.verzija){
            return 0;
        }
        else if(verzija<os.verzija){
            return -1;
        }
        else{
            return 1;
        }
    }
    bool istaFamilija(const OperativenSistem &sporedba){
        if(strcmp(ime,sporedba.ime)==0 && type==sporedba.type){
            return true;
        }
        return false;
    }
};
class Repozitorium{
private:
    char name[20];
    OperativenSistem *os;
    int n;
    void copy(const Repozitorium&other){
        strcpy(this->name,other.name);
        this->os=new OperativenSistem[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->os[i]=other.os[i];
        }
        this->n=other.n;
    }

public:
    Repozitorium(){
        strcpy(this->name, "repo");
        os = nullptr;
        n = 0;}
    Repozitorium( const char *ime){
        strcpy(this->name,ime);
       this-> os= nullptr;
        n=0;
    }
    Repozitorium(const Repozitorium &other){
        copy(other);
    }
    ~Repozitorium(){
        delete[] os;
    }
    Repozitorium& operator=(const Repozitorium&other){
        if(this==&other){
            return*this;
        }
        delete[]os;
        copy(other);
        return *this;
    }
    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<name<<endl;
        for (int i = 0; i < n; ++i)  {
            this->os[i].pecati();
        }
    }/*
   void izbrishi(const OperativenSistem &operativenSistem)
   {
        int index=-1;
        for (int i = 0; i < n; ++i) {
            if(os[i].ednakviSe(operativenSistem)){
                index=i;
               break;
            }
        }
        if(index==-1){
            return;
        }
       for (int i = 0; i < n-1; ++i) {
           os[i]=os[i+1];
       }
       n--;
    }*/

    void izbrishi(const OperativenSistem &operativenSistem){
           int br=0;
        for (int i = 0; i < n; ++i) {
            if(os[i].ednakviSe(operativenSistem)){
                br++;
            }
            else{
                os[i-br]=os[i];
            }
        }
        n-=br;
    }
    void dodadi(const OperativenSistem &nov){

       for (int i = 0; i < n; ++i) {
            if(os[i].istaFamilija(nov) && os[i].sporediVerzija(nov)==-1){
               {os[i]=nov;
                   return;
               }
            }
       }
        OperativenSistem *tmp=new OperativenSistem[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=os[i];
        }
        tmp[n++]=nov;
        delete[]os;
        this->os=tmp;
       /* delete[]os;
      this->os=new OperativenSistem[n];
        for (int i = 0; i < n; ++i) {
            this->os[i]=tmp[i];
        }
        delete[]tmp;
*/}
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
