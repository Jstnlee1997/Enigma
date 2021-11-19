// Header file "plugboard.h"

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

/* Plugboard Class */
class Plugboard{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    int setConnection(const int first, const int second);
    void getConnection(int &number);
    void printConnections();
};

#endif