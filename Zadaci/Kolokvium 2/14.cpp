#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class SMS{
protected:
    double cena;
    char number[14];
    const static float ddv;
public:
    SMS(char *num,double cena){
        this->cena=cena;
        strcpy(number,num);
    }
    virtual double SMS_cena()=0;
    friend ostream &operator<<(ostream &o,SMS &s){
        o<<"Tel: "<<s.number<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
        return o;
    }
    SMS(){}


};
const float SMS::ddv=0.18;

class RegularSMS:public SMS{
private:
    bool roaming;
    char msg[1000];
    static double percentage;
public:
    RegularSMS(char *num,double cena,char *msg,bool roaming): SMS(num,cena){
        this->roaming=roaming;
        strcpy(this->msg,msg);
    }
    double SMS_cena(){
        double price;
        if(roaming){
            price=percentage/100.0;
        }
        else{
            price=ddv;
        }
        return cena*(1.0+price)*(ceil(strlen(msg)/160.0));
    }
    static void set_rProcent(double newpercentage){
        percentage = newpercentage;
    }
    ~RegularSMS(){}

};
double RegularSMS::percentage=300;


class SpecialSMS:public SMS{
private:
    bool humanitarni;
    static double persent;
public:
    SpecialSMS(char *num,double cena,bool humanitarni): SMS(num,cena){
        this->humanitarni=humanitarni;
    }
    double SMS_cena(){
        if(humanitarni){
            return cena;
        }
        else{
            return cena*(1.0+(persent)/100.0);
        }
    }
    static  void set_sProcent(double newPercent){
        persent=newPercent;
    }
    ~SpecialSMS(){}
};
double SpecialSMS::persent=150;


void vkupno_SMS(SMS** poraka, int n){
    int r=0,s=0;
    float rprice=0,sprice=0;
    for (int i = 0; i < n; ++i) {
//        RegularSMS *reg= dynamic_cast<RegularSMS*>(poraka[i]);
//        if(reg){
//            r++;
//            rprice+=reg->SMS_cena();
//        }else{
//            SpecialSMS *spec=dynamic_cast<SpecialSMS*>(poraka[i]);
//            if(spec){
//                s++;
//                sprice+=spec->SMS_cena();
//            }
//        }
        if(dynamic_cast<RegularSMS*>(poraka[i])){
            r++;
            rprice+=poraka[i]->SMS_cena();
        }
        else{
            s++;
            sprice+=poraka[i]->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<r<<" regularni SMS poraki i nivnata cena e: "<<rprice<<endl;
    cout<<"Vkupno ima "<<s<<" specijalni SMS poraki i nivnata cena e: "<<sprice<<endl;
}
int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
