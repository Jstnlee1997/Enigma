#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <strings.h>
#include "enigma.h"
#include "errors.h"

using namespace std;

/* Class Functions */

/* Plugboard Class Functions */
// Function to create a connection between two characters
void Plugboard::setConnection(int first, int second)
{
    // If number is not between 0 and 25
    if (first < 0 || first > 25 || second < 0 || second > 25) {
        cout << "Error: INVALID_INDEX\n";
        exit(INVALID_INDEX);
    }

    // If file attempts to connect a contact with itself
    if (first == second) {
        cout << "Error: IMPOSSIBLE_PLUGBOARD_CONFIGURATION\n";
        exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }


    int i=0;
    for (; i<13; i++) {
        // Reached an empty slot in connections to create a new connection
        if (connections[i][0] == -1) break;

        // Check if either characters already have existing connections
        if (connections[i][0] == first || connections[i][0] == second || connections[i][1] == first || connections[i][1] == second) {
            cout << "Error: IMPOSSIBLE_PLUGBOARD_CONFIGURATION\n";
            exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }
    }

    // If it reaches here, can create new connection
    connections[i][0] = first;
    connections[i][1] = second;
}

// Function to receive the corresponding connection if the connection exists
void Plugboard::getConnection(int &first)
{
    for (int i=0; i<13; i++) {
        // No established connection
        if (connections[i][0] == -1) break;

        // Existing connection
        if (connections[i][0] == first) {
            first = connections[i][1];
            break;
        }
        if (connections[i][1] == first) {
            first = connections[i][0];
            break;
        }
    }
}

// Function to print out connections to see existing connections
void Plugboard::printConnections()
{
    for (int i=0; i<13; i++) {
        // End of connections
        if (connections[i][0] == -1) break;

        // Print out connections
        cout << connections[i][0] << "<->" << connections[i][1] << endl;
    }
}


/* Function Definitions */
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
        char filename[7];
        int val, index=0;
        int values[30];
        ifstream in;
        in.open(argv[i]);

        // Error opening configuration file
        if (!in)
        {
            cerr << "Error: ERROR_OPENING_CONFIGURATION_FILE!\n";
            exit(ERROR_OPENING_CONFIGURATION_FILE);
        }

        // Check for name of current configuration file
        strncpy(filename, argv[i], 7);

        // If current file is for plugboards
        if (!strcmp("plugboa", filename)) {
            auto plugboard = Plugboard();
            
            in >> val;

            while (!in.fail()) {
                out << val;
                values[index] = val;
                index ++;
                in >> val;
            }
            out << endl;

            // Check if there are odd number of numbers for plugboard
            if (index % 2 != 0) {
                cout << "Error: INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS\n";
                exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
            }

            // Create connections using values obtained for plugboard
            for (int i=0; i<index-1; i+=2) {
                plugboard.setConnection(values[i], values[i+1]);
            }

            plugboard.printConnections();
        }

        else {
            in >> val;

            while (!in.fail()) {
                out << val;
                in >> val;
            }
            out << endl;
        }
        
        in.close();
    }
    out.close();
}


void checkPlugBoardNumbers() {

}

void checkRotorNumbers() {
    
}

void encryptMessage(char* message)
{
    cout << "Your encrypted/decrypted message is: " << message << endl;
}