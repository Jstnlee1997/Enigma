// Header file "enigma.h"

#ifndef ENIGMA_H

///////////////////////////
///* CLASS DEFINITIONS *///
///////////////////////////

/* Plugboard Class */
class Plugboard{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    int setConnection(const int first, const int second);
    void getConnection(int &number);
    void printConnections();
};

/* Reflector Class */
class Reflector{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    int setConnection(const int first, const int second);
    void getConnection(int &number);
    void printConnections();
};

/* Rotor Class */
class Rotor{
    int pos=0;
    int connections[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int notches[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

public:
    int setConnection(const int number, const int index);
    void getForwardConnection(int &number);
    void getBackwardConnection(int &number);
    void printConnections();
    int setNotch(const int number);
    bool getNotch();
    void printNotches();
    int setInitialPosition(const int number);
    void rotate();
    int getPosition();
};

///////////////////////////////
///* FUNCTION DECLARATIONS *///
///////////////////////////////

int receiveConfigurationFiles(int argc, char** argv, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors);
bool isNumber(const std::string &word);
int encryptMessage(std::string message, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors);
void rotateAllRotors(const int numberOfRotors, std::vector<Rotor> &rotors);
void passThroughRotorsFromRight(int &number, const int numberOfRotors, std::vector<Rotor> &rotors);
void passThroughRotorsFromLeft(int &number, const int numberOfRotors, std::vector<Rotor> &rotors);
void changeInputAccordingToRotorPosition(int &number, const int pos);
void changeOutputAccordingToRotorPosition(int &number, const int pos);

#define ENIGMA_H
#endif