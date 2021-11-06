// Header file "enigma.h"

#ifndef ENIGMA_H

///////////////////////////
///* CLASS DEFINITIONS *///
///////////////////////////

/* Plugboard Class */
class Plugboard{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    void setConnection(int first, int second);
    void getConnection(int &number);
    void printConnections();
};

/* Reflector Class */
class Reflector{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    void setConnection(int first, int second);
    void getConnection(int &number);
    void printConnections();
};

/* Rotor Class */
class Rotor{
    int pos=0;
    int connections[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int notches[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

public:
    void setConnection(int number, int index);
    void getForwardConnection(int &number);
    void getBackwardConnection(int &number);
    void printConnections();
    void setNotch(int number);
    bool getNotch();
    void printNotches();
    void setInitialPosition(int number);
    void rotate();
    int getPosition();
};

///////////////////////////////
///* FUNCTION DECLARATIONS *///
///////////////////////////////

void receiveConfigurationFiles(int argc, char** argv, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors);
bool isNumber(const std::string &word);
void encryptMessage(std::string message, Plugboard &plugboard, Reflector &reflector, std::vector<Rotor> &rotors);
void rotateAllRotors(const int numberOfRotors, std::vector<Rotor> &rotors);
void passThroughRotorsFromRight(int &number, const int numberOfRotors, std::vector<Rotor> &rotors);
void passThroughRotorsFromLeft(int &number, const int numberOfRotors, std::vector<Rotor> &rotors);
void changeInputAccordingToRotorPosition(int &number, const int pos);
void changeOutputAccordingToRotorPosition(int &number, const int pos);

#define ENIGMA_H
#endif