#include <iostream>
#include <cstring>
using namespace std;
class FudbalskaEkipa {
protected:
    char imeTrener[100];
    int golovi[10];
public:
    FudbalskaEkipa(char *imeTrener,int *golovi){
        strcpy(this->imeTrener,imeTrener);
        for(int i = 0; i < 10; i++) {
            this->golovi[i] = golovi[i];
        }
    }
     virtual int uspeh()=0;
    FudbalskaEkipa& operator+=(int lastMatchGoals) {
        for(int i = 0; i < 9; i++) {
            this->golovi[i] = this->golovi[i + 1];
        }
        this->golovi[9] = lastMatchGoals;
        return *this;
    }

    bool operator>( FudbalskaEkipa& other) {
        return uspeh() > other.uspeh();
    }
     virtual void print()=0;
    friend ostream&operator<<(ostream&o,FudbalskaEkipa&fe){
        fe.print();
        o<<fe.imeTrener<<endl;
        o<<fe.uspeh()<<endl;
        return o;
    }

};

class Klub:public FudbalskaEkipa{
private:
    char ime[100];
    int tituli;
public:
    Klub(char *imeTrener=" ",int *golovi= nullptr,char *ime=" ",int tituli=0): FudbalskaEkipa(imeTrener,golovi){
        strcpy(this->ime,ime);
        this->tituli=tituli;
    }
    ~Klub(){}
    int uspeh(){
        int zbirNaGolovi=0;
        int dostignuvanja;
        for (int i = 0; i < 10; ++i) {
            zbirNaGolovi+=golovi[i];
        }
        dostignuvanja=zbirNaGolovi*3+tituli*1000;
        return dostignuvanja;
    }
    void print(){
        cout<<ime<<endl;
    }
};
class Reprezentacija:public FudbalskaEkipa{
private:
    char drzhava[100];
    int vknatrpevari;
public:
    Reprezentacija(char *imeTrener=" ",int *golovi= nullptr,char *drzava=" ",int vknatrevari=0): FudbalskaEkipa(imeTrener,golovi){
        strcpy(this->drzhava,drzava);
        this->vknatrpevari=vknatrevari;
    }
    ~Reprezentacija(){}
    int uspeh() {
        int zbirNaGolovi=0;
        int dostignuvanja;
        for (int i = 0; i < 10; ++i) {
            zbirNaGolovi+=golovi[i];
        }
        dostignuvanja=zbirNaGolovi*3+vknatrpevari*50;
        return dostignuvanja;
    }
    void print(){
        cout<<drzhava<<endl;
    }

};
void najdobarTrener(FudbalskaEkipa **fb,int n){
    int index=-1;
    int max=0;
    for (int i = 0; i < n; ++i) {
      if(fb[i]->uspeh()>max){
          max=fb[i]->uspeh();
          index=i;
      }
    }
    cout<<*fb[index];
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
