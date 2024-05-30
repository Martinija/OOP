#include <iostream>
#include <cstring>
using namespace std;
class Book {
protected:
    char isbn[20];
    char naslov[50];
    char avtor[30];
    double osnovnaCena;

    void copy(const Book &other){
        strcpy(this->isbn,other.isbn);
        strcpy(this->naslov, other.naslov);
        strcpy(this->avtor,other.avtor);
        this->osnovnaCena=other.osnovnaCena;
    }
public:
    Book(char *ibsn=" ",char *naslov=" ",char *avtor=" ",double osnovnaCena=0){
        strcpy(this->isbn,ibsn);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor,avtor);
        this->osnovnaCena=osnovnaCena;
    }
    ~Book(){}
    Book(const Book&other){
        copy(other);
    }
    Book &operator=(const Book&other){
        if (this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    void setISBN(char *ibsn ){
        strcpy(this->isbn,ibsn);
    }
    virtual double bookPrice()=0;

  
    friend ostream& operator<<(ostream& out, Book& book) {
        out << book.isbn << ": " << book.naslov << ", " << book.avtor << " " << book.bookPrice() << "\n";
        return out;
    }
    bool operator>(const Book &rhs) const {
        return osnovnaCena > rhs.osnovnaCena;
    }

};

class OnlineBook:public Book{
private:
    char *url;
    int golemina;
public:
    OnlineBook(char *ibsn=" ",char *naslov=" ",char *avtor=" ",double osnovnaCena=0,char *url= 0,int golemina=0):Book(ibsn,naslov,avtor,osnovnaCena){
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);
        this->golemina=golemina;
    }
    ~OnlineBook(){
        delete []url;
    }
    OnlineBook(const OnlineBook&ob): Book(ob){
        this->url=new char[strlen(ob.url)+1];
        strcpy(this->url,ob.url);
        this->golemina=ob.golemina;
    }
    OnlineBook &operator=(const OnlineBook&other){
        if(this==&other){
            return *this;
        }
        Book::operator=(other);
        delete []url;
        this->url=new char[strlen(other.url)+1];
        strcpy(this->url,other.url);
        this->golemina=other.golemina;
        return *this;
    }
    double bookPrice(){
        if(golemina>20){
            return osnovnaCena*1.2;
        }
        else{
            return osnovnaCena;
        }
    }




};

class PrintBook:public Book{
private:
    double tezhina;
    bool zaliha;
public:
    PrintBook(char *ibsn=" ",char *naslov=" ",char *avtor=" ",double osnovnaCena=0,double tezhina=0,bool zaliha=false): Book(ibsn, naslov,avtor,osnovnaCena){
        this->tezhina=tezhina;
        this->zaliha=zaliha;
    }
    ~PrintBook(){}
    double bookPrice(){
        if (tezhina>0.7){
            return osnovnaCena*1.15;
        }
        else
        {
            return osnovnaCena;
        }
    }
    PrintBook(const PrintBook& other) : Book(other) {
        this->tezhina=other.tezhina;
        this->zaliha=other.zaliha;
    }

    PrintBook& operator=(const PrintBook& other) {
        if(this == &other) {
            return *this;
        }
        Book::operator=(other);
        this->tezhina=other.tezhina;
        this->zaliha=other.zaliha;
        return *this;
    }


};
void mostExpensiveBook (Book** books, int n){
    int brojachO=0,brojachP=0;
    /*
     * for(int i=0,i<n;i++){
     * Online *o=dynamic_cast<OnlineBook*>(books[i]);
         * if(o){
             * brojachO++;
         * }
         * else{
            * PrintedBook *p=dynamic_cast<PrintBook*>(books[i]);
             * if(p){
             *  brojachP++;}
             * }
     * }
     */
    for (int i = 0; i < n; ++i) {
        if(dynamic_cast<OnlineBook*>(books[i])) {
            brojachO++;
        } else if(dynamic_cast<PrintBook*>(books[i])) {
            brojachP++;
        }
    }
    int maks=0,index=0;
    for (int i = 0; i < n; ++i) {
        if(books[i]->bookPrice()>maks){
            maks=books[i]->bookPrice();
            index=i;
        }
    }
    cout << "FINKI-Education\n";
    cout << "Total number of online books: " << brojachO << "\n";
    cout << "Total number of print books: " << brojachP << "\n";
    cout << "The most expensive book is:\n";
    cout<<*books[index]<<"\n";
}
int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
