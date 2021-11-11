#include <iostream>
#include "helper.h"
#include "errors.h"

using namespace std;

/////////////////////////
///* CLASS FUNCTIONS *///
/////////////////////////

/* Plugboard Class Functions */

// Void function to create a connection between two characters
int Plugboard::setConnection(const int first, const int second)
{
    // If first number is not between 0 and 25
    if (first < 0 || first > 25) {
        cerr << "Invalid index given in plugboard file for mapping of number: " << first << endl;
        return(INVALID_INDEX);
    }

    // If second number is not between 0 and 25
    if (second < 0 || second > 25) {
        cerr << "Invalid index given in plugboard file for mapping of number: " << second << endl;
        return(INVALID_INDEX);
    }

    // If file attempts to connect a contact with itself
    if (first == second) {
        cerr << "Invalid index given for mapping of two identical numbers: " << first << endl;
        return(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }


    int i=0;
    for (; i<13; i++) {
        // Reached an empty slot in connections to create a new connection
        if (connections[i][0] == -1) break;

        // Check if first number already has existing connections
        if (connections[i][0] == first || connections[i][1] == first) {
            cerr << "Invalid plugboard mapping as there are repeats of mapping of number: " << first << endl;
            return(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }
        // Check if second number already has existing connections
        if (connections[i][0] == second || connections[i][1] == second) {
            cerr << "Invalid plugboard mapping as there are repeats of mapping of number: " << second << endl;
            return(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }
    }

    // If it reaches here, can create new connection
    connections[i][0] = first;
    connections[i][1] = second;

    return NO_ERROR;
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
int Reflector::setConnection(const int first, const int second)
{
    // If first number is not between 0 and 25
    if (first < 0 || first > 25) {
        cerr << "Invalid index given in reflector file for mapping of number: " << first << endl;
        return(INVALID_INDEX);
    }

    // If second number is not between 0 and 25
    if (second < 0 || second > 25) {
        cerr << "Invalid index given in reflector file for mapping of number: " << second << endl;
        return(INVALID_INDEX);
    }

    // If file attempts to connect a contact with itself
    if (first == second) {
        cerr << "Invalid index given for mapping of two identical numbers: " << first << endl;
        return(INVALID_REFLECTOR_MAPPING);
    }


    int i=0;
    for (; i<13; i++) {
        // Reached an empty slot in connections to create a new connection
        if (connections[i][0] == -1) break;

        // Check if first number already has existing connections
        if (connections[i][0] == first || connections[i][1] == first) {
            cerr << "Invalid reflector mapping as there are repeats of mapping of number: " << first << endl;
            return(INVALID_REFLECTOR_MAPPING);
        }
        // Check if second number already has existing connections
        if (connections[i][0] == second || connections[i][1] == second) {
            cerr << "Invalid reflector mapping as there are repeats of mapping of number: " << second << endl;
            return(INVALID_REFLECTOR_MAPPING);
        }
    }

    // If it reaches here, can create new connection
    connections[i][0] = first;
    connections[i][1] = second;

    return NO_ERROR;
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
int Rotor::setConnection(const int number, const int index) {
    // If number is not between 0 and 25
    if (number < 0 || number > 25) {
        cerr << "Invalid index given for mapping of input " << index << " to output " << number << endl;
        return(INVALID_INDEX);
    }

    // Check through all previous mapping if there has been any repeat
    for (int i=0; i<index; i++) {
        if (connections[i] == number) {
            cerr << "Invalid mapping of input " << index << " to output " << number << " (output " << number << " is already mapped to from input " << i << ")";
            return(INVALID_ROTOR_MAPPING);
        }
    }

    // No error, map number to input
    connections[index] = number;

    return NO_ERROR;
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
int Rotor::setNotch(const int number)
{
    // If number is not between 0 and 25
    if (number < 0 || number > 25) {
        cerr << "Invalid index given for notch: " << number << endl;
        return(INVALID_INDEX);
    }

    // Notches has 26 elements, change value of element at where a notch is present
    notches[number] = 1;

    return NO_ERROR;
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
int Rotor::setInitialPosition(const int number){
    // If number is not between 0 and 25
    if (number < 0 || number > 25) {
        cerr << "Invalid index given for initial rotor position: " << number << endl;
        return(INVALID_INDEX);
    }

    // No error, set initial position of rotor to number
    pos = number;

    return NO_ERROR;
}

// Void function to rotate position of the motor
void Rotor::rotate()
{
    pos++;
    if (pos > 25) pos = 0;
}

// Void function to output current position of the rotor
int Rotor::getPosition()
{
    return pos;
}
