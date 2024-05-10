#include <iostream>
#include <string>
#include "date.h"
using namespace std;


string numberToMonth(string num1, string num2, string num3) {
    string month;
    if(num1=="1"){
        month="January";
    }
    if(num1=="2"){
        month="Feburary";
    }
    if(num1=="3"){
        month="March";
    }
    if(num1=="4"){
        month="April";
    }
    if(num1=="5"){
        month="May";
    }
    if(num1=="6"){
        month="June";
    }
    if(num1=="7"){
        month="July";
    }
    if(num1=="8"){
        month="August";
    }
    if(num1=="9"){
        month="September";
    }
    if(num1=="10"){
        month="October";
    }
    if(num1=="11"){
    month="November";
    }
    if(num1=="12"){
    month="December";
    }

    return month + " " + num2 +", " + num3;
}


Birthdate::Birthdate(string birthday_info){
    this->birthday_info="";
    set_date();
    string temp= this->birthday_info;
    int size= temp.length();
    string num1;
    string num2;
    string num3;
    int flag=0;
    for (int i=0; i<size; i++){
        if(temp[i]=='0'){
            if(i==0){
                num1=temp[i+1];
                i=i+2;
            }
            else if(i!=0){
                num2=temp[i+1];
                i=i+3;
                flag=1;
            }
        }
        else if(temp[i+2]=='/'){
            if(i==0){
                num1=temp.substr(i,2);
                i=i+2;
            }
            else if(i!=0){
                num2=temp.substr(i,2);
                i=i+3;
                flag=1;
            }
              
        }
        else if(temp[i+2]!='/'){
            if(i==0){
                num1=temp[0];
                i++;
            }
            else if(i!=0){
                num2=temp[0];
                i+=2;
                flag=1;
            }
            
        }
        if(flag==1){
            num3=temp.substr(i,size-i);
            break;
        }
    }
    temp = numberToMonth(num1, num2, num3);
    this->birthday_info=temp;
    print();
    // TODO: Complete me!
}


void Birthdate::set_date(){
    // TODO: Do not change the prompts!
    cout << "Enter the birthdate info ";
    cin >> birthday_info;
    // some code here
}

string Birthdate::get_date(string style){
    // TODO: Complete this method, get hint from Email 
    if (style=="full")
	    return birthday_info;
    else
        return birthday_info;

}


void Birthdate::print(){
    // Note: get_contact is called with default argument
   // cout << "final date  " << get_date() << endl;
}

