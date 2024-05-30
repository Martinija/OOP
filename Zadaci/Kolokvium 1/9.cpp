#include <iostream>
#include <cstring>
#include <cctype>
#include <climits>
#include <iomanip>
using namespace std;
struct Laptop{
    char firma[100];
    float golemina;
    int touch;
    int cena;
};
struct ItStore{
    char ime[100];
    char lokacija[100];
    Laptop topi[100];
    int n;
};
void print(ItStore *store,int n){
    for(int i=0;i<n;i++){
        cout<<store[i].ime<<" "<<store[i].lokacija<<endl;
        for(int j=0;j<store[i].n;j++){
            cout<<store[i].topi[j].firma<<" "<<store[i].topi[j].golemina<<" "<<store[i].topi[j].cena<<endl;
        }
    }
}

void najeftina_ponuda(ItStore *store,int n){
    int maxi=0,min=INT_MAX;
    for(int i=0;i<n;i++){
        for (int j = 0; j < store[i].n; ++j) {
          if( store[i].topi[j].cena < min && store[i].topi[j].touch==1){
              min=store[i].topi[j].cena;
              maxi=i;
          }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata: "<<endl;
    cout<<store[maxi].ime<<" "<<store[maxi].lokacija<<endl;
    cout<<"Najniskata cena iznesuva: "<<min<<endl;
}
int main() {
    ItStore s[100];
    int n;
   cin>>n;//broj na IT prodavnici
    for(int i=0;i<n;i++){
        cin>>s[i].ime>>s[i].lokacija>>s[i].n;
        for (int j = 0; j < s[i].n; ++j) {
            cin>>s[i].topi[j].firma>>s[i].topi[j].golemina>>s[i].topi[j].touch>>s[i].topi[j].cena;
        }
    }

    //pecatenje na site prodavnici
    print(s,n);

    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}
