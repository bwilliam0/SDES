#ifndef SDES_H_INCLUDED
#define SDES_H_INCLUDED

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "Key.h"
//#include "conversion.h"

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
        int count;
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
        int getBitsetVectTempSize();
        void bitsetToString();
        void stringToBitset();
        void cipherTextToString();
        void setCount(int countVar);


};

#endif // SDES_H_INCLUDED
/*
printBitsetCipherText();
    int newPos[] = {4, 1, 2, 3, 2, 3, 4, 1};
    //bitset<8> tempObj(0);
    int tempInt;
    int arraySize = bitsetCipherText[index].size() - 1;
    int range = 3;
    cout << "expandAndPermuteBits: ";
    for (size_t j = 0; j < bitsetCipherText[index].size(); j++)
    {
        tempInt = newPos[j] - 1;
        bitsetTemp[arraySize - j] = bitsetCipherText[index][range - tempInt];
        cout << bitsetTemp[arraySize - j];
    }
    //bitsetCipherText[index] = bitsetTemp;
    cout << endl;
}*/
