#ifndef _KEY_CPP
#define _KEY_CPP

#include <iostream>
#include "Key.h"

// Define parallel arrays of bit masks and shift amounts used to permute the 10 bit key

class BitMasks {
public:
    static const int masks[];
};

const int BitMasks::masks[] = {0x000, 0x200, 0x100, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};


class PermuteTenShifts {
public:
    static const int shifts[];
};

const int PermuteTenShifts::shifts[] = {0, 6, 1, -2, 1, -4, -3, 1, -2, -1, -4};

Key::Key(unsigned int seed) {

    if (seed < 1023) { //input must be less than 10 bits
        keyInput = seed;
        generateSubKeys();
    } else {
        throw "Input out of range error";
    }

}

unsigned int Key::getKeyOne() {

    return keyOne;

}

unsigned int Key::getKeyTwo() {

    return keyTwo;

}

void Key::generateSubKeys() {

    permuteTen();

}

void Key::permuteTen() {

    unsigned int firstPermutaion = 0;
    unsigned int temp = keyInput;
    for (int i = 0; i < 11; i++) {
        temp = keyInput & BitMasks::masks[i];
        if (PermuteTenShifts::shifts[i] > 0)
            temp = temp >> PermuteTenShifts::shifts[i];
        else
            temp = temp << -(PermuteTenShifts::shifts[i]);
        firstPermutaion = firstPermutaion | temp;
    }

    std::cout << "The result of P10 is: " << firstPermutaion << std::endl;

}

#endif
