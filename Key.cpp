#ifndef _KEY_CPP
#define _KEY_CPP

#include <iostream>
#include "Key.h"

// Define parallel arrays of bit masks and shift amounts used to permute the 10 bit key

const unsigned int Key::masks[] = {0x200, 0x100, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};

const int Key::pTenShifts[] = {6, 1, -2, 1, -4, -3, 1, -2, -1, -4};

const int Key::pEightShifts[] = {-3, 1, -2, 2, -1, 3, -1, 1};

const unsigned int Key::pEightMasks[] = {0x10, 0x80, 0x08, 0x40, 0x04, 0x20, 0x01, 0x02};

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
    leftShiftOne();
    keyOne = permuteEight(key10bit);

}

void Key::permuteTen() {

    unsigned int temp;
    for (int i = 0; i < 11; i++) {
        temp = keyInput & masks[i];
        if (pTenShifts[i] > 0)
            temp = temp >> pTenShifts[i];
        else
            temp = temp << -(pTenShifts[i]);
        key10bit = key10bit | temp;
    }

    std::cout << "The result of P10 is: " << key10bit << std::endl;

}

void Key::leftShiftOne() {

    unsigned int right5bits = 0;
    unsigned int left5bits = 0;

    right5bits = key10bit & rightBitMask;
    left5bits = key10bit & leftBitMask;

    right5bits = right5bits << 1;
    left5bits = left5bits << 1;

    if (left5bits & 0x400) {
        left5bits = left5bits | 0x20;
        left5bits = left5bits & leftBitMask;
    }

    if (right5bits & 0x20) {
        right5bits = right5bits | 1;
        right5bits = right5bits & rightBitMask;
    }

    key10bit = 0;
    key10bit = key10bit | right5bits;
    key10bit = key10bit | left5bits;

    std::cout << "After LS1 key10bit is: " << key10bit << std::endl;

}

int Key::permuteEight(int inputKey) {

    int outputKey = 0;
    unsigned int temp;
    for (int i = 0; i < 8; i++) {
        temp = key10bit & pEightMasks[i];
        if (pEightShifts[i] > 0)
            temp = temp >> pEightShifts[i];
        else
            temp = temp << -pEightShifts[i];
        outputKey = outputKey | temp;
    }

    std::cout << "The result of P8 is: " << outputKey << std::endl;

}

#endif
