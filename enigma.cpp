#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "enigma.h"
#include "errors.h"

using namespace std;

/* Void function to receive configuration files and output the content into output.txt */
void receiveConfigurationFiles(int argc, char** argv) {
    // There needs to be at least 4 parameters (including executable file) when there are no rotors.
    if (argc <= 3) {
        cerr << "Error: INSUFFICIENT_NUMBER_OF_PARAMETERS!\n";
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    ofstream out;
    out.open("output.txt");

    for (int i=1; i < argc; ++i) {
        ifstream in;
        in.open(argv[i]);

        if (!in)
        {
            cerr << "Error: ERROR_OPENING_CONFIGURATION_FILE!\n";
            exit(ERROR_OPENING_CONFIGURATION_FILE);
        }

        int val;
        in >> val;

        while (!in.fail()) {
            out << val;
            in >> val;
        }
        out << endl;

        in.close();
    }
}


void checkPlugBoardNumbers() {

}

void checkRotorNumbers() {
    
}