/** @file SDES.h

    @authors: Jesse Babcock, Brady Anderson

    This specification file performs simple SDES encryption and decryption. There are 2 rounds with subkeys
    1 and 2 used in funcK. Public functions perform initial and inverse permutation, convert strings to bitsets,
    bitsets to strings, print out bitset vectors, and swap bit halfs. Helper functions are used with funcK in 4
    separate steps to encrypt or decrypt. A boolean flag indicates what order to perform the operations. Bitsets
    are used to perform binary operations and vectors hold them when more than 8 bits are needed for storage. The
    encryption is done one char (8 bits) at a time until the entire string is cipher text. This process repeats
    for decryption to convert back to plain text.

*/

#ifndef SDES_H_INCLUDED
#define SDES_H_INCLUDED

#include "MasterHeader.h"
#include "Key.h"

using namespace std;

class SDES {
    private:
        vector<bitset<8>> bitsetPlainText; // each char from string as a bitset
        vector<bitset<8>> bitsetCipherText; // bitset vector of ciphertext
        vector<bitset<8>> bitsetCipherTextAfterEncrypt; // temp storage to print contents after encrypt
        vector<bitset<8>> bitsetVectTemp; // temp storage plain text
        bitset<8> bitsetTemp; // temp 8 bit bitset for different funcs
        bitset<4> fourbitTemp; // temp 4 bit bitset for different funcs
        string input; // store user input
        bool encryptDoneFlag;  // flip flag when encryption is done

        /** private helper funcitons **/

        /** @brief expand last 4 bits of initial permutation to 8 and permutate
         *
         * @param index an int that reps char spot in string
         * @return void
         *
         */
        void expandAndPermute(int index);

        /** @brief perform sBox substitution
         *
         * @return void
         *
         */
        void sboxSub();

        /** @brief permutate 4 bits and store in fourbitTemp
         *
         * @return void
         *
         */
        void permuteFour();

        /** @brief XOR with left 4 bits from initial permutation
         *
         * @param index an int that reps char spot in string
         * @return void
         *
         */
        void xorFunc(int index);

        /** @brief convert string to a vector of bitsets
         *
         * @return void
         *
         */
        void stringToBitset();

    public:
        /** @brief Default constructor to initialize encrypt/decrypt objects
         */
        SDES();

        /** @brief Parameterized constructor
         *
         * @param userInput is a string to encrypt/decrypt
         *
         */
        SDES(string userInput);

        /** @brief perform initial permutation
         *
         * @param index an int that reps char spot in string
         * @return void
         *
         */
        void initPermute(int index);

        /** @brief reverse initial permutation
         *
         * @param index an int that reps char spot in string
         * @return void
         *
         */
        void inverseInitPermute(int index);

        /** @brief primary func that uses helper funcs expandAndPermute, sboxSub, xorFunc
         *
         * @param index an int that reps char spot in string
         * @param key stores the key as single bits in bitset
         * @return void
         *
         */
        void funcK(int index, bitset<8> key);

        /** @brief swap 1st and 2nd half of bits
         *
         * @param index an int that reps char spot in string
         *
         * @return void
         *
         */
        void swapHalfs(int index);

        /** @brief print plaintext bitset as a string
         *
         * @return void
         *
         */
        void printBitsetPlainText();

        /** @brief print ciphertext bitset as a string after decryption
         *
         * @return void
         *
         */
        void printBitsetCipherText();

        /** @brief print ciphertext bitset as a string after encryption
         *
         *
         * @return void
         *
         */
        void printBitsetCipherTextAfterEncrypt();

        /** @brief get size of plaintext bitset
         *
         * @return int size of bitset
         */
        int getBitsetPlainTextSize() const;

        /** @brief get size of ciphertext bitset
         *
         * @return int size of bitset
         *
         */
        int getBitsetCipherTextSize() const;

        /** @brief convert bitset to string
         *
         * @return void
         *
         */
        void bitsetToString();

        /** @brief convert ciphertext to string
         *
         * @return void
         *
         */
        void cipherTextToString();

        /** @brief flip encrytion flag to start decryption
         *
         * @return void
         *
         */
        void setEncryptFlag(bool flag);
};

//#include "SDES.cpp"

#endif // SDES_H_INCLUDED
