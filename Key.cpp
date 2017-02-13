#ifndef _KEY_CPP
#define _KEY_CPP

#include <iostream>
#include <bitset>
#include "Key.h"

// Define parallel arrays of bit masks and shift amounts used to permute the 10 and 8 bit key
// Negative shift amounts will perform a left shift, positive amounts a right shift
const unsigned int Key::masks[] = {512, 256, 128, 64, 32, 16, 8, 4, 2, 1};

const int Key::pTenShifts[] = {6, 1, -2, 1, -3, 4, -3, 1, -1, -4};

const int Key::pEightShifts[] = {-3, 1, -2, 2, -1, 3, -1, 1};

const unsigned int Key::pEightMasks[] = {0x10, 0x80, 0x08, 0x40, 0x04, 0x20, 0x01, 0x02};

/**
 * @brief Constructs a Key object and generates both subkeys
 *
 * @param seed A ten bit integer that will be used to generate both of the subkeys
 */
Key::Key(unsigned int seed) {

    if (seed <= KEY_MAX_SIZE) { //input must be less than 10 bits
        keyInput = seed;
        generateSubKeys();
    } else {
        throw std::out_of_range("Seed to large");
    }

}

/**
 *
 * @return A bitset of the first subkey
 */
std::bitset<Key::SUBKEY_SIZE> Key::getKeyOne() {

    return std::bitset<SUBKEY_SIZE>(keyOne);

}

/**
 *
 * @return A bitset of the second subkey
 */
std::bitset<Key::SUBKEY_SIZE> Key::getKeyTwo() {

    return std::bitset<SUBKEY_SIZE>(keyTwo);

}

/**
 * @brief Generates both of the subkeys for simple DES
 */
void Key::generateSubKeys() {

    permuteTen();
    leftShiftOne();
    keyOne = permuteEight(key10bit);
    leftShiftOne();
    leftShiftOne();
    keyTwo = permuteEight(key10bit);

}

/**
 * @brief Performs the P10 operation which rearranges the bits in the input key
 */
void Key::permuteTen() {

    unsigned int temp;
    for (int i = 0; i <= KEY_SIZE; i++) {
        temp = keyInput & masks[i];     // pick out the next bit from the original key
        if (pTenShifts[i] > 0)          // check which direction the shift is
            temp = temp >> pTenShifts[i];   // perform the shift
        else
            temp = temp << -(pTenShifts[i]);
        key10bit = key10bit | temp;     // place the bit into the new key
    }

    //std::cout << "The result of P10 is: " << key10bit << std::endl;

}

/**
 * @brief Rotates the right 5 bits, and the left 5 bits of the 10 bit permuted key
 */
void Key::leftShiftOne() {

    unsigned int right5bits = 0;
    unsigned int left5bits = 0;

    right5bits = key10bit & RIGHT_BIT_MASK;     // assign each variable the proper bits
    left5bits = key10bit & LEFT_BIT_MASK;

    right5bits = right5bits << 1;               // shift each by one
    left5bits = left5bits << 1;

    if (left5bits & 0x400) {// Test if MSB was a one, and if it was place a one in the LSB
        left5bits = left5bits | 0x20;
        left5bits = left5bits & LEFT_BIT_MASK;
    }

    if (right5bits & 0x20) {// Test if MSB was a one, and if it was place a one in the LSB
        right5bits = right5bits | 1;
        right5bits = right5bits & RIGHT_BIT_MASK;
    }

    key10bit = 0;           // Output the key
    key10bit = key10bit | right5bits;
    key10bit = key10bit | left5bits;

    //std::cout << "After LS1 key10bit is: " << key10bit << std::endl;

}

/**
 *
 * @param inputKey The 10 bit key that you want to generate an 8 bit subkey from
 * @return The 8 bit subkey generated by the ten bit key
 */
unsigned int Key::permuteEight(unsigned int inputKey) {

    int outputKey = 0;
    unsigned int temp;
    for (int i = 0; i < 8; i++) {
        temp = key10bit & pEightMasks[i];   // pick out the next bit from the original key
        if (pEightShifts[i] > 0)            // check which direction the shift is
            temp = temp >> pEightShifts[i]; // perform the shift
        else
            temp = temp << -pEightShifts[i];
        outputKey = outputKey | temp;       // place the bit into the new key
    }

    //std::cout << "The result of P8 is: " << outputKey << std::endl;

}

#endif
