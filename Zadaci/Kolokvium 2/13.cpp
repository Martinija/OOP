#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
using namespace std;

class Image{
protected:
    char *imeslika;
    char ime[50];
    int height;
    int width;
private:
    void copy(const Image&other){
        strcpy(ime,other.ime);
        this->imeslika=new char [strlen(other.imeslika)+1];
        strcpy(this->imeslika,other.imeslika);
        height=other.height;
        width=other.width;
    }
public:
    Image(char *imeslika="untitled",char *ime="unknown",int width=800,int height=800){
        strcpy(this->ime,ime);
        this->imeslika=new char [strlen(imeslika)+1];
        strcpy(this->imeslika,imeslika);
        this->height=height;
        this->width=width;
    }
    Image(const Image&other){
        copy(other);
    }
    Image &operator=(const Image&other){
        if(this!=&other){
            delete[]imeslika;
            copy(other);
        }
        return *this;
    }
    ~Image(){
        delete[ ]imeslika;
    }
     virtual int fileSize(){
        return height*width*3;
    }
    friend ostream &operator<<(ostream &o,Image&i){
        o<<i.imeslika<<" "<<i.ime<<" "<< fixed << setprecision(0) << i.fileSize() << endl;
        return o;
    }
    bool operator>(Image &i){
        return fileSize()>i.fileSize();
    }


};
class TransparentImage:public Image{
private:
    bool transparent;
public:
    TransparentImage(char *imeslika="untitled",char *ime="unknown",int width=800,int height=800,bool transparent= true): Image(imeslika,ime,width,height){
        this->transparent=transparent;
    }
    TransparentImage(const TransparentImage&other) : Image(other){
        this->transparent=other.transparent;
    }
    TransparentImage &operator=(const TransparentImage &other){
        if(this!=&other){
            Image::operator=(other);
            this->transparent=other.transparent;
        }
        return *this;
    }
    int fileSize(){
        if(transparent){
            return width*height*4;
        }
        else{
            return (width*height+((width*height)/8.0));
        }
    }
    bool operator>(TransparentImage &i){
        return fileSize()>i.fileSize();
    }
};

class Folder{
private:
    char name[25];
    char username[50];
    Image *images[100];
    int n;

    void copyFolder(const Folder&other){
        strcpy(name,other.name);
        strcpy(username,other.username);
        for (int i = 0; i < other.n; ++i) {
            this->images[i]=other.images[i];
        }
        n=other.n;
    }
public:
    Folder(char *name="unknown",char *username="unknown"){
        strcpy(this->name,name);
        strcpy(this->username,username);
        n=0;
    }
    Folder(const Folder&other){
        copyFolder(other);
    }
    double folderSize(){
        double sum=0;
        for (int i = 0; i < n; ++i) {
            sum+=images[i]->fileSize();
        }
        return sum;
    }
    friend ostream &operator<<(ostream &o,Folder&f){
        o<<f.name<<" "<<f.username<<"\n--\n";
        for(int i=0;i<f.n;i++){
            o<<*f.images[i];
        }
        o<<"--\nFolder size: "<< fixed << setprecision(0) << f.folderSize() << endl;
        return o;
    }
    Image *getMaxFile(){
        int index=-1;
        for (int i = 0; i < n; ++i) {
            if(index==-1||images[i]->fileSize()>images[index]->fileSize()){
                index=i;
            }
        }
        if(index==-1){
            return NULL;
        }
        return images[index];
    }
    Folder &operator+=(Image &other){
        if(n>100){
            return *this;
        }
        images[n++]=&other;
        return *this;
    }
    Image *operator[](int index){
        if(index<n){
            return images[index];
        }
        else{
            return NULL;
        }
    }
};
Folder &max_folder_size(Folder *f,int n){
    int index=-1;
    for (int i = 0; i < n; ++i) {
        if(f[i].folderSize()>f[index].folderSize()){
            index=i;
        }
    }
    return f[index];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout << max_folder_size(dir_list, folders_num);
    }
    return 0;
};
