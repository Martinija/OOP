#include <iostream>
#include <cstring>
using namespace std;
enum tip{
    smartphone,computer
};
char Tip[][8]={"Mobilen","Laptop"};

class InvalidProductionDate{
public:
    void pechati(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

class Device{
private:
    char model[100];
    tip type;
    static double hours;
    int year;

    void copy(const Device &other){
        strcpy(this->model,other.model);
        type=other.type;
        year=other.year;
    }
public:
    Device(){
        strcpy(model," ");
        type=smartphone;
        year=0;

    }
    Device(char *model,tip type, int year){
        strcpy(this->model,model);
        this->type=type;
        this->year=year;
    }
    ~Device(){}
    Device(const Device &other){
        copy(other);
    }
    static void setPocetniCasovi(double newHour){
        hours=newHour;
    }
    double proverka(){
        float s=0;
        if(year>2015){
            s+=2;
        }
        if(type==computer){
            s+=2;
        }
        return s+Device::hours;
    }
    friend ostream &operator<<(ostream &o,Device&d){
        o<<d.model<<endl;
        o<<Tip[d.type]<<" "<<d.proverka()<<endl;
        return o;
    }
    friend class MobileServis;

};
double Device::hours=1;
class MobileServis{
private:
    char address[100];
    Device *niza;
    int n;

    void copy_m(const MobileServis &other){
        strcpy(this->address,other.address);
        this->niza=new Device[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->niza[i]=other.niza[i];
        }
        this->n=other.n;
    }
public:
    MobileServis(){
        strcpy(address," ");
        niza= nullptr;
        n=0;
    }
    MobileServis(char *address){
       strcpy(this->address,address);
       niza= nullptr;
       n=0;
    }
    MobileServis(const MobileServis &other){
        copy_m(other);
    }
    MobileServis &operator=(const MobileServis &other){
        if(this!=&other){
            delete []niza;
            copy_m(other);
        }
        return *this;
    }
    MobileServis&operator+=(Device &d){
        if(d.year>2019 || d.year<2000){
            throw InvalidProductionDate();
        }

       Device *tmp =new Device[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=niza[i];
        }
        tmp[n++]=d;
        delete []niza;
        this->niza=tmp;
        return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<address<<endl;
        for (int i = 0; i < n; ++i) {
            cout<<niza[i];
        }
    }
    ~MobileServis(){
        delete []niza;
    }

};
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &e){
                e.pechati();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &e){
                e.pechati();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &e){
                e.pechati();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &e){
                e.pechati();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &e){
                e.pechati();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

