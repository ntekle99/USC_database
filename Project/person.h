#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include "date.h"
#include "contact.h"
#include "raja.h"
// You may need to add other libraries here!
using namespace std;

class Person {
    friend class Network;

private:
    string f_name;
    string l_name;
    string b_date;
    string email;
    string phone;
    vector<Person*> myfriends;
    Person* next; 
    Person* prev;
    string codename;

public:
    
    Person(string f_name, string l_name, string b_date, string email, string phone, vector<Person*> myfriends, string codename);
    void makeFriend(Person* newFriend);
    void print_person();
    string get_name(string style = "full");
    void pprint_friends();
};

#endif