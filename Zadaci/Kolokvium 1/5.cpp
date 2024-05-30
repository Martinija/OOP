#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
class Gitara{
private:
    char seriskiBroj[25];
    double cena;
    int godina;
    char tip[40];

    void copy(const Gitara&other){
        strcpy(this->seriskiBroj,other.seriskiBroj);
        this->cena=other.cena;
        this->godina=other.godina;
        strcpy(this->tip,other.tip);
    }
public:
    Gitara(char *tip="",char * seriski ="",int godinaProizvodstvo=0,double nabavna =0)
    {
        strcpy(this->tip,tip);
        strcpy(this->seriskiBroj,seriski);
        this->godina = godinaProizvodstvo;
        this->cena = nabavna;
    }

    Gitara(const Gitara&other){
        copy(other);
    }
    ~Gitara(){}
    Gitara& operator=(const Gitara& other) {
        if(this == &other) {
            return *this;
        }
        copy(other);
        return *this;
    }
    bool daliIsti( Gitara &p){
        if(strcmp(this->seriskiBroj,p.seriskiBroj)==0){
            return true;
        }
        else
            return false;
    }
    void pecati(){
        cout<<seriskiBroj<<" "<<tip<<" "<<cena<<endl;
    }

    double getNabavna()  {
        return cena;
    }

    const char *getSeriski() const {
        return seriskiBroj;
    }

    int getGodina() const {
        return godina;
    }

    const char *getTip() const {
        return tip;
    }
};
class Magacin{
private:
    char ime[30];
    char lokacija[60];
    Gitara *gitari;
    int n;
    int godina;
    void copy( const Magacin&other){
        strcpy(this->ime,other.ime);
        strcpy(this->lokacija,other.lokacija);
        this->n=other.n;
        this->godina=other.godina;
        gitari=new Gitara[n];
        for (int i = 0; i < n; ++i) {
            this->gitari[i]=other.gitari[i];
        }
    }
public:
    /*
    Magacin(){
        strcpy(this->ime," ");
        strcpy(this->lokacija," ");
        this->n=0;
        this->godina=0;
        gitari= nullptr;
    }
    Magacin(char *ime, char *lokacija, int godina){
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->n=0;
        this->godina=godina;
       this->gitari= nullptr;
    }
    */
    Magacin( char *ime=" ", char*lokacija=" ",int godina=0){
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->n=0;
        this->godina=godina;
        this->gitari= nullptr;
    }
    Magacin(const Magacin&other){
        copy(other);
    }
    Magacin& operator=(const Magacin &other){
        if(this==&other){
            return *this;
        }
        delete []gitari;
        copy(other);
        return *this;
    }
    ~Magacin(){
        delete []gitari;
    }
     void dodadi(Gitara d){
        Gitara *tmp=new Gitara[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=gitari[i];
        }
        tmp[n]=d;
        delete []gitari;
        gitari=tmp;
        n++;
    }
    double vrednost(){
        double vr=0;
        for (int i = 0; i < n; ++i) {
            vr+=gitari[i].getNabavna();
        }
        return vr;
    }
    /*void prodadi(Gitara p){
        int element=0, brojach=0;
        for (int i = 0; i < n; ++i) {
            element+=!gitari[i].daliIsti(p);
        }
        if(!element){
            return;
        }
        Gitara* tmp=new Gitara[element];
        for (int i = 0; i < n; ++i) {
            if(gitari[i].daliIsti(p)){
                continue;
            }
            tmp[brojach++]=gitari[i];
        }
        delete []gitari;
        gitari=new Gitara[brojach];
        for(int i=0;i<brojach;i++){
            gitari[i]=tmp[i];
        }
        n=brojach;
        delete[] tmp;
    }
     */

    void prodadi(Gitara & g)
    {
        int newBr = 0;
        for(int i=0;i<n;i++)
        {
            if(gitari[i].daliIsti(g)==false)
            {
                newBr++;
            }
        }
        Gitara * tmp = new Gitara[newBr];
        int j=0;
        for(int i=0;i<n;i++)
        {
            if(gitari[i].daliIsti(g)==false)
            {
                tmp[j] = gitari[i];
                j++;
            }
        }
        delete [] gitari;
        gitari = tmp;
        n = newBr;
    }
    void pecati(bool daliNovi){
        cout<<ime<<" "<<lokacija<<endl;
        for (int i = 0; i < n; ++i) {
            if(daliNovi && gitari[i].getGodina()>godina)
            {
                gitari[i].pecati();
            }
            else if(!daliNovi){
                gitari[i].pecati();
            }
        }
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
