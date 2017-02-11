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

    static const int masks[];
    static const int pTenShifts[];
    static const int rightBitMask = 0x1F;
    static const int leftBitMask = 0x3E0;
    unsigned int keyInput;
    unsigned int key10bit;
    unsigned int keyOne;
    unsigned int keyTwo;
    void generateSubKeys();
    void permuteTen();
    void leftShiftOne();


};


#endif
