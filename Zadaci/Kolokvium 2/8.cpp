#include<iostream>
#include<string.h>
using namespace std;

class Koncert{
private:
    char naziv[20];
    char lokacija[20];
   static float popust;
    float price;

    void copy(const Koncert &other){
        strcpy(this->naziv,other.naziv);
        strcpy(this->lokacija,other.lokacija);
        this->price=other.price;
    }
public:
    Koncert(char *naziv=" ",char *lokacija=" ",float price=0){
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->price=price;
    }
    Koncert(const Koncert&other){
        copy(other);
    }
    virtual float cena(){
        return price*(1.0-popust);
    }

     char *getNaziv()  {
        return naziv;
    }

     char *getLokacija()  {
        return lokacija;
    }
    float getPrice(){
        return price;
    }
    float getPopust() {
        return popust;
    }
    float getSezonskiPopust(){
        return popust;
    }
    void setSezonskiPopust(float p){
        popust=p;
    }
};
float Koncert::popust=0.2;

class ElektronskiKoncert:public Koncert{
private:
    char *imeDj;
    float vreme;
    bool dnevna;
public:
    ElektronskiKoncert(char *naziv=" ",char *lokacija=" ",float price=0,char *imeDj=" ",float vreme=0,bool dnevna= true): Koncert(naziv,lokacija,price){
        this->imeDj=new char [strlen(imeDj)+1];
        strcpy(this->imeDj,imeDj);
        this->vreme=vreme;
        this->dnevna=dnevna;
    }
    ElektronskiKoncert(const ElektronskiKoncert&other): Koncert(other){
        this->imeDj=new char [strlen(other.imeDj)+1];
        strcpy(this->imeDj,other.imeDj);
        this->vreme=other.vreme;
        this->dnevna=other.dnevna;
    }
    ElektronskiKoncert &operator=(const ElektronskiKoncert&other){
        if(this!=&other){
            delete []imeDj;
            this->imeDj=new char [strlen(other.imeDj)+1];
            strcpy(this->imeDj,other.imeDj);
            this->vreme=other.vreme;
            this->dnevna=other.dnevna;
        }
        return *this;
    }
    ~ElektronskiKoncert(){
        delete []imeDj;
    }
    float cena(){
        float s=0;
        if(vreme>7){
            s+=360;
        }
        else if(vreme>5){
           s+=150;
        }
        if(dnevna){
            s-=50;
        }
        else{
            s+=100;
        }
        return Koncert::cena()+s;
    }

};
void najskapKoncert(Koncert ** koncerti, int n){
    double maks=0;
    int index=0;
    int brojach=0;
    for (int i = 0; i < n; ++i) {
        if(koncerti[i]->cena()>maks){
            index=i;
            maks=koncerti[i]->cena();
        }
        if(dynamic_cast<ElektronskiKoncert*>(koncerti[i])){
            brojach++;
        }
    }
    cout<<"Najskap koncert: "<<koncerti[index]->getNaziv()<<" "<<koncerti[index]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<brojach<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    for (int i = 0; i < n; ++i) {
        if(elektronski) {
            ElektronskiKoncert *tmp = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if (tmp) {
                if(!strcmp(tmp->getNaziv(),naziv)){
                    cout<<tmp[i].getNaziv()<<" "<<tmp[i].cena()<<endl;
                        return true;
                }
            }
        }
        else{
            if(!strcmp(koncerti[i]->getNaziv(),naziv)){
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }

    }
    return false;
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
