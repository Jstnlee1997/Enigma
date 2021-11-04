#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <strings.h>
#include "errors.h"
#include "enigma.h"

const int MAX_LENTH = 255;

using namespace std;

int main(int argc, char** argv)
{
    char message[MAX_LENTH];

    // Receive configuration files
    receiveConfigurationFiles(argc, argv);

    // Prompt user to send a message to be encrypted/decrypted
    cout << "What message would you like to encrypt/decrypt?\n"
        << "Please make sure your message is in CAPITAL letters only.\n";
    cin.getline(message, MAX_LENTH);

    // Encrypt/Decrypt message if possible, and output to standard output stream
    encryptMessage(message);

    return NO_ERROR;
}