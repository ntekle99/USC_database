#include <iostream>
#include "network.h"
#include <limits>
#include "person.h"
#include "raja.h"
#include <fstream>
#include <sstream>
using namespace std;

Network::Network() {
    head = NULL;
    tail = NULL;
    count = 0;
}

Network::Network(string fileName) {
    loadDB(fileName);
}

Network::~Network() {}

Person* Network::search(Person* searchEntry) {
    Person* ptr = head;
    while (ptr != NULL) {
        if (ptr == searchEntry) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

Person* Network::search(string fname, string lname) {
    Person* ptr = head;
    while (ptr != NULL) {
        if ((ptr->f_name == fname) || (ptr->l_name == lname)) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void Network::loadDB(string filename) {
    ifstream file(filename); // Open the file for reading

    string line;
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty())
            continue;

        // Check for the dashes indicating the start of a new person's information
        if (line == "--------------------") {
            // Skip to the next line to avoid reading the dashes as part of the person's data
            getline(file, line);
            cout << endl;
        }

        stringstream ss(line);
        string fname, lname, bdate, email, phone;
        getline(ss, fname, ','); // Read first name up to the comma delimiter
        getline(file, lname);    // Corrected order of reading lname and bdate
        getline(file, bdate);
        getline(file, email);
        getline(file, phone);

        string codename= codeName(fname, lname);
        cout << codename << endl;
        cout << endl;
        // Read myfriends vector
        vector<Person*> myfriends;
        while (getline(file, line)) {
            if (line == "--------------------")
                break;
            stringstream ss(line);
            string friendFName, friendLName;
            getline(ss, friendFName, ','); // Read first name up to the comma delimiter
            getline(ss, friendLName);
            // Search for the friend and add to myfriends vector
            Person* friendPtr = search(friendFName, friendLName);
            if (friendPtr != nullptr)
                myfriends.push_back(friendPtr);
        }

        // Create a new Person object and add it to the network
        Person* newPerson = new Person(fname, lname, bdate, email, phone, myfriends, codename);
        push_back(newPerson);
    }

    // Close the file after reading
    file.close();
    cout << "Network loaded from " << filename << " with " << count << " people" << endl;
}

void Person::pprint_friends() {
    // Bubble sort algorithm to sort friends based on the code of names
    int n = myfriends.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Extract the first and second letters of the code for comparison
            char firstLetter1 = myfriends[j]->codename[0];
            char firstLetter2 = myfriends[j + 1]->codename[0];
            char secondLetter1 = myfriends[j]->codename[1];
            char secondLetter2 = myfriends[j + 1]->codename[1];

            // Compare first letters
            if (firstLetter1 > firstLetter2) {
                // Swap if necessary
                swap(myfriends[j], myfriends[j + 1]);
            } else if (firstLetter1 == firstLetter2) {
                // If first letters are the same, compare second letters
                if (secondLetter1 > secondLetter2) {
                    // Swap if necessary
                    swap(myfriends[j], myfriends[j + 1]);
                }
            }
        }
    }

    // Print the sorted friends
    for (vector<Person*>::iterator it = myfriends.begin(); it != myfriends.end(); ++it) {
        cout << (*it)->f_name << ", " << (*it)->l_name << endl;
    }
}

void Network::saveDB(string filename) {
    ofstream file(filename);
    Person* current = head;
    while (current != nullptr) {
        file << current->f_name << "," << current->l_name << endl;
        file << current->b_date << endl;
        file << current->email << endl;
        file << current->phone << endl;
        for (vector<Person*>::iterator it = current->myfriends.begin(); it != current->myfriends.end(); ++it) {
            file << (*it)->codename << " ("<< (*it)->f_name << " " << (*it)->l_name << ")" << endl;
        }


        file << "--------------------" << endl;

        current = current->next;
    }

    file.close();

    cout << "Network saved to " << filename << endl;
}

void Network::printDB() {
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;

    while (ptr != NULL) {
        cout << ptr->l_name << ", " << ptr->f_name << endl;
        cout << ptr->b_date << endl;
        cout << ptr->email << endl;
        cout << ptr->phone << endl;
        for (vector<Person*>::iterator it = ptr->myfriends.begin(); it != ptr->myfriends.end(); ++it) {
            cout << (*it)->codename << " ("<< (*it)->f_name << " " << (*it)->l_name << ")" << endl;
        }

        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

void Network::push_front(Person* newEntry) {
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;

    head = newEntry;
    count++;
}

void Network::push_back(Person* newEntry) {
    newEntry->prev = tail;
    newEntry->next = NULL;

    if (head != NULL)
        tail->next = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    count++;
}

bool Network::remove(string fname, string lname) {
    Person* ptr = head;
    while (ptr != NULL) {
        if ((ptr->f_name == fname) || (ptr->l_name == lname)) {
            if (ptr == head) {
                head = ptr->next;
                head->prev = nullptr;
            } else if (ptr == tail) {
                tail = ptr->prev;
                tail->next = nullptr;
            } else {
                ptr->next->prev = ptr->prev;
                ptr->prev->next = ptr->next;
            }
            delete ptr;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void Network::showMenu() {
    int opt;
    while (true) {
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library
        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "6. Connect two people and make them friends  \n";
        cout << "7. Print your frineds in order  \n";
        cout << "\nSelect an option ... ";

        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }

        string fname, lname, fileName, bdate;

        cout << "\033[2J\033[1;1H";

        if (opt == 1) {
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        } else if (opt == 2) {
            cout << "Loading network database \n";
            cout << "Enter the name of the load file: ";
            cin >> fileName;
            ifstream file(fileName);
            if (!file.good()) {
                cout << "File " << fileName << " does not exist!" << endl;
            } else {
                file.close();
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " people \n";
            }
        } else if (opt == 3) {
            cout << "Adding a new person \n";
            string fname, lname, bdate, email, phone;

            cout << "Enter first name: ";
            cin >> fname;
            cout << "Enter last name: ";
            cin >> lname;

            string codename = codeName(fname, lname);
            vector<Person*> myfriends;
            // Check if the person already exists
            if (search(fname, lname) != nullptr) {
                cout << "Person already exists! \n";
            } else {
                cout << "Enter birth date: ";
                cin >> bdate;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter phone number: ";
                cin >> phone;

                Person* newPerson = new Person(fname, lname, bdate, email, phone, myfriends, codename);
                push_front(newPerson);

                cout << "Person added successfully! \n";
            }
        } else if (opt == 4) {
            cout << "Removing a person \n";
            cout << "First name: ";
            cin >> fname;
            cout << endl;
            cout << "Last name: ";
            cin >> lname;
            bool result = remove(fname, lname);
            if (result) {
                cout << "Remove Successful! \n";
            } else {
                cout << "Person not found! \n";
            }
        } else if (opt == 5) {
            // Print people with first name
            cout << "Print people with first name \n";
            cout << "First name: ";
            cin >> fname;
            cout << "Last name: ";
            cin >> lname;

            // Search for the person
            Person* result = search(fname, lname);

            if (result != nullptr) {
                // Print out the information of the found person
                cout << "Person found:" << endl;
                cout << "First Name: " << result->f_name << endl;
                cout << "Last Name: " << result->l_name << endl;
                cout << "Birth Date: " << result->b_date << endl;
                cout << "Email: " << result->email << endl;
                cout << "Phone Number: " << result->phone << endl;
            } else {
                cout << "Person not found! \n";
            }
        } else if (opt == 6) {
            cout << "Make friends" << endl;
            cout << "What is person 1 first name? " << endl;
            cin >> fname;
            cout << "What is person 1 last name? " << endl;
            cin >> lname;
            vector<Person*> myfriends;

            // Search for person 1
            Person* result1 = search(fname, lname);
            if (result1 != nullptr) {
                cout << "What is person 2 first name? " << endl;
                cin >> fname;
                cout << "What is person 2 last name? " << endl;
                cin >> lname;

                // Search for person 2
                Person* result2 = search(fname, lname);
                if (result2 != nullptr) {
                    result1->makeFriend(result2);
                    result2->makeFriend(result1);
                    cout << "Friends added successfully!" << endl;
                } else {
                    cout << "Person 2 not found! \n";
                }
            } else {
                cout << "Person 1 not found! \n";
            }
        } 

        else if(opt==7){
            cout << "Search for Person's friends! " << endl;
            cout << "What is Person's first name?  " << endl;
            cin >> fname;
            cout << "What is Person's last name" << endl;
            cin >> lname;
            Person* specificPerson = search(fname, lname); // Assuming "John Doe" exists in the network
            if (specificPerson != nullptr) {
                cout << specificPerson->f_name << ", " << specificPerson->l_name << endl;
                cout << "------------------------------" << endl;
                specificPerson->pprint_friends();
            } else {
                cout << "Person not found!" << endl;
            }
            
        }
        else {
            cout << "Nothing matched!\n";
        }

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to the main menu ... ";
        string temp;
        std::getline(std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}