#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;
struct Vozenje{
    char name[100];
    int vremetraenje;
    float cena;
    int daliPopust;
};
struct ZabavenPark{
    char ime[100];
    char lokacija[100];
    Vozenje adrenalinski[100];
    int n;
};
void print(ZabavenPark *niza,int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s\n", niza[i].ime, niza[i].lokacija);

        for (int j = 0; j < niza[i].n; j++) {
            printf("%s %d %.2f\n", niza[i].adrenalinski[j].name, niza[i].adrenalinski[j].vremetraenje,
                   niza[i].adrenalinski[j].cena);
        }

    }
}
    void najdobar_park(ZabavenPark *niza,int n){
        int maxi=0,max=0,maxvremetraenje=0;
        for(int i=0;i<n;i++){
            int brojach=0;
            int vreme=0;
            for(int j=0;j<niza[i].n;j++)
            {
                if(niza[i].adrenalinski[j].daliPopust==1)
                {
                    brojach++;
                }
                vreme+=niza[i].adrenalinski[j].vremetraenje;

            }
            if(brojach>max || brojach==max &&vreme>maxvremetraenje ){
                max=brojach;

                maxvremetraenje=vreme;
                maxi=i;
            }

    }
        cout<<"Najdobar park: "<<niza[maxi].ime<<" "<<niza[maxi].lokacija;
}
    int main(){
        int n;
        cin>>n;
        ZabavenPark park[100];
        for (int i = 0; i < n; ++i) {
            cin>>park[i].ime>>park[i].lokacija>>park[i].n;
            for(int j=0;j<park[i].n;j++){
                cin>>park[i].adrenalinski[j].name>>park[i].adrenalinski[j].vremetraenje>>park[i].adrenalinski[j].cena>>park[i].adrenalinski[j].daliPopust;
            }

        }
        print(park,n);
        najdobar_park(park,n);
        return 0;
    }
