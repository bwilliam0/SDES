#ifndef SDES_H_INCLUDED
#define SDES_H_INCLUDED

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "Key.h"

using namespace std;

class SDES {
    private:
        vector<bitset<8>> bitsetPlainText; //each char from string as a bitset
        vector<bitset<8>> bitsetCipherText;
        vector<bitset<8>> bitsetCipherTextAfterEncrypt;
        vector<bitset<8>> bitsetVectTemp;
        bitset<8> bitsetTemp;
        bitset<4> fourbitTemp;
        string input;
        //Key key1, key2;
        //bitset<8> key1, key2;
        bool encryptDoneFlag;
        void expandAndPermute(int index);
        void sboxSub();
        void permuteFour();
        void xorFunc(int index);
        void stringToBitset();

    public:
        SDES();
        SDES(string userInput);
        //SDES(string userInput, Key key1, Key key2);
        void initPermute(int index);
        void inverseInitPermute(int index);
        void funcK(int index, bitset<8> key);
        void swapHalfs(int index);
        void printBitsetPlainText();
        void printBitsetCipherText();
        void printBitsetCipherTextAfterEncrypt();
        int getBitsetPlainTextSize() const;
        int getBitsetCipherTextSize() const;
        void bitsetToString();
        void cipherTextToString();
        void setEncryptFlag(bool flag);
};

//#include "SDES.cpp"

#endif // SDES_H_INCLUDED
