#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <strings.h>
#include <regex>
#include <algorithm>
#include "enigma.h"
#include "errors.h"

using namespace std;

/* Class Functions */

/* Plugboard Class Functions */
// Void function to create a connection between two characters
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

// Void function to receive the corresponding connection if the connection exists
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

// Void function to print out connections to see existing connections
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
// Void function to create a connection between two characters
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

// Void function to receive the corresponding connection if the connection exists
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

// Void function to print out connections to see existing connections
void Reflector::printConnections()
{
    cout << "The Reflector connections are: \n";
    for (int i=0; i<13; i++) {
        // Print out connections
        cout << connections[i][0] << "<->" << connections[i][1] << endl;
    }
}

/* Rotor Class Functions */
// Void function to map current number to its corresponding letter
void Rotor::setConnection(int number, int index) {
    // If number is not between 0 and 25
    if (number < 0 || number > 25) {
        cerr << "Error: INVALID_INDEX\n";
        exit(INVALID_INDEX);
    }

    // Check through all previous mapping if there has been any repeat
    for (int i=0; i<index; i++) {
        if (connections[i] == number) {
            cout << "current index is: " << i << " and number is: " << number << endl;
            cerr << "Error: INVALID_ROTOR_MAPPING\n";
            exit(INVALID_ROTOR_MAPPING);
        }
    }

    connections[index] = number;
}

// Void function to receive the corresponding mapping of input in the FORWARD direction
void Rotor::getForwardConnection(int &number)
{
    number = connections[number];
}

// Void function to receive the corresponding mapping of input in the BACKWARD direction
void Rotor::getBackwardConnection(int &number)
{
    // Loop through each connection to find corresponding backwards mapping
    for (int i=0; i<26; i++) {
        if (connections[i] == number) {
            number = i;
            break;
        }
    }
}

// Void function to print out mapping of inputs
void Rotor::printConnections()
{
    cout << "The Rotor connections are: \n";
    for (int i=0; i<26; i++) {
        // Output the ASCII equivalent of the letter, and show what number is it mapped to
        cout << i << " (" << (char) (i + 65) << ") -> " 
            << connections[i] << " (" << (char) (connections[i] + 65) << ")" << endl;
    }
}

// Void function to record where are the notches on current rotor
void Rotor::setNotch(int number)
{
    // If number is not between 0 and 25
    if (number < 0 || number > 25) {
        cerr << "Error: INVALID_INDEX\n";
        exit(INVALID_INDEX);
    }
    // Notches has 26 elements, change value of element at where a notch is present
    notches[number] = 1;
}

// Boolean function to check if current rotor position has a notch
bool Rotor::getNotch()
{
    if (notches[pos] == 1) return true;
    return false;
}

// Void function to output the notches for the particular rotor
void Rotor::printNotches()
{
    cout << "Notches present are: " << endl;
    for (int i=0; i<26; i++) {
        if (notches[i] == 1) cout << i << " (" << (char) (i+65) << ")" << endl;
    }
}

// Void function to set the intiial position of the rotor
void Rotor::setInitialPosition(int number){
    // If number is not between 0 and 25
    if (number < 0 || number > 25) {
        cerr << "Error: INVALID_INDEX\n";
        exit(INVALID_INDEX);
    }
    pos = number;
}

// Void function to rotate position of the motor
void Rotor::rotate()
{
    // cout << "Rotor has rotated from postion: " << pos << " to position: ";
    pos++;
    if (pos > 25) pos = 0;
    // cout << pos << endl;
}

// Void function to output current position of the rotor
int Rotor::getPosition()
{
    return pos;
}

/* Function Definitions */
/* Void function to receive configuration files and output the content into output.txt */
void receiveConfigurationFiles(int argc, char** argv, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors)
{
    int numberOfRotors = 0;
    int numberOfStartingPositions=0;
    ofstream out;
    out.open("output.txt");

    // There needs to be at least 4 parameters (including executable file) when there are no rotors.
    if (argc <= 3) {
        cerr << "Error: INSUFFICIENT_NUMBER_OF_PARAMETERS!\n";
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

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

            // plugboard.printConnections();
        }

        // If current file is for reflectors
        else if (regex_match(*(argv+i), regex("reflectors/[A-Z]+.rf"))) {
            
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

            // reflector.printConnections();
        }

        // If current file is for rotors (.rot)
        else if (regex_match(*(argv+i), regex("rotors/[A-Z]+.rot"))) {
            numberOfRotors ++;
            Rotor *r1 = new Rotor();

            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Erorr: NON_NUMERIC_CHARACTER\n";
                    exit(NON_NUMERIC_CHARACTER);
                }
                if (index < 26) {
                    r1->setConnection(stoi(word), index);
                    out << word;
                    word.clear();
                    index ++;
                }
                else {
                    r1->setNotch(stoi(word));
                    out << word;
                    word.clear();
                }
            }
            out << endl;

            // Check that every input is provided a mapping
            if (index != 26) {
                cerr << "Error: INVALID_ROTOR_MAPPING\n";
                exit(INVALID_ROTOR_MAPPING);
            }

            // r1->printConnections();
            // r1->printNotches();

            // Add current rotor to vector of rotors
            rotors.push_back(*r1);
        }

        // If current file is for rotors (.pos)
        else if (regex_match(*(argv+i), regex("rotors/[A-Z]+.pos"))) {
            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Erorr: NON_NUMERIC_CHARACTER\n";
                    exit(NON_NUMERIC_CHARACTER);
                }
                numberOfStartingPositions ++;
                rotors[numberOfStartingPositions-1].setInitialPosition(stoi(word));
                out << word;
                word.clear();
            }
            if (numberOfStartingPositions < numberOfRotors) {
                cerr << "Error: NO_ROTOR_STARTING_POSITION\n";
                exit(NO_ROTOR_STARTING_POSITION);
            }
            out << endl;
        }

        // Unknown file type
        else {
            cout << "Unknown file type: " << *(argv+i) << endl;
            cerr << "Error: ERROR_OPENING_CONFIGURATION_FILE!\n";
            exit(ERROR_OPENING_CONFIGURATION_FILE);
        }
        in.close();
    }
    out.close();
}

/* Helper function to check if input read in from file is a number */
bool isNumber(const std::string &word)
{
    for (char const &c : word) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void encryptMessage(std::string message, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors)
{
    // Remove whitespaces from message
    message.erase(remove_if(message.begin(), message.end(), ::isspace), message.end());

    // Get the number of rotors
    int numberOfRotors = rotors.size();

    // Encrypt/Decrypt every message
    for (char &c : message) {
        // Only take in CAPITAL letters
        if (c < 'A' || c > 'Z') {
            cerr << "Error: INVALID_INPUT_CHARACTER\n";
            exit(INVALID_INPUT_CHARACTER);
        }

        int number = (int) c - 65;

        // Pass number through the plugbloard
        plugboard.getConnection(number);

        // Rotate all rotors starting from right most rotor
        for (int r_index = numberOfRotors-1; r_index>=0; r_index--) {
            // Rotate current rotor
            rotors[r_index].rotate();

            // Only rotate next rotor if current one hits a notch
            if (!rotors[r_index].getNotch()) {
                break;
            }
        }

        // Pass number through all the rotors starting from RIGHT
        for (int r_index = numberOfRotors-1; r_index>=0; r_index--) {
            cout << "Connections for current rotor are: " << endl;
            rotors[r_index].printConnections();

            cout << "Current rotor index is " << r_index << endl;

            // Change number accordingly depending on current rotor position
            cout << "Current position of rotor is at: " << rotors[r_index].getPosition() << endl;
            cout << "Number is currently: " << number << endl;
            changeNumberAccordingToRotorPosition(number, rotors[r_index].getPosition());
            cout << "Number is now after changing according to rotor position: " << number << endl;

            // Change number according to the respective mapping
            rotors[r_index].getForwardConnection(number);
            cout << "After mapping, the number is now: " << number << endl;
        } 

        // Pass number through the reflector
        reflector.getConnection(number);
        cout << "After reflection, the number is now: " << number << endl;

        // Pass number through all the rotors again but starting from the LEFT
        for (int r_index = 0; r_index < numberOfRotors; r_index++) {
            cout << "Connections for current rotor are: " << endl;
            rotors[r_index].printConnections();

            cout << "Current rotor index is " << r_index << endl;

            // Change number accordingly depending on current rotor position
            cout << "Current position of rotor is at: " << rotors[r_index].getPosition() << endl;
            cout << "Number is currently: " << number << endl;
            changeNumberAccordingToRotorPosition(number, rotors[r_index].getPosition());
            cout << "Number is now after changing according to rotor position: " << number << endl;

            // Change number according to the respective mapping
            rotors[r_index].getBackwardConnection(number);
            cout << "After mapping, the number is now: " << number << endl;
        }

        // Pass number through the plugbloard
        plugboard.getConnection(number);

        cout << "Initial letter: " << c << " has been encrypted/decrypted to letter: ";

        c = (char) (number + 65);

        cout << c << endl;
    }

    cout << "Your encrypted/decrypted message is: " << message << endl;
}

void changeNumberAccordingToRotorPosition(int &number, const int pos)
{
    number += pos;
    if (number > 25) number -= 26;
}