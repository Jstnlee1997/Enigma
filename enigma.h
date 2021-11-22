// Header file "enigma.h"

#ifndef ENIGMA_H
#define ENIGMA_H

#include "src/plugboard.h"
#include "src/reflector.h"
#include "src/rotor.h"

///////////////////////////////
///* FUNCTION DECLARATIONS *///
///////////////////////////////

int receiveConfigurationFiles(int argc, char **argv, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors);
bool isNumber(const std::string &word);
int encryptMessage(std::string message, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors);
void rotateAllRotors(const int numberOfRotors, std::vector<Rotor> &rotors);
void passThroughRotorsFromRight(int &number, const int numberOfRotors, std::vector<Rotor> &rotors);
void passThroughRotorsFromLeft(int &number, const int numberOfRotors, std::vector<Rotor> &rotors);
void changeInputAccordingToRotorPosition(int &number, const int pos);
void changeOutputAccordingToRotorPosition(int &number, const int pos);

#endif