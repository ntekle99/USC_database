#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
// TODO: You may need to add other libraries here!
using namespace std;


class Date {
    // TODO: private or protected? Look at your children!
protected:	
    string type;
public:
	virtual void print() = 0;
     virtual string get_date(string style="full") = 0;
	virtual void set_date() = 0;
};


class Birthdate: public Date{
private:
    string birthday_info;
public:
    Birthdate(string birthday_info);

    void set_date();
    void print();
    string get_date(string style="full");

    // TODO: Complete me!
};


#endif