#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Athlete{
protected:
    char ime[100];
    int age;
public:
    Athlete(char *ime="", int age=0) :  age(age) {
        strcpy(this->ime,ime);
    }

    virtual  void displayInfo(){
        cout<<"Athlete: "<<ime<< "\n";
        cout<<"Age: "<<age<<"\n";
    };
};

class Runner : virtual public Athlete{
private:
    double speed;
public:
    Runner(char *ime="", int age=0,double speed=0): Athlete(ime,age){
        this->speed=speed;
    }
     virtual void displayInfo(){
        Athlete::displayInfo();
        cout<<"Speed: "<< speed<<" mph"<<endl;
    }

    double getSpeed() const {
        return speed;
    }
};
class Jumper: virtual public Athlete{
private:
    double height;
public:
    Jumper(char *ime=" ", int age=0,double height=0): Athlete(ime,age){
        this->height=height;
    }
    virtual void displayInfo(){
        Athlete::displayInfo();
        cout<<"Height: "<< height<<"m"<<endl;
    }

    double getHeight() const {
        return height;
    }
};

class AllRoundAthlete:public Runner,public Jumper{
private:
    int stamina;
public:
    AllRoundAthlete(char *ime=" ", int age=0, double speed=0,double height=0,int stamina=0): Athlete(ime,age), Runner(ime,age, speed),
                                                                                             Jumper(ime,age,height){this->stamina=stamina;}
    virtual void displayInfo(){
        Runner::displayInfo();
        cout<<"Height: "<<getHeight() <<"m"<<endl;
        cout<<"Stamina: "<<stamina<<"\n";
    }
};
Athlete* findAthleteWithMaxValue(Athlete** athletes, int n){
    Athlete *najak=athletes[0];
    double maks=0;
    for (int i = 0; i <n ; ++i) {
        Runner* runner = dynamic_cast<Runner*>(athletes[i]);
        Jumper* jumper = dynamic_cast<Jumper*>(athletes[i]);
        if(runner){
            if(runner->getSpeed()>maks){
                maks= runner->getSpeed();
                najak=athletes[i];
            }
        }
        else if(jumper){
            if(jumper->getHeight()>maks){
                maks= jumper->getHeight();
                najak=athletes[i];
            }
        }
    }
    return najak;
}

int main() {
    char name[50];
    int age;
    double speed;
    double height;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>name;
        cin>>age;
        AllRoundAthlete allRoundAthlete(name, age, 13.6, 1.80, 6);
        allRoundAthlete.displayInfo();
    }
    else {

        cin >> n;

        Athlete **athletes = new Athlete *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> name >> age >> speed;

                athletes[i] = new Runner(name, age, speed);
            } else {
                cin >> name >> age >> height;

                athletes[i] = new Jumper(name, age, height);
            }

        }

        findAthleteWithMaxValue(athletes, n)->displayInfo();

    }


    return 0;
}
