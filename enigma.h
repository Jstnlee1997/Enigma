// Header file "enigma.h"

#ifndef ENIGMA_H

/* Classes Definitions */

// Plugboard Class
class Plugboard{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    void setConnection(int first, int second);
    void getConnection(int &first);
    void printConnections();
};

class Reflector{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    void setConnection(int first, int second);
    void getConnection(int &first);
    void printConnections();
};


/* Function Declarations */

void receiveConfigurationFiles(int argc, char** argv);
void encryptMessage(char* message);

#define ENIGMA_H
#endif