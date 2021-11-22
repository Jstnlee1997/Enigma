#include <iostream>
#include "reflector.h"
#include "../errors.h"

using namespace std;

///////////////////////////////////
///* REFLECTOR CLASS FUNCTIONS *///
///////////////////////////////////

// Void function to create a connection between two characters
int Reflector::setConnection(const int first, const int second)
{
    // If first number is not between 0 and 25
    if (first < 0 || first > 25)
    {
        cerr << "Invalid index given in reflector file for mapping of number: " << first << endl;
        return (INVALID_INDEX);
    }

    // If second number is not between 0 and 25
    if (second < 0 || second > 25)
    {
        cerr << "Invalid index given in reflector file for mapping of number: " << second << endl;
        return (INVALID_INDEX);
    }

    // If file attempts to connect a contact with itself
    if (first == second)
    {
        cerr << "Invalid index given for mapping of two identical numbers: " << first << endl;
        return (INVALID_REFLECTOR_MAPPING);
    }

    int i = 0;
    for (; i < 13; i++)
    {
        // Reached an empty slot in connections to create a new connection
        if (connections[i][0] == -1)
            break;

        // Check if first number already has existing connections
        if (connections[i][0] == first || connections[i][1] == first)
        {
            cerr << "Invalid reflector mapping as there are repeats of mapping of number: " << first << endl;
            return (INVALID_REFLECTOR_MAPPING);
        }
        // Check if second number already has existing connections
        if (connections[i][0] == second || connections[i][1] == second)
        {
            cerr << "Invalid reflector mapping as there are repeats of mapping of number: " << second << endl;
            return (INVALID_REFLECTOR_MAPPING);
        }
    }

    // If it reaches here, can create new connection
    connections[i][0] = first;
    connections[i][1] = second;

    return NO_ERROR;
}

// Void function to receive the corresponding connection if the connection exists
void Reflector::getConnection(int &number)
{
    for (int i = 0; i < 13; i++)
    {
        // No established connection
        if (connections[i][0] == -1)
            break;

        // Existing connection
        if (connections[i][0] == number)
        {
            number = connections[i][1];
            break;
        }
        if (connections[i][1] == number)
        {
            number = connections[i][0];
            break;
        }
    }
}

// Void function to print out connections to see existing connections
void Reflector::printConnections()
{
    cout << "The Reflector connections are: \n";
    for (int i = 0; i < 13; i++)
    {
        // Print out connections
        cout << connections[i][0] << "<->" << connections[i][1] << endl;
    }
}