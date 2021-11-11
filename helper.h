// Header file "helper.h"

#ifndef HELPER_H
#define HELPER_H

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

#endif