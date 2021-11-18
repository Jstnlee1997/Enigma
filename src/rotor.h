// Header file "rotor.h"

#ifndef ROTOR_H
#define ROTOR_H

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

#endif