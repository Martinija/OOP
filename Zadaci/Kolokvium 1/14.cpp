#include <iostream>
#include <cstring>
using namespace std;
enum  Extension{
    txt,pdf,exe
};
char extensions[100][100] = {"pdf", "txt", "exe"};
class File{
private:
    char *ime;
    Extension e;
    char *imecovek;
    int numDatoteka;

    void copy(const File &other)
    {
        this->ime=new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->e=other.e;
        this->imecovek=new char[strlen(other.imecovek)+1];
        strcpy(this->imecovek,other.imecovek);
        this->numDatoteka=other.numDatoteka;
    }
public:
    File(char *ime=" ", char *imecovek="",int numDatoteka=0,Extension e=(Extension)1){

        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->e=e;
        this->imecovek=new char[strlen(imecovek)+1];
        strcpy(this->imecovek,imecovek);
        this->numDatoteka=numDatoteka;
    }
    File(const File&other){
        copy(other);
    }
    ~File()
    {
        delete []ime;
        delete []imecovek;
    }
    File&operator=(const File&other){
        if(this==&other){
            return *this;
        }
        delete[]imecovek;
        delete []ime;
        copy(other);
        return *this;
    }
    void print(){
        cout<<"File name: "<<ime<<"."<<extensions[e]<<endl;
        cout<<"File owner: "<<imecovek<<endl;
        cout<<"File size: "<<numDatoteka<<endl;
    }
    bool equals(const File&that){
        if((strcmp(ime,that.ime)==0) && (strcmp(imecovek,that.imecovek)==0)&& (e==that.e)){
            return true;
        }
        return false;
    }
    bool equalsType(const File & that){
        if((strcmp(ime,that.ime)==0 )&& e==that.e){
            return true;
        }
        return false;
    }
};
class Folder{
private:
    char *imeDirektorium;
    File * files;
    int n;

    void copy(const Folder&other){
        this->imeDirektorium=new char[strlen(other.imeDirektorium)+1];
        strcpy(this->imeDirektorium,other.imeDirektorium);
        this->files=new File[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->files[i]=other.files[i];
        }
        this->n=other.n;
    }
public:
    Folder(const char* name){
        this->imeDirektorium=new char[strlen(name)+1];
        strcpy(this->imeDirektorium,name);
        files= nullptr;
        n=0;
    }
    Folder(const Folder&other){
        copy(other);
    }
    Folder& operator=(const Folder&other){
        if(this==&other){
           return *this;
        }
        delete[]imeDirektorium;
        delete[] files;
        copy(other);
        return *this;
    }
    ~Folder(){
        delete[]imeDirektorium;
        delete[] files;
    }
    void print(){
        cout<<"Folder name: "<<imeDirektorium<<endl;
        for (int i = 0; i < n; ++i) {
            files[i].print();
        }
    }
    /*void remove(const File&file){
        int index=-1,br=0;
        for (int i = 0; i < n; ++i) {
            if(files[i].equals(file)){
                index=i;
                br++;
            }
        }
        if(index==-1){
            return;
        }
        File *tmp=new File[n-br];
        int current=0;
        for (int i = 0; i < n; ++i) {
            if(files[i].equals(file)){
                continue;
            }
            tmp[current++]=files[i];
        }
        delete []files;
        this->files=new File[current];
        for (int i = 0; i < current; ++i) {
            files[i]=tmp[i];

        }
        delete []tmp;
        n=current;
    }
     */
    void remove(const File& file) {
        int br = 0;
        for (int i = 0; i < n; ++i) {
            if (files[i].equals(file)) {
                br++;
            } else {
                files[i - br] = files[i];
            }
        }
        n -= br; // Decrease the size of the array by the number of removed files
    }
    void add(const File & file){
        File *tmp=new File[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=files[i];
        }
        tmp[n++]=file;
        delete[ ]files;
        files=tmp;
    }
};


int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
