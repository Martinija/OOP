#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
struct Voz{
    char relacija[50];
    int kilometri;
    int patnici;

};
struct ZeleznickaStanica{
    char grad[20];
    Voz voz[30];
    int brvozovi;
};
void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad){
    int minj;int tempi=0;
    char temp[50],poagja[50];
    for(int i=0;i<n;i++){
        int min=zs[i].voz[0].kilometri;
        minj=0;
        for(int j=0;j<zs[i].brvozovi;j++){
            strcpy(temp,zs[i].voz[j].relacija);
            int k= strlen(strchr(temp,'-'));
            strncpy(poagja,temp, strlen(temp)-k);
            poagja[strlen(temp)-k]='\0';
            if(!strcmp(poagja,grad)){
                if(min>=zs[i].voz[j].kilometri){
                    min=zs[i].voz[j].kilometri;
                    minj=j;
                    tempi=i;
                }
            }
        }

    }
    cout<<"Najkratka relacija: "<<zs[tempi].voz[minj].relacija<<" ("<<zs[tempi].voz[minj].kilometri<<" km)"<<endl;
}
int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin >> zStanica[i].grad;
        cin >> zStanica[i].brvozovi;
        for (int j = 0; j < zStanica[i].brvozovi; j++) {
            cin >> zStanica[i].voz[j].relacija;
            cin >> zStanica[i].voz[j].kilometri;
            cin >> zStanica[i].voz[j].patnici;
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
