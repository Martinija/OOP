//Partially correct
#include<iostream>
#include <cstring>
using namespace std;

struct Igrac{
    char korisnickoIme[50];
    int nivo;
    int poeni;
};
struct KompjuterskaIgra{
    char ime[50];
    Igrac lista[100];
    int n;
};
void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int najdobarIgrach=0;
    for(int i=0;i<n;i++){
        if(lista[i].n>lista[najdobarIgrach].n){
            najdobarIgrach=i;
        }
    }
    KompjuterskaIgra popularna=lista[najdobarIgrach];
    int indeks=0;
    for (int i = 1; i <n ; ++i) {
        if(popularna.lista[i].poeni>popularna.lista[indeks].poeni){
            indeks=i;
        }
        else if(popularna.lista[i].poeni==popularna.lista[indeks].poeni){
            if(popularna.lista[i].nivo>popularna.lista[indeks].nivo){
                indeks=i;
            }
        }
        
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<popularna.lista[indeks].korisnickoIme<<" koj ja igra igrata "<<popularna.ime<<endl;
}

int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
