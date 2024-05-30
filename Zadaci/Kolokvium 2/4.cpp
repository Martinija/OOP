#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    float cena;

private:
    void copy(const Pizza &other){
        strcpy(this->ime,other.ime);
        strcpy(this->sostojki,other.sostojki);
        cena=other.cena;
    }
public:
    Pizza(char *ime=" ",char *sostojki=" ",float cena=0):cena(cena){
        strcpy(this->ime,ime);
        strcpy(this->sostojki,sostojki);

    }
    virtual float price(){
        return cena;
    }
    friend ostream &operator<<(ostream &o,Pizza &p);
    bool operator <(Pizza &p){
        return price()<p.price();
    }
};
enum Size{
    small,large,family
};
char Tip[100][100]={"small","large","family"};

class FlatPizza:public Pizza{
private:
    Size type;
public:
    FlatPizza(char *ime=" ",char *sostojki=" ",float cena=0,Size type=small):Pizza(ime,sostojki,cena){
        this->type=type;
    }
    float price(){
        if(type==small){
            return cena*1.1;
        }
        else if(type==large){
            return cena*1.2;
        }
        else if(type==family){
            return cena*1.3;
        }
        else{
            return cena;
        }
    }

    char* getSize(){
        return Tip[type];
    }
};

class FoldedPizza:public Pizza{
private:
    bool brasno;
public:
    FoldedPizza(char *ime=" ",char *sostojki=" ",float cena=0):Pizza(ime,sostojki,cena){
        this->brasno=true;
    }
    float price(){
        if(brasno){
            return cena*1.1;
        }
        else{
            return cena*1.3;
        }
    }
    void setWhiteFlour(bool newFlour){
        brasno=newFlour;
    }
    bool getFlour(){
        return brasno;
    };
};
ostream &operator<<(ostream &o,Pizza &p){
    o<<p.ime<<": "<<p.sostojki<<", ";
    FoldedPizza *folded=dynamic_cast<FoldedPizza*>(&p);
    if(folded){
        if (!folded->getFlour()){
            o<<"nwf";
        }
        else{
            o<<"wf";
        }
    }
    else {
        FlatPizza *flat=dynamic_cast<FlatPizza*>(&p);
        if(flat){
            o<<flat->getSize();
        }
    }
    o<<" - "<<p.price()<<endl;
    return o;
}
void expensivePizza(Pizza **pizzas,int n){
    int maks=0;
    int index=-1;
    for (int i = 0; i < n; ++i) {
        if(pizzas[i]->price()>maks){
            maks=pizzas[i]->price();
            index=i;
        }
    }
    if(index==-1){
        return;
    }
    cout<<*pizzas[index];
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
