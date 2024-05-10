#include "person.h"
#include "contact.h"
#include "network.h"
#include "raja.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Person::Person(string f_name, string l_name, string b_date, string email, string phone, vector<Person*> myfriends, string codename)
    : f_name(f_name), l_name(l_name), b_date(b_date), email(email), phone(phone), myfriends(myfriends), codename(codename) {}

void Person::print_person() {
    cout << l_name << ", " << f_name << endl;
    cout << b_date << endl;
    cout << email << endl;
    cout << phone << endl;
}

string Person::get_name(string style) {
    if (style == "full") {
        return f_name + " " + l_name;
    } else if (style == "last") {
        return l_name;
    } else {
        return ""; // Default to empty string if style is invalid
    }
}

void Person::makeFriend(Person* newFriend) {
    myfriends.push_back(newFriend);
}



int main(){

    Birthdate nt_2 = Birthdate("");
    Phone nt_3 = Phone("","");
    Email nt_4 = Email("","");

    string f_name;
    string l_name;
    vector<Person*> myfriends;
    string codename;

    cout << "Enter the first name of this person ";
    cin >> f_name;

    cout << "Enter the last name of this person ";
    cin >> l_name;

    string b_date = nt_2.get_date();
    string email = nt_3.get_contact();
    string phone = nt_4.get_contact();

    Person nt_1 = Person(f_name, l_name, b_date, email, phone, myfriends, codename);

    cout << endl;
    nt_1.print_person(); 

    Network network_nt("network.txt"); // Create an instance of the Network class

    network_nt.showMenu();

    cout << endl;

    // After you're done, you can save the database back to a file if needed

    return 0;
}