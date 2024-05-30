#include <cstdio>
#include <iostream>
#include <climits>
#include <iomanip>
using namespace std;

struct Pacient {
    char ime[100];
    int zdrastveno;
    int pregledi;
};

struct MatichenDoktor{
    char ime[100];
    int br_pac;
    Pacient niza[100];
    float cena;
};

void najuspesen_doktor(MatichenDoktor *md,int n){
    float makscena = INT_MIN;
    int maksposeti = INT_MIN;
    int index = 0;
    for (int i = 0; i < n; ++i) {
        float total = 0;
        int totalvisit = 0;
        for(int j = 0; j < md[i].br_pac; ++j) {
            if (md[i].niza[j].zdrastveno == 0) {
                total += md[i].cena*md[i].niza[j].pregledi;
            }
            totalvisit += md[i].niza[j].pregledi;
        }
        if (makscena < total || (total == makscena && totalvisit > maksposeti)) {
            makscena = total;
            maksposeti = totalvisit;
            index = i;
        }
    }
    cout << md[index].ime << " " << fixed<<setprecision(2)<<makscena << " " << maksposeti;
}

int main()
{
    int n;
    MatichenDoktor md[100];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", md[i].ime);
        scanf("%d", &md[i].br_pac);
        scanf("%f", &md[i].cena);

        for (int j = 0; j < md[i].br_pac; ++j) {
            scanf("%s", &md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}
