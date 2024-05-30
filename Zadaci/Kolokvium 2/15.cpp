#include<iostream>
#include<string.h>
#include "cctype"
using namespace std;
class BadInputException{
public:
     void message(){
        cout<<"Greshna opisna ocenka"<<endl;
    }
};
class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
private:
   void copy_kurs(const StudentKurs &other){
       strcpy(this->ime,other.ime);
       this->ocenka=other.ocenka;
       this->daliUsno=other.daliUsno;
   }
public:
    static int MAX;
    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
   StudentKurs(const StudentKurs &other){
       copy_kurs(other);
    }
    //дополни ја класата
    static void setMAX(int newMax){
        MAX=newMax;
    }
    friend ostream &operator<<(ostream &o,StudentKurs &s){
        o<<s.ime<<" --- "<<s.getOcenka()<<"\n";
        return o;
    }
    char *getIme(){
        return ime;
    }
    virtual int getOcenka(){
        return ocenka;
    }
    bool getDaliUsno(){
        return daliUsno;
    }
};
int StudentKurs::MAX=10;

//вметни го кодот за StudentKursUsno
class StudentKursUsno:public StudentKurs{
private:
    char *niza;
public:
    StudentKursUsno(char* ime,int finalenIspit):StudentKurs(ime,finalenIspit){
            this->niza=new char [10];
            strcpy(this->niza,"opisna");
            this->daliUsno=true;
    }
    StudentKursUsno(const StudentKursUsno &other): StudentKurs(other){
        this->niza=new char[strlen(other.niza)+1];
        strcpy(this->niza,other.niza);
        this->daliUsno=true;
   }
    ~StudentKursUsno(){
        delete [] niza;
    }
   int getOcenka() {
       int kursOcena= StudentKurs::getOcenka(), sum = 0;
       if (strcmp(niza, "odlicen")==0) {
           sum = 2;
       } else if (strcmp(niza, "dobro")==0) {
           sum = 1;
       } else if (strcmp(niza, "losho")==0) {
           sum = -1;
       } else {
           return kursOcena;
       }
       if(kursOcena+sum<=MAX) {
           return kursOcena + sum;
       }
       else{
           return MAX;
       }
   }
   friend ostream &operator<<(ostream&o,StudentKursUsno&s){
       o<<s.ime<<" --- "<<s.getOcenka()<<"\n";
       return o;
   }
   StudentKursUsno &operator+=(char *c){
       for (int i = 0; i < strlen(c); ++i) {
           if(!isalpha(c[i])){
               throw BadInputException();
           }
       }
       delete []niza;
       this->niza=new char [strlen(niza)+1];
       strcpy(this->niza,c);
       return *this;
   }
};

class KursFakultet {
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    const static int MINOCENKA;
public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            } else this->studenti[i] = new StudentKurs(*studenti[i]);
        }
        this->broj = broj;
    }

    ~KursFakultet() {
        for (int i = 0; i < broj; i++) delete studenti[i];
    }

    void pecatiStudenti() {
        cout << "Kursot " << naziv << " go polozile:" << "\n";
        for (int i = 0; i < broj; ++i) {
            if (studenti[i]->getOcenka() >= MINOCENKA) {
                cout << *studenti[i];
            }
        }
    }

    void postaviOpisnaOcenka(char *ime, char *opisnaOcenka) {
        for (int i = 0; i < broj; ++i) {
            if (studenti[i]->getDaliUsno() && (!strcmp(ime, studenti[i]->getIme()))) {
                StudentKursUsno *usno = dynamic_cast<StudentKursUsno *>(studenti[i]);
                if (usno) {
                    try {
                        *usno += opisnaOcenka;
                    }
                    catch (BadInputException &e) {
                        e.message();
                        char nova_opisna[10];
                        int counter = 0;
                        for (int j = 0; j < strlen(opisnaOcenka); ++j) {
                            if (isdigit(opisnaOcenka[j])) {
                                continue;
                            }
                            nova_opisna[counter++] = opisnaOcenka[j];
                        }
                        nova_opisna[counter++] = '\0';
                        *usno += nova_opisna;
                    }
                    // *dynamic_cast<StudentKursUsno*>(studenti[i])+=opisnaOcenka;
                }
            }
        }
    }
        //дополни ја класата
};
const int KursFakultet::MINOCENKA = 6;

    int main() {

        StudentKurs **niza;
        int n, m, ocenka;
        char ime[30], opisna[10];
        bool daliUsno;
        cin >> n;
        niza = new StudentKurs *[n];
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> ocenka;
            cin >> daliUsno;
            if (!daliUsno)
                niza[i] = new StudentKurs(ime, ocenka);
            else
                niza[i] = new StudentKursUsno(ime, ocenka);
        }

        KursFakultet programiranje("OOP", niza, n);
        for (int i = 0; i < n; i++) delete niza[i];
        delete[] niza;
        cin >> m;

        for (int i = 0; i < m; i++) {
            cin >> ime >> opisna;
            try {
                programiranje.postaviOpisnaOcenka(ime, opisna);
            }
            catch (BadInputException e) {
                e.message();
                char nova_opisna[10];
                int counter = 0;
                for (int j = 0; j < strlen(opisna); ++j) {
                    if (isdigit(opisna[j])) {
                        continue;
                    }
                    nova_opisna[counter++] = opisna[j];
                }
                nova_opisna[counter++] = '\0';
                programiranje.postaviOpisnaOcenka(ime, nova_opisna);
            }
        }


        StudentKurs::setMAX(9);

        programiranje.pecatiStudenti();

    }
