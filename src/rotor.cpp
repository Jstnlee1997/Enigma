#include <iostream>
#include "rotor.h"
#include "../errors.h"

using namespace std;

///////////////////////////////
///* ROTOR CLASS FUNCTIONS *///
///////////////////////////////

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