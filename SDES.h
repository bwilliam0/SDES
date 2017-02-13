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



    public:
        SDES();
        SDES(string userInput);
        //SDES(string userInput, Key key1, Key key2);
        void initPermute(int i);
        void inverseInitPermute(int index);
        void funcK(int index, bitset<8> key);
        void swapHalfs(int index);
        string getInput() const;
        void printBitsetPlainText();
        void printBitsetCipherText();
        int getBitsetPlainTextSize();
        int getBitsetCipherTextSize();
        void bitsetToString();
        void stringToBitset();
        void cipherTextToString();
        void setEncryptFlag(bool flag);
};

#endif // SDES_H_INCLUDED
