#ifndef SDES_H_INCLUDED
#define SDES_H_INCLUDED

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
//#include "conversion.h"

using namespace std;

class SDES {
    private:
        vector<bitset<8>> bitsetPlainText; //each char from string as a bitset
        vector<bitset<8>> bitsetCipherText;
        bitset<8> bitsetTemp;
        string input;
        Key key1, key2;
        bitset<8> expandAndPermute(int index);
        void sboxSub();
        void permuteFour();
        void xorFunc();


    public:
        SDES();
        SDES(string userInput);
        SDES(string userInput, Key key1, Key key2);
        void initPermute(int i);
        void funcK(int index);
        void swapHalfs();
        string getInput() const;
        void printBitsetPlainText();
        void printBitsetCipherText();
        int getBitsetPlainTextSize();
        int getBitsetCipherTextSize();
        void bitsetToString();
        void stringToBitset();


};

#endif // SDES_H_INCLUDED
