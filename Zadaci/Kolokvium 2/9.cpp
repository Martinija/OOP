#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;
class Exception{
public:
    void print(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};
class Trud{
private:
    char tip;
    int godina;
public:
    Trud(){
        tip=0;
        godina=0;
    }
    Trud(char tip,int godina){
        this->tip=tip;
        this->godina=godina;
    }
    friend istream& operator>>(istream& in, Trud& t) {
        in >> t.tip >> t.godina;
        return in;
    }

    char getTip() const {
        return tip;
    }

    int getGodina() const {
        return godina;
    }
};

class Student{
protected:
    char ime[50];
    int indeks;
    int godina;
    int *predmeti;
    int n;
private:
    void copy(const Student&other){
        strcpy(this->ime,other.ime);
        indeks=other.indeks;
        godina=other.godina;
        predmeti=new int[other.n];
        for (int i = 0; i < other.n; ++i) {
            predmeti[i]=other.predmeti[i];
        }
        n=other.n;
    }
public:
    Student(char* ime, int index, int inYear, int* grades, int n) {
        strcpy(this->ime, ime);
        this->indeks = index;
        this->godina = inYear;
        this->predmeti = new int[n];
        for (int i = 0; i < n; i++) {
            this->predmeti[i] = grades[i];
        }
        this->n = n;
    }
    Student(const Student&other){
        copy(other);
    }
    Student &operator=(const Student &other){
        if(this!=&other){
            delete []predmeti;
            copy(other);
        }
        return *this;
    }
     virtual double rang(){
        double s=0;
        for (int i = 0; i < n; ++i) {
            {
                s += predmeti[i];
            }

        }
        return s/n;
    }
    friend ostream &operator<<(ostream &o,Student&s){
        o<<s.indeks<<" "<<s.ime<<" "<<s.godina<<" "<<s.rang()<<endl;
        return o;
    }

    const char *getIme() const {
        return ime;
    }

    int getIndeks() const {
        return indeks;
    }

    int getGodina() const {
        return godina;
    }

    int *getPredmeti() const {
        return predmeti;
    }

    int getN() const {
        return n;
    }
};

class PhDStudent:public Student{
private:
    Trud *trudovi;
    int tn;
    static int c;
    static int j;
public:
    PhDStudent(char *ime, int index, int inYear, int* grades, int n,Trud *trudovi,int tn):Student(ime,index,inYear,grades,n){
        this->trudovi = new Trud[tn];
        for(int i = 0; i < tn; i++) {
            try {
                trudovi[i].getGodina() < inYear ? throw Exception() : this->trudovi[i] = trudovi[i];
            } catch(Exception& e) {
                e.print();
            }
        }
        this->tn = tn;
    }
    PhDStudent(const PhDStudent&other): Student(other){
        this->trudovi=new Trud[tn];
        for (int i = 0; i < other.tn; ++i) {
            this-> trudovi[i]=other.trudovi[i];
        }
        this->tn=other.tn;
    }
    PhDStudent &operator=(const PhDStudent&other){
        if(this!=&other){
            Student::operator=(other);
            delete []trudovi;
            this->trudovi=new Trud[tn];
            for (int i = 0; i < other.tn; ++i) {
                this-> trudovi[i]=other.trudovi[i];
            }
            this->tn=other.tn;


        }
        return *this;
    }
    PhDStudent &operator+=(Trud &t){
        if(t.getGodina()<godina){
            throw Exception();
        }
        Trud* tmp = new Trud[tn + 1];
        for(int i = 0; i < tn; i++) {
            tmp[i] = trudovi[i];
        }
        tmp[tn++] = t;
        delete []trudovi;
        trudovi=tmp;
        return *this;

    }
    ~PhDStudent(){
        delete []trudovi;
    }
    double rang() {
        double curr = Student::rang();
        for (int i = 0; i < tn; i++) {
            if (tolower(trudovi[i].getTip()) == 'c') {
                curr += c;
            } else if (tolower(trudovi[i].getTip()) == 'j') {
                curr += j;
            }
        }
        return curr;
    }
    static void setC(int _c) {
        c = _c;
    }

    static void setJ(int _j) {
        j = _j;
    }
};
int PhDStudent::c = 1;
int PhDStudent::j = 3;
int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool found=false;
        try {
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndeks() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                    found = true;
                }
            }
        } catch(Exception& e) {
            e.print();
        }

        if(!found) cout << "Ne postoi PhD student so indeks " << indeks << "\n";

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        try{
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndeks() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                }
            }
        }
        catch(Exception& e) {
        e.print();
    }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try{
        for(int i = 0; i < m; i++) {
            if(niza[i]->getIndeks() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                *dynamic_cast<PhDStudent*>(niza[i]) += t;
            }
        }
    } catch(Exception& e) {
        e.print();
    }

    // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}
