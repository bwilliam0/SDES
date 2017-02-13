#ifndef _KEY_H
#define _KEY_H

#include <iostream>
#include <stdexcept>
#include <bitset>

class Key {

public:

    static const unsigned int RIGHT_BIT_MASK = 0x1F;///< Bit mask used to pick out the right 5 bits in the ten bit key
    static const unsigned int LEFT_BIT_MASK = 0x3E0;///< Bit mask used to pick out the left 5 bits in the ten bit key
    static const unsigned int KEY_MAX_SIZE = 1023;///< The maximum decimal value that the given key can be
    static const unsigned int KEY_SIZE = 10;///< The number of bits in the key
    static const unsigned int SUBKEY_SIZE = 8;///< The number of bits in the subkey

    Key(unsigned int seed);
    std::bitset<SUBKEY_SIZE> getKeyOne();
    std::bitset<SUBKEY_SIZE> getKeyTwo();

private:

    static const unsigned int pEightMasks[];///< Defines a list of bit masks used in the 8 bit permutation
    static const unsigned int masks[];///< Defines a list of bit masks that can be used to pick out individual bits
    static const int pTenShifts[];///< Defines a list of bit shifts used in the 10 bit permutation
    static const int pEightShifts[];///< Defines a list of bit shifts used in the 8 bit permutation

    unsigned int keyInput;///< Stores the key that was input by the user
    unsigned int key10bit;///< Stores the 10 bit key after the multiple shifts
    unsigned int keyOne;///< Stores the first 8 bit key
    unsigned int keyTwo;///< Stores the second 8 bit key

    void generateSubKeys();
    void permuteTen();
    void leftShiftOne();
    unsigned int permuteEight(unsigned int inputKey);

};


#endif
