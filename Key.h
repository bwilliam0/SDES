#ifndef _KEY_H
#define _KEY_H

#include <iostream>
#include <bitset>

class Key {

public:

    Key(unsigned int seed);
    unsigned int getKeyOne();
    unsigned int getKeyTwo();

private:

    unsigned int keyInput;
    unsigned int key10bit;
    unsigned int keyOne;
    unsigned int keyTwo;
    void generateSubKeys();
    void permuteTen();


};


#endif
