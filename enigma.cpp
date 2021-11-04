#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <strings.h>
#include <regex>
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
        cerr << "Error: INVALID_INDEX\n";
        exit(INVALID_INDEX);
    }

    // If file attempts to connect a contact with itself
    if (first == second) {
        cerr << "Error: IMPOSSIBLE_PLUGBOARD_CONFIGURATION\n";
        exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }


    int i=0;
    for (; i<13; i++) {
        // Reached an empty slot in connections to create a new connection
        if (connections[i][0] == -1) break;

        // Check if either characters already have existing connections
        if (connections[i][0] == first || connections[i][0] == second || connections[i][1] == first || connections[i][1] == second) {
            cerr << "Error: IMPOSSIBLE_PLUGBOARD_CONFIGURATION\n";
            exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }
    }

    // If it reaches here, can create new connection
    connections[i][0] = first;
    connections[i][1] = second;
}

// Function to receive the corresponding connection if the connection exists
void Plugboard::getConnection(int &number)
{
    for (int i=0; i<13; i++) {
        // No established connection
        if (connections[i][0] == -1) break;

        // Existing connection
        if (connections[i][0] == number) {
            number = connections[i][1];
            break;
        }
        if (connections[i][1] == number) {
            number = connections[i][0];
            break;
        }
    }
}

// Function to print out connections to see existing connections
void Plugboard::printConnections()
{
    cout << "The Plugboard connections are: \n";
    for (int i=0; i<13; i++) {
        // End of connections
        if (connections[i][0] == -1) break;

        // Print out connections
        cout << connections[i][0] << "<->" << connections[i][1] << endl;
    }
}

/* Reflector Class Functions */
// Function to create a connection between two characters
void Reflector::setConnection(int first, int second)
{
    // If number is not between 0 and 25
    if (first < 0 || first > 25 || second < 0 || second > 25) {
        cerr << "Error: INVALID_INDEX\n";
        exit(INVALID_INDEX);
    }

    // If file attempts to connect a contact with itself
    if (first == second) {
        cerr << "Error: INVALID_REFLECTOR_MAPPING\n";
        exit(INVALID_REFLECTOR_MAPPING);
    }


    int i=0;
    for (; i<13; i++) {
        // Reached an empty slot in connections to create a new connection
        if (connections[i][0] == -1) break;

        // Check if either characters already have existing connections
        if (connections[i][0] == first || connections[i][0] == second || connections[i][1] == first || connections[i][1] == second) {
            cerr << "Error: INVALID_REFLECTOR_MAPPING\n";
            exit(INVALID_REFLECTOR_MAPPING);
        }
    }

    // If it reaches here, can create new connection
    connections[i][0] = first;
    connections[i][1] = second;
}

// Function to receive the corresponding connection if the connection exists
void Reflector::getConnection(int &number)
{
    for (int i=0; i<13; i++) {
        // No established connection
        if (connections[i][0] == -1) break;

        // Existing connection
        if (connections[i][0] == number) {
            number = connections[i][1];
            break;
        }
        if (connections[i][1] == number) {
            number = connections[i][0];
            break;
        }
    }
}

// Function to print out connections to see existing connections
void Reflector::printConnections()
{
    cout << "The Reflector connections are: \n";
    for (int i=0; i<13; i++) {
        // Print out connections
        cout << connections[i][0] << "<->" << connections[i][1] << endl;
    }
}

/* Rotor Class Functions */
// Function to map current number to its corresponding letter
void Rotor::setConnection(int number, int index) {
    // If number is not between 0 and 25
    if (number < 0 || number > 25) {
        cerr << "Error: INVALID_INDEX\n";
        exit(INVALID_INDEX);
    }

    // Check through all previous mapping if there has been any repeat
    for (int i=0; i<index; i++) {
        if (connections[i][1] == number) {
            cerr << "Error: INVALID_ROTOR_MAPPING\n";
            exit(INVALID_ROTOR_MAPPING);
        }
    }

    connections[index][1] = number;
}

// Function to receive the corresponding mapping of input
void Rotor::getConnection(int &number)
{
    for (int i=0; i<26; i++) {
        if (connections[i][0] == number) number = connections[i][1];
    }
}

// Function to print out mapping of inputs
void Rotor::printConnections()
{
    cout << "The Rotor connections are: \n";
    for (int i=0; i<26; i++) {
        // Output the ASCII equivalent of the letter, and show what number is it mapped to
        cout << (char) (connections[i][0] + 65) << " -> " 
            << connections[i][1] << " (" << (char) (connections[i][1] + 65) << ")" << endl;
    }
}

/* Function Definitions */
/* Void function to receive configuration files and output the content into output.txt */
void receiveConfigurationFiles(int argc, char** argv) 
{
    // There needs to be at least 4 parameters (including executable file) when there are no rotors.
    if (argc <= 3) {
        cerr << "Error: INSUFFICIENT_NUMBER_OF_PARAMETERS!\n";
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    ofstream out;
    out.open("output.txt");

    for (int i=1; i < argc; ++i) {
        string word;
        int index=0;
        int values[30];
        ifstream in;
        in.open(argv[i]);

        // Error opening configuration file
        if (!in)
        {
            cerr << "Error: ERROR_OPENING_CONFIGURATION_FILE!\n";
            exit(ERROR_OPENING_CONFIGURATION_FILE);
        }


        // If current file is for plugboards
        if (regex_match(*(argv+i), regex("plugboards/[A-Z]+.pb"))) {
            auto plugboard = Plugboard();

            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Erorr: NON_NUMERIC_CHARACTER\n";
                    exit(NON_NUMERIC_CHARACTER);
                }

                out << word;
                values[index] = stoi(word);
                word.clear();
                index ++;
            }

            out << endl;

            // Check if there are odd number of numbers for plugboard
            if (index % 2 != 0) {
                cerr << "Error: INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS\n";
                exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
            }

            // Create connections using values obtained for plugboard
            for (int i=0; i<index-1; i+=2) {
                plugboard.setConnection(values[i], values[i+1]);
            }

            plugboard.printConnections();
        }

        // If current file is for reflectors
        else if (regex_match(*(argv+i), regex("reflectors/[A-Z]+.rf"))) {
            auto reflector = Reflector();
            
            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Erorr: NON_NUMERIC_CHARACTER\n";
                    exit(NON_NUMERIC_CHARACTER);
                }

                out << word;
                values[index] = stoi(word);
                word.clear();
                index ++;
            }
            out << endl;

            // Check that there are exactly 13 pairs of numbers
            if (index != 26) {
                cerr << "Error: INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS\n";
                exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
            }

            // Create connections using values obtained for reflector
            for (int i=0; i<25; i+=2) {
                reflector.setConnection(values[i], values[i+1]);
            }

            reflector.printConnections();
        }

        // If current file is for rotors (.rot)
        else if (regex_match(*(argv+i), regex("rotors/[A-Z]+.rot"))) {
            while (in >> word) {
                out << word;
                word.clear();
            }
            out << endl;
        }

        // If current file is for rotors (.pos)
        else if (regex_match(*(argv+i), regex("rotors/[A-Z]+.pos"))) {
            while (in >> word) {
                out << word;
                word.clear();
            }
            out << endl;
        }

        else {
            // Unknown file type
            cout << "Unknown file type: " << *(argv+i) << endl;
            cerr << "Error: ERROR_OPENING_CONFIGURATION_FILE!\n";
            exit(ERROR_OPENING_CONFIGURATION_FILE);
        }
        in.close();
    }
    out.close();
}

bool isNumber(const std::string &word)
{
    for (char const &c : word) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void checkPlugBoardNumbers() {

}

void checkRotorNumbers() {
    
}

void encryptMessage(char* message)
{
    cout << "Your encrypted/decrypted message is: " << message << endl;
}