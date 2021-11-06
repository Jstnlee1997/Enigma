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

    // Receive configuration files
    receiveConfigurationFiles(argc, argv, plugboard, reflector, rotors);

    // Prompt user to send a message to be encrypted/decrypted
    // cout << "What message would you like to encrypt/decrypt?\n"
    //     << "Please make sure your message is in CAPITAL letters only.\n";
    getline(cin, message);

    // Encrypt/Decrypt message if possible, and output to standard output stream
    encryptMessage(message, plugboard, reflector, rotors);

    return NO_ERROR;
}