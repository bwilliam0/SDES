#ifndef _KEY_H
#define _KEY_H

#include <iostream>
#include <stdexcept>
#include <bitset>

/**
 * @class This class generates two 8 bit SDES subkeys from a ten bit key provided to the constructor
 *
 * @authors: Brady Anderson, Jesse Babcock
 *
 * The Key class is used to generate the two 8 bit subkeys used by the SDES encryption algorithm from
 * a ten bit key provided to the constructor. The constructor takes an integer as an argument and
 * checks to ensure that it is the correct number of bits. It then passes it to several functions to permute the ten bit
 * number, shift the high 5 and the low 5 bits left, permute it to an eight bit number (creating the first subkey),
 * perform two more left shifts on the ten bit number, and finally a second 8 bit to generate the second subkey.
 */
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
