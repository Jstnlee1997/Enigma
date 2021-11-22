#include <iostream>
#include <fstream>
#include <vector>
#include <strings.h>
#include <regex>
#include "enigma.h"
#include "src/plugboard.h"
#include "src/reflector.h"
#include "src/rotor.h"
#include "errors.h"

using namespace std;

//////////////////////////////
///* FUNCTION DEFINITIONS *///
//////////////////////////////

/* Void function to receive configuration files and output the content into output.txt */
int receiveConfigurationFiles(int argc, char** argv, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors)
{
    int numberOfRotors = 0;
    int numberOfStartingPositions=0;
    int result = 0;
    ofstream out;
    out.open("output.txt");

    // There needs to be at least 4 parameters (including executable file) when there are no rotors.
    if (argc <= 3) {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
        return(INSUFFICIENT_NUMBER_OF_PARAMETERS);
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
            cerr << "There is an error opening configuration file " << *(argv+i) << endl;
            return(ERROR_OPENING_CONFIGURATION_FILE);
        }


        // If current file is for plugboards
        if (regex_match(*(argv+i), regex("[a-zA-Z0-9_/]+.pb"))) {

            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Non-numeric character in plugboard file " << *(argv+i) << endl;
                    return(NON_NUMERIC_CHARACTER);
                }

                out << word;
                values[index] = stoi(word);
                word.clear();
                index ++;
            }

            out << endl;

            // Case: Odd number of parameters provided for plugboard
            if (index % 2 != 0) {
                cerr << "Incorrect number of parameters in plugboard file " << *(argv+i) << endl;
                return(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
            }

            // Case: Too many parameters provided for plugboard
            if (index > 26) {
                cerr << "Incorrect number of parameters in plugboard file " << *(argv+i) << endl;
                return(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
            }

            // Create connections using values obtained for plugboard
            for (int i=0; i<index-1; i+=2) {
                // setConnection will output non-zero if any errors are present
                result = plugboard.setConnection(values[i], values[i+1]);
                if (result != 0) return result;
            }

            // plugboard.printConnections();
        }

        // If current file is for reflectors
        else if (regex_match(*(argv+i), regex("[a-zA-Z0-9_/]+.rf"))) {
            
            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Non-numeric character in reflector file " << *(argv+i) << endl;
                    return(NON_NUMERIC_CHARACTER);
                }

                out << word;
                values[index] = stoi(word);
                word.clear();
                index ++;
            }
            out << endl;

            // Case: Odd number of parameters provided for reflector
            if (index % 2 != 0) {
                cerr << "Incorrect (odd) number of parameters in reflector file " << *(argv+i) << endl;
                return(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
            }

            // Case: Even BUT Fewer than 26 parameters provided 
            if (index < 26) {
                cerr << "Insufficient number of mappings in reflector file: " << *(argv+i) << endl;
                return(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
            }

            // Check that there are exactly 13 pairs of numbers
            if (index != 26) {
                cerr << "Incorrect number of parameters in reflector file " << *(argv+i) << endl;
                return(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
            }

            // Create connections using values obtained for reflector
            for (int i=0; i<25; i+=2) {
                // setConnection will output non-zero if any errors are present
                result = reflector.setConnection(values[i], values[i+1]);
                if (result != 0) return result;
            }

            // reflector.printConnections();
        }

        // If current file is for rotors (.rot)
        else if (regex_match(*(argv+i), regex("[a-zA-Z0-9_/]+.rot"))) {
            numberOfRotors ++;
            Rotor *r1 = new Rotor();

            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Non-numeric character for mapping in rotor file " << *(argv+i) << endl;
                    return(NON_NUMERIC_CHARACTER);
                }
                if (index < 26) {
                    // setConnection will output non-zero if any errors are present
                    result = r1->setConnection(stoi(word), index);
                    if (result == INVALID_ROTOR_MAPPING) {
                        cerr << " in rotor file: " << *(argv+i) << endl;
                        return result;
                    }
                    if (result != 0) return result;
                    out << word;
                    word.clear();
                    index ++;
                }
                else {
                    // setNotch will output non-zero if any errors are present
                    result = r1->setNotch(stoi(word));
                    if (result != 0) return result;
                    out << word;
                    word.clear();
                }
            }
            out << endl;

            // Check that every input is provided a mapping
            if (index != 26) {
                cerr << "Not all inputs mapped in rotor file: " << *(argv+i) << endl;
                return(INVALID_ROTOR_MAPPING);
            }

            // r1->printConnections();
            // r1->printNotches();

            // Add current rotor to vector of rotors
            rotors.push_back(*r1);
        }

        // If current file is for rotors (.pos)
        else if (regex_match(*(argv+i), regex("[a-zA-Z0-9_/]+.pos"))) {
            if (numberOfRotors == 0) break;
            while (in >> word) {
                // check if current word is non-numeric
                if (!isNumber(word)) {
                    cerr << "Non-numeric character in rotor positions file " << *(argv+i) << endl;
                    return(NON_NUMERIC_CHARACTER);
                }
                numberOfStartingPositions ++;
                // setInitialPosition will output non-zero if any errors are present
                result = rotors[numberOfStartingPositions-1].setInitialPosition(stoi(word));
                if (result != 0) return result;
                out << word;
                word.clear();
            }
            if (numberOfStartingPositions < numberOfRotors) {
                cerr << "No starting position for rotor " << numberOfStartingPositions << " in rotor position file: " << *(argv+i) << endl;
                return(NO_ROTOR_STARTING_POSITION);
            }
            out << endl;

            // This has to be the final file
            break;
        }

        // Unknown file type
        else {
            cerr << "Unacceptable or unknown file type for configuration file " << *(argv+i) << endl;
            return(ERROR_OPENING_CONFIGURATION_FILE);
        }
        in.close();
    }
    out.close();

    return NO_ERROR;
}

/* Helper Boolean function to check if input read in from file is a number */
bool isNumber(const std::string &word)
{
    for (char const &c : word) {
        if (!isdigit(c)) return false;
    }
    return true;
}

/* Void function to encrypt each character of the message
Each character goes through the following components where they are changed accordingly:
    1. Plugboard
    2. Through every rotor from Right -> Left
    3. Reflector
    4. Through every rotor from Left -> Right
    5. Plugboard
*/
int encryptMessage(std::string message, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors)
{
    // Remove whitespaces from message
    message.erase(remove_if(message.begin(), message.end(), ::isspace), message.end());

    // Get the number of rotors
    int numberOfRotors = rotors.size();

    // Encrypt/Decrypt every letter
    for (char &c : message) {
        // Only take in CAPITAL letters
        if (c < 'A' || c > 'Z') {
            cerr << endl; cerr << c << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
            return(INVALID_INPUT_CHARACTER);
        }

        int number = (int) (c - 'A');

        // Pass number through the plugbloard
        plugboard.getConnection(number);

        // Rotate all rotors starting from right most rotor
        rotateAllRotors(numberOfRotors, rotors);

        // Pass number through all the rotors starting from RIGHT
        passThroughRotorsFromRight(number, numberOfRotors, rotors);

        // Pass number through the reflector
        reflector.getConnection(number);
        // cout << "After reflection, the number is now: " << number << endl;

        // Pass number through all the rotors again but starting from the LEFT
        passThroughRotorsFromLeft(number, numberOfRotors, rotors);

        // Pass number through the plugbloard
        plugboard.getConnection(number);

        // cout << "Initial letter: " << c << " has been encrypted/decrypted to letter: ";

        c = (char) (number + 'A');

        cout << c;
    }

    cout << endl;

    return NO_ERROR;
}

/* Void function to rotate all rotors */
void rotateAllRotors(const int numberOfRotors, std::vector<Rotor> &rotors)
{
    for (int r_index = numberOfRotors-1; r_index>=0; r_index--) {
        // Rotate current rotor
        rotors[r_index].rotate();

        // Only rotate next rotor if current one hits a notch
        if (!rotors[r_index].getNotch()) {
            break;
        }
    }
}

/* Void function to pass number through each rotor from RIGHT -> LEFT */
void passThroughRotorsFromRight(int &number, const int numberOfRotors, std::vector<Rotor> &rotors)
{
    for (int r_index = numberOfRotors-1; r_index>=0; r_index--) {
        // cout << "Connections for current rotor are: " << endl;
        // rotors[r_index].printConnections();

        // cout << "Current rotor index is " << r_index << endl;

        // Change input number accordingly depending on current rotor position
        // cout << "Current position of rotor is at: " << rotors[r_index].getPosition() << endl;
        // cout << "Number is currently: " << number << endl;
        changeInputAccordingToRotorPosition(number, rotors[r_index].getPosition());
        // cout << "Number is now after changing intput according to rotor position: " << number << endl;

        // Change number according to the respective mapping
        rotors[r_index].getForwardConnection(number);
        // cout << "After mapping, the number is now: " << number << endl;

        // Change output number accordingly depending on current rotor position
        changeOutputAccordingToRotorPosition(number, rotors[r_index].getPosition());
        // cout << "Number is now after changing output according to rotor position: " << number << endl;

    } 
}

/* Void function to pass number through each rotor from LEFT -> RIGHT */
void passThroughRotorsFromLeft(int &number, const int numberOfRotors, std::vector<Rotor> &rotors)
{
    for (int r_index = 0; r_index < numberOfRotors; r_index++) {
        // cout << "Connections for current rotor are: " << endl;
        // rotors[r_index].printConnections();

        // cout << "Current rotor index is " << r_index << endl;

        // Change number accordingly depending on current rotor position
        // cout << "Current position of rotor is at: " << rotors[r_index].getPosition() << endl;
        // cout << "Number is currently: " << number << endl;
        changeInputAccordingToRotorPosition(number, rotors[r_index].getPosition());
        // cout << "Number is now after changing according to rotor position: " << number << endl;

        // Change number according to the respective mapping
        rotors[r_index].getBackwardConnection(number);
        // cout << "After mapping, the number is now: " << number << endl;

        // Change output number accordingly depending on current rotor position
        changeOutputAccordingToRotorPosition(number, rotors[r_index].getPosition());
        // cout << "Number is now after changing output according to rotor position: " << number << endl;
    }
}

/* Void function to change the input number into the current rotor depending on the relative position of the rotor */
void changeInputAccordingToRotorPosition(int &number, const int pos)
{
    number += pos;
    if (number > 25) number -= 26;
}

/* Void function to change the output number out of the current rotor depending on the relative position of the rotor */
void changeOutputAccordingToRotorPosition(int &number, const int pos)
{
    number -= pos;
    if (number < 0) number += 26;
}