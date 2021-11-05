// Header file "enigma.h"

#ifndef ENIGMA_H

/* Classes Definitions */

// Plugboard Class
class Plugboard{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    void setConnection(int first, int second);
    void getConnection(int &number);
    void printConnections();
};

class Reflector{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    void setConnection(int first, int second);
    void getConnection(int &number);
    void printConnections();
};

class Rotor{
    int connections[26][2] = {{0,-1},{1,-1},{2,-1},{3,-1},{4,-1},{5,-1},{6,-1},{7,-1},{8,-1},{9,-1},{10,-1},
                                {11,-1},{12,-1},{13,-1},{14,-1},{15,-1},{16,-1},{17,-1},{18,-1},{19,-1},{20,-1},
                                {21,-1},{22,-1},{23,-1},{24,-1},{25,-1}};
    int notches[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

public:
    int pos=0;
    void setConnection(int number, int index);
    void getConnection(int &number);
    void printConnections();
    void setNotch(int number);
    bool getNotch(int number);
    void printNotches();
    void setInitialPosition(int number);
};

/* Function Declarations */

void receiveConfigurationFiles(int argc, char** argv);
bool isNumber(const std::string &word);
void encryptMessage(char* message);

#define ENIGMA_H
#endif