#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class ExistingGame{
private: string text;
public:

    void message(){
        cout<<"The game is already in the collection"<<endl;
    }

};
class Game{
protected:
    char title[100];
    double price;
    bool sale;
private:
    void copy_g(const Game &other){
        strcpy(this->title,other.title);
        price=other.price;
        sale=other.sale;
    }
public:
    Game(char *title=" ",double price=0,bool sale= false){
        strcpy(this->title,title);
        this->price=price;
        this->sale=sale;
    }
    friend ostream &operator<<(ostream &o,Game &g);
    friend istream &operator>>(istream&i, Game&g);

    bool operator==(Game &other){
        return (strcmp(title,other.title)==0);
    }
    virtual ~Game(){}
    virtual double getprices(){
        if(sale){
            return price *0.3;
        }
        else{
            return price;
        }
    }
};

class SubscriptionGame:public Game {
private:
    double subscription;
    int year;
    int month;

public:
    SubscriptionGame(char *title = " ", double price = 0, bool sale = false, double subscription = 0, int month = 0,
                     int year = 0) : Game(title, price, sale) {
        this->subscription = subscription;
        this->year = year;
        this->month = month;
    }

    friend ostream &operator<<(ostream &o, SubscriptionGame &s);
    friend istream &operator>>(istream &i, SubscriptionGame &s);

    ~SubscriptionGame(){}
    double getprices() {
        double s=Game::getprices();
        int months=0;
        if(year<2018){
            months=(12-this->month)+(2017-year)*12+5;
        }
        else{
            months=5-this->month;
        }
        s+=months*subscription;
        return s;
    }
};

ostream &operator<<(ostream &o,Game&g){
    o<<"Game: "<<g.title<<", regular price: $"<<g.price;
    if(g.sale){
        o<<", bought on sale";
    }
    return o;
}
ostream &operator<<(ostream &o,SubscriptionGame&s){
    Game *tmp=dynamic_cast<Game*>(&s);
    o<<*tmp;
    o<<", monthly fee: $"<<s.subscription<<", purchased: "<<s.month<<"-"<<s.year<<endl;
    return o;
}
istream &operator>>(istream &i,SubscriptionGame &s){
    i.get();
    i.getline(s.title,100);
    i>>s.price>>s.sale;
    i>>s.subscription>>s.month>>s.year;
    return i;
}
istream &operator>>(istream&i, Game&g){
    i.get();
    i.getline(g.title,100);
    i>>g.price>>g.sale;
    return i;
}

class User{
private:
    char name[100];
    Game **games;
    int n;

    void copy_u(const User&other){
        strcpy(this->name,name);

        games=new Game*[other.n];
        for (int i = 0; i <other.n ; ++i) {
            games[i]=new Game(*(other.games[i]));
        }
        n=other.n;
    }
public:
    User(char *name=" "){
        strcpy(this->name,name);
        n=0;
       this->games=new Game * [0];
    }
    User(const User&other){
        copy_u(other);
    }
    User &operator=(const User&other){
        if(this!=&other){
            for (int i = 0; i < n; ++i) {
                delete this->games[i];
            }
            delete []games;
            copy_u(other);
        }
        return *this;
    }
    User &operator+=(Game &g){
        for (int i = 0; i < n; ++i) {
            if(*games[i]==g){
                throw ExistingGame();
            }
        }
        Game **tmp=new Game *[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=games[i];
        }
        SubscriptionGame* sGames=dynamic_cast<SubscriptionGame*>(&g);
        if(sGames){
            tmp[n++]=new SubscriptionGame(*sGames);
        }
        else{
            tmp[n++]=new Game(g);
        }
        delete []games;
        games=tmp;
        return *this;
    }
    ~User(){
        for (int i = 0; i < n; ++i) {
            delete games[i];
        }
        delete []games;
    }
    double total_spent(){
        float sum=0;
        for (int i = 0; i < n; ++i) {
            sum+=games[i]->getprices();
        }
        return sum;
    }
    friend ostream &operator<<(ostream &o,User&u){
        o<<endl;
        o<<"User: "<<u.name<<endl;
        for (int i = 0; i < u.n; ++i) {
            SubscriptionGame *sGames=dynamic_cast<SubscriptionGame*>(u.games[i]);
            o<<"- ";
            if(sGames){
                o<<*sGames;
            }
            else{
                o<<*u.games[i];
            }
            o<<endl;
        }
       
        return o;
    }
};
int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;
        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
