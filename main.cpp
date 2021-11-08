#include <iostream>
#include <fstream>
#include <cstdio>
#include <strings.h>
#include <vector>
#include "errors.h"
#include "enigma.h"

using namespace std;

int main(int argc, char** argv)
{
    Plugboard plugboard;
    Reflector reflector;
    vector<Rotor> rotors;
    string message;
    int result = 0;

    /* Receive configuration files
    - Output will be non-zero if errors are present 
    */
    result = receiveConfigurationFiles(argc, argv, plugboard, reflector, rotors);
    if (result != 0) return result;

    // Prompt user to send a message to be encrypted/decrypted
    // cout << "What message would you like to encrypt/decrypt?\n"
    //     << "Please make sure your message is in CAPITAL letters only.\n";
    getline(cin, message);

    /* Encrypt/Decrypt message if possible 
    - Each character will be encrypted and output to standard output stream
    - Program will exit immediately if it faces any errors 
    - Output will be non-zero if errors are present
    */

    result = encryptMessage(message, plugboard, reflector, rotors);
    if (result != 0) return result;

    return 0;
}