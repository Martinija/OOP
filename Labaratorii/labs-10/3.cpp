#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class InvalidOperation{
public:
    void print(){
        cout<<"Conference duration exceeded"<<endl;
    }
};
class Speaker{
private:
    string ime;
    string naslov;
    int vreme;
public:
    Speaker( string ime=" ",  string naslov=" ", int vreme=0) : ime(ime), naslov(naslov), vreme(vreme) {}

    const string &getIme() const {
        return ime;
    }

    void setIme(const string &ime) {
        Speaker::ime = ime;
    }

    const string &getNaslov() const {
        return naslov;
    }

    void setNaslov(const string &naslov) {
        Speaker::naslov = naslov;
    }

    int getVreme() const {
        return vreme;
    }

    void setVreme(int vreme) {
        Speaker::vreme = vreme;
    }

    friend ostream &operator<<(ostream &o,Speaker &s){
        o<<s.ime<<" - "<<s.naslov<<", "<<s.vreme;
    }
};

class Conference{
private:
    string kod;
    string datum;
    vector<Speaker> lista;
    static int vremetraenje;
public:

    Conference(string kod=" ",string datum=""){
        this->kod=kod;
        this->datum=datum;
    }

    const string &getKod() const{
        return kod;
    }

    void setKod(const string &kod){
        this->kod = kod;
    };

    const string &getDatum() const{
        return datum;
    };

    void setDatum(const string &datum){
        this->datum = datum;
    };

    const vector<Speaker> &getLista() const{
        return lista;
    };

    void setLista(const vector<Speaker> &lista){
        this->lista = lista;
    };
    bool operator>(Conference&other){
        return lista.size()>other.lista.size();
    }
    bool operator==( Conference &other) {
        return datum==other.datum;
    };
    Conference &operator+=(Speaker &other){
            int totalDuration = 0;
            for (int i=0;i<lista.size();i++) {
                totalDuration += lista[i].getVreme();
            }

            if (totalDuration + other.getVreme() > vremetraenje) {
                throw InvalidOperation();
            }

            lista.push_back(other);
            return *this;

    }
    friend ostream &operator<<(ostream &o,Conference &c){
        o<<c.kod<<" - "<<c.datum<<", "<<c.lista.size();
        return o;
    }

    void longestPresentation(){
       int maks=0,index=0;
        for (int i = 0; i < lista.size(); ++i) {
            if(lista[i].getVreme()>maks){
                maks=lista[i].getVreme();
                index=i;
            }
        }
        cout<<"Longest Presentation: "<<lista[index]<<endl;
    }
   static void setMaxDuration(int newDuration){
        Conference::vremetraenje=newDuration;
    }

};
int Conference::vremetraenje=360;



//Your code here
int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 0) {
        cout << "Speaker constructor" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 1) {
        cout << "Speaker copy-constructor and operator=" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Speaker c1 = speaker2;
        Speaker c3;
        c3 = speaker2;
        cout << c3 << endl;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 2) {
        cout << "Speaker operator print" << endl;
        Speaker speaker1("Aleksandar Stojmenski", "Introduction to C++", 60);
        Speaker speaker2("Stefan Andonov", "Object-Oriented Programming", 120);
        Speaker speaker3("Boban Joksimoski", "Computer Animation", 180);
        cout << speaker1 << endl;
        cout << speaker2 << endl;
        cout << speaker3 << endl;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 3) {
        cout << "Conference class" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Conference conference("CONF001", "2023-07-01");
        try {
            conference += speaker1;
            conference += speaker2;
            conference += speaker3;
        }
        catch (InvalidOperation e){
            e.print();
        }

        cout << conference << endl;
    } else if (testCase == 4) {
        cout << "Conference constructors" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Conference c("CONF001", "2023-07-01");
        try {
            c += speaker1;
            c += speaker2;
        }
        catch (InvalidOperation e){
            e.print();
        }
        Conference c1, c2 = c;
        c1 = c;
        try{
        c2 += speaker3;
        }
        catch (InvalidOperation e){
            e.print();
        }
        cout << c1 << endl;
        cout << c2 << endl;
    } else if (testCase == 5) {
        cout << "Conference operator> constructors" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Conference c("CONF001", "2023-07-01");
        try {
            c += speaker1;
            c += speaker2;
        }
        catch (InvalidOperation e){
            e.print();
        }
        Conference c1, c2 = c;
        try {
            c2 += speaker3;
        }
        catch (InvalidOperation e){
            e.print();
        }
        if (c2 > c) {
            cout << "PASSED" << endl;
        }
    } else if (testCase == 6) {
        cout << "longestPresentation and comparison" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);
        Conference conference("CONF001", "2023-07-01");
        try {
            conference += speaker1;
            conference += speaker2;
            conference += speaker3;
        }
        catch (InvalidOperation e){
            e.print();
        }
        cout << "Conference: " << conference << endl;

        conference.longestPresentation();

        // Test case for comparison operators
        Conference conference2("CONF002", "2023-07-01");
        try {
            conference2 += speaker1;
            conference2 += speaker2;
        }
        catch (InvalidOperation e){
            e.print();
        }
        if (conference > conference2) {
            cout << "CONF001 has more speakers than CONF002." << endl;
        } else {
            cout << "CONF001 has fewer speakers than CONF002." << endl;
        }

        // Test case for exceeding duration limit
        Speaker speaker4("Sarah Adams", "Advanced C++ Programming", 240);

    } else if (testCase == 7) {
        cout << "Exception handling" << endl;
        cout << "longestPresentation and comparison" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);
        Conference conference("CONF001", "2023-07-01");
       try {
           conference += speaker1;
           conference += speaker2;
           conference += speaker3;
       }
       catch (InvalidOperation e){
           e.print();
       }
        Conference conference2("CONF002", "2023-07-01");
       try {
           conference2 += speaker1;
           conference2 += speaker2;
       }
       catch (InvalidOperation e){
           e.print();
       }
        if (conference > conference2) {
            cout << "CONF001 has more speakers than CONF002." << endl;
        } else {
            cout << "CONF001 has fewer speakers than CONF002." << endl;
        }
        Speaker speaker4("Sarah Adams", "Advanced C++ Programming", 240);
        try{
        conference += speaker4;
        }
        catch (InvalidOperation e){
            e.print();
        }


    } else if (testCase == 8) {
        Conference conference4("CONF004", "2023-07-01");
        Conference conference5("CONF005", "2023-07-01");

        Speaker speaker9("Alex Turner", "Network Security", 120);
        Speaker speaker10("Olivia Parker", "Artificial Intelligence", 180);
        try {
            conference4 += speaker9;
            conference5 += speaker10;
        }
        catch (InvalidOperation e){
            e.print();
        }
        cout << "Conference 4: " << conference4 << endl;
        cout << "Conference 5: " << conference5 << endl;

        if (conference4 == conference5) {
            cout << "Conference 4 and Conference 5 have the same date." << endl;
        } else {
            cout << "Conference 4 and Conference 5 have different dates." << endl;
        }
    } else if (testCase == 9) {
        Conference conference3("CONF003", "2023-07-01");

        Conference::setMaxDuration(1000);
        Speaker speaker5("Michael Brown", "Web Development", 180);
        Speaker speaker6("Emily Davis", "Machine Learning", 240);
        Speaker speaker7("Robert Wilson", "Software Engineering", 120);
        try {
            conference3 += speaker5;
            conference3 += speaker6;
            conference3 += speaker7;
        }
        catch (InvalidOperation e){
            e.print();
        }
        cout << "Conference 3: " << conference3 << endl;

        Speaker speaker8("Jessica Lee", "Database Management", 180);

        try {
            conference3 += speaker8;
        }
        catch (InvalidOperation e){
            e.print();
        }
        cout << conference3;

    }
    return 0;
}


