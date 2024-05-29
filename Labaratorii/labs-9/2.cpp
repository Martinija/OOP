#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Flight {
protected:
    char kod[40];
    char trgnuvanja[100];
    char sletuvanje[100];
    double cenaLet;
    double cenaBagaz;
public:
    Flight(char *kod="",char *trgnuvanje="",char *sletuvanje="",double cenaLet=0,double cenaBagaz=0) :cenaLet(cenaLet),cenaBagaz(cenaBagaz){
        strcpy(this->kod,kod);
        strcpy(this->trgnuvanja,trgnuvanje);
        strcpy(this->sletuvanje,sletuvanje);
    }
    virtual double calculateTotalPrice(){
        return cenaBagaz+cenaLet;
    }
     virtual void displayInfo(){
        cout<<kod<<" "<<trgnuvanja<<"-"<<sletuvanje<<" "<<endl;
        cout<<"Total price $"<<calculateTotalPrice()<<endl;
    }
};
class InvalidSeatNumberException{
private:
    string text;
public:
    void print(){
        cout<<"Invalid Seat Number Exception"<<endl;
    }
};

class EconomyFlight:public Flight{
private:
    char brSedishta[4];
public:
    static double LOYALTY_DISCOUNT;
    EconomyFlight(Flight&f,char *brSedishta=0 ): Flight(f){
        strcpy(this->brSedishta,brSedishta);
    }
    double calculateTotalPrice(){
        if (!(brSedishta[0] == 'A' || brSedishta[0] == 'B' || brSedishta[0] == 'C' || brSedishta[0] == 'D' || brSedishta[0] == 'E' || brSedishta[0] == 'F')) {
            throw InvalidSeatNumberException();
        }

        double discountPrice = Flight::calculateTotalPrice()*(100-LOYALTY_DISCOUNT)/100.0;
        if (brSedishta[0] == 'C' || brSedishta[0] == 'F') {
            discountPrice *= 1.3;
        }

        return discountPrice;
    }
    void displayInfo(){
        cout<<kod<<" "<<trgnuvanja<<"-"<<sletuvanje<<" "<<brSedishta<<endl;
        try {
            double totalPrice = calculateTotalPrice();
            cout << "Total Price: $" << totalPrice << endl;
        }
        catch(InvalidSeatNumberException &e){
            e.print();
        }
    }
    static void setLoyaltyDiscount(double newDiscount){
        LOYALTY_DISCOUNT=newDiscount;
    }
};
double EconomyFlight::LOYALTY_DISCOUNT=20;

int main() {
    int testCase;
    cin>>testCase;
    char code[100];
    char from[100];
    char to[100];
    double price;
    double baggagePrice;
    char seatNumber[4];

    if(testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        int n;
        cin>>n;
        for(int i=0; i<n;i++){
            cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
            Flight f = Flight(code, from, to, price, baggagePrice);
            EconomyFlight ec = EconomyFlight(f, seatNumber);
            ec.displayInfo();
        }
    }
    if(testCase == 2){
        cout << "===== Testiranje na isklucoci ======" << endl;
        int n;
        cin>>n;
        for(int i=0; i<n;i++){
            cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
            Flight f = Flight(code, from, to, price, baggagePrice);
            try {
                EconomyFlight ec = EconomyFlight(f, seatNumber);
                ec.displayInfo();
            }
            catch(InvalidSeatNumberException &e){
                e.print();
            }
        }
    }
    if(testCase == 3){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
        Flight f = Flight(code, from, to, price, baggagePrice);
        EconomyFlight ec = EconomyFlight(f, seatNumber);
        ec.displayInfo();
        EconomyFlight::setLoyaltyDiscount(50);
        ec.displayInfo();
    }

    return 0;
}
