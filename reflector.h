// Header file "reflector.h"

#ifndef REFLECTOR_H
#define REFLECTOR_H

/* Reflector Class */
class Reflector{
    int connections[13][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

public:
    int setConnection(const int first, const int second);
    void getConnection(int &number);
    void printConnections();
};

#endif