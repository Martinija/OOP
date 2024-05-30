
#include <iostream>
using namespace std;

class ListContainer;
class List{
private:
    int *niza;
    int n;
public:
    List() {
        niza = nullptr;
        n = 0;
    }
    List(int *niza,int n){
        this->niza = new int[n];
        for(int i = 0; i < n; i++) {
            this->niza[i] = niza[i];
        }
        this->n = n;
    }
    List(const List &other){
        this->niza= new int [other.n];
        for (int i = 0; i < other.n; ++i) {
            this->niza[i]=other.niza[i];
        }
        this->n=other.n;
    }
    ~List(){
        delete []niza;
    }
    List& operator=(const List &l){
        if(this==&l){
            return *this;
        }
        delete[] niza;
        niza= new int [l.n];
        for(int i=0;i<l.n;i++){
            niza[i]=l.niza[i];
        }
        n=l.n;
        return *this;
    }
    int sum(){
        int total=0;
        for (int i = 0; i < n; ++i) {
            total+=niza[i];
        }
        return total;
    }
    double average(){
        return (double)sum()/(double)n;
    }
    void pechati(){
        cout<<n<<": ";
        for(int i=0;i<n;i++){
            cout<<niza[i]<<" ";

        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }
    friend class ListContainer;
};
class ListContainer{
private:
    List *listi;
    int n;
    int obidi;
public:
    //friend class List;
    ListContainer(){
        this->listi=new List[25];
        this->n=0;
        this->obidi=0;
    }
    ListContainer(const ListContainer&other){
        this->listi=new List[25];
        for (int i = 0; i < other.n; ++i) {
            this->listi[i]=other.listi[i];
        }
        this->n=other.n;
        this->obidi=other.obidi;
    }
    ~ListContainer(){
        delete[]listi;
    }
    ListContainer& operator=(const ListContainer &l){
        if(this==&l){
            return *this;
        }
        delete[] listi;
        this->listi=new List[100];
        for (int i = 0; i < l.n; ++i) {
            this->listi[i]=l.listi[i];
        }
        this->n=l.n;
        this->obidi=l.obidi;
        return *this;
    }
    int sum(){
        int total=0;
        for (int i = 0; i < n; ++i) {
            total+=listi[i].sum();
        }
        return total;
    }
    double average(){
        double average=0;
        for(int i=0;i<n;i++){
            average+=listi[i].n;
        }
        return (double )sum()/average;
    }
    void addNewList(List l){
        obidi++;
        for (int i = 0; i < n; ++i) {
            if(listi[i].sum()==l.sum()){
                return;
            }
        }
        listi[n++]=l;
    }
    void print(){
        if(n<=0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for (int i = 0; i < n; ++i) {
            cout<<"List number: "<<(i+1)<<" List info: ";
            listi[i].pechati();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<n<<" Failed attempts: "<<(obidi-n)<<endl;

    }

};
int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];
        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}
