#include<iostream>
#include<cstring>
using namespace std;
class User;
class SocialNetwork;
class UserAlreadyExistsException {
private:
    char username[50];
public:
    UserAlreadyExistsException( char* username) {
        strcpy(this->username, username);
    }

    void what()  {
        cout << "User with username " << username << " already exists!" << endl;
    }
};

class UserNotFoundException {
private:
    char username[50];
public:
    UserNotFoundException( char* username) {
        strcpy(this->username, username);
    }

    void what()  {
        cout << "User with username " << username << " was not found!" << endl;
    }
};

class FriendsLimitExceededException {
    int limit;
public:
     explicit FriendsLimitExceededException(int limit) : limit(limit) {}

    void what()  {
        cout << "Can't have more than " << limit << " friends." << endl;
    }
};
class User {
private:
    char username[50];
    int age;
    int friends;
    static int limit;

public:
    friend class UserAlreadyExistsException;
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    User &operator++() {
        if(friends>=limit)
        {
            throw FriendsLimitExceededException(limit);
        }else{
            ++friends;
        }
        return *this;
    }
    static  void setLimit(int newLimit){
        limit=newLimit;
    }
    friend class SocialNetwork;

     char *getUsername() {
         return username;
     };

};
int User::limit=3;


class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
        for(int i=0;i<n;i++){
            if(strcmp(users[i].username,u.getUsername())==0){
                throw UserAlreadyExistsException(users[i].username);
            }
        }
        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        User *user1 = nullptr;
        User *user2 = nullptr;

        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                user1 = &users[i];
            }
            if (strcmp(users[i].username, secondUsername) == 0) {
                user2 = &users[i];
            }
        }
        if (!user2) {
            throw UserNotFoundException(secondUsername);
        }

        if (!user1) {
            throw UserNotFoundException(firstUsername);
        }

        if (user1->friends >= User::limit || user2->friends >= User::limit) {
            throw FriendsLimitExceededException(User::limit);
        }

        ++(user1->friends);
        ++(user2->friends);
    }

/*
    void friendRequest(char* firstUsername, char* secondUsername) {
        User *firstFound = nullptr, *secondFound = nullptr;

        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].getUsername(), firstUsername) == 0) {
                firstFound = &users[i];
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].getUsername(), secondUsername) == 0) {
                        secondFound=&users[j];

                    }
                }
            }
        }
        if (!firstFound) {
            throw UserNotFoundException(firstUsername);
        }
        if (!secondFound) {
            throw UserNotFoundException(secondUsername);
        }
        if (firstFound->friends >= User::limit || secondFound->friends >= User::limit){
                throw FriendsLimitExceededException(User::limit);
        }
           ++firstFound->friends;
            ++secondFound->friends;

    }
    */





    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i=0;i<network.n;i++) {
            os << network.users[i] << endl;
        }
        return os;
    }
    ~SocialNetwork(){
        delete []users;
    }
};


int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        char username[50]; int age;
        cin >> username >> age;
        User u(username, age);
        try{
            sn += u;
        }
        catch (UserAlreadyExistsException &e){
            e.what();
        }
    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        }
        catch (FriendsLimitExceededException &e){
            e.what();
        }
        catch (UserNotFoundException u){
            u.what();
        }
    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    User::setLimit(maxFriends);
    cin >> friendships;
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        }
        catch (UserNotFoundException &e){
            e.what();
        }
        catch (FriendsLimitExceededException &e){
            e.what();
        }
    }
    cout << sn;
    return 0;
}
