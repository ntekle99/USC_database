#include <iostream>
#include "raja.h"
using namespace std;

void printMe(string type){
        if (type == "banner"){
            char banner[] = \
    "   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
        ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
        ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
        ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
        ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
        ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
        ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
            cout << endl << banner << endl << endl;
        }
}

string codeName(string str1, string str2) {
    // Concatenate str1 and str2
    string concatenated = str1 + str2;

    // Remove spaces
    concatenated.erase(remove_if(concatenated.begin(), concatenated.end(), ::isspace), concatenated.end());

    // Convert all letters to lowercase
    transform(concatenated.begin(), concatenated.end(), concatenated.begin(), ::tolower);
    return concatenated;
}