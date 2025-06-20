
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;
void writeToFile() {
    std::ofstream outFile("text.txt");
    char c;
    while((c = std::cin.get()) != '#') {
        outFile.put(c);
    }
    outFile.close();
}

int main() {
    writeToFile();

    // Your code
    ifstream file("text.txt");
    if(!file.is_open()){
        return -1;
    }
    int lowerFq;
    int upperFq;
    int totalCh=0;
    char ch;
    while(file.get(ch)){
        if(isalpha(ch)){
            totalCh++;
        }
        if(islower(ch)){
            lowerFq++;
        }
        else if(isupper(ch)){
            upperFq++;
        }
    }

    double lfq=(lowerFq / static_cast<double>(totalCh));
    double ufq = (upperFq / static_cast<double>(totalCh));
    cout << fixed << setprecision(4);
    cout << ufq << endl;
    cout << lfq <<endl;

    return 0;
}

