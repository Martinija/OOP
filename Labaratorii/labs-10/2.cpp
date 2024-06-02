#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;
class Sentence{
private:
    vector<string >words;
    vector<string>stopwords;
public:
    Sentence(vector<string> &stopwords){
        this->stopwords=stopwords;
    }
    Sentence &operator+=(string other){
        if(find(stopwords.begin(),stopwords.end(),other)==stopwords.end()){
            words.push_back(other);
        }
        return *this;
    }
    Sentence &operator-=(string other){
        if(find(words.begin(),words.end(),other)!=words.end()){
            words.erase(remove(words.begin(),words.end(),other),words.end());
        }
        return *this;
    }
    friend ostream &operator<<(ostream &o,Sentence &s){
       for(int i=0;i<s.words.size();i++){
           o<<s.words[i];
           if(i!=s.words.size()-1) {
               o << " ";
           }
       }
        return o;
    }
};

int main() {
    // Read stopwords from standard input
    vector<string> stopwords;
    string stopword;
    while (cin >> stopword) {
        if (stopword == "done") {
            break;
        }
        stopwords.push_back(stopword);
    }

    // Create a Sentence object with the stopwords
    Sentence sentence(stopwords);

    // Read words to add to the sentence from standard input
    string word;
    while (cin >> word) {
        if (word == "exit") {
            break;
        }
        sentence += word;
    }

    // Display the sentence
    cout << sentence << endl;

    // Demonstrate removing a word
    cin >> word;
    sentence -= word;

    // Display the updated sentence
    cout << sentence << endl;

    return 0;
}
