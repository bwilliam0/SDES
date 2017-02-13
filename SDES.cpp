#include <iostream>
#include <string>
#include <bitset>
#include "SDES.h"
//#include "conversion.h"

using namespace std;

SDES::SDES(){}

SDES::SDES(string userInput){
    input = userInput;
    bitsetTemp.reset();
    count = 0;
    //key1 = bitset<8>(164);
    //key2 = bitset<8>(67);
    stringToBitset();
}
/*
SDES(string userInput, Key keyone, Key keytwo){
    input = userInput;
    key1 = keyone;
    key2 = keytwo;
    stringToBitset();
}*/

void SDES::initPermute(int i)
{
    if (count > 0)
    {
        bitsetVectTemp = bitsetCipherText;
    }

    int newPos[] = {2, 6, 3, 1, 4, 8, 5, 7};
    bitset<8> tempObj(0);
    int tempInt;
    int range = bitsetVectTemp[i].size() - 1;
    cout << "initPermBits: ";
    for (size_t j = 0; j < bitsetVectTemp[i].size(); j++)
    {
        tempInt = newPos[j] - 1;
        tempObj[range - j] = bitsetVectTemp[i][range - tempInt];
        cout << tempObj[range - j];
    }
    if (count == 0)
        bitsetCipherText.push_back(tempObj);
    else
        bitsetCipherText[i] = tempObj;
    cout << endl;
}

void SDES::inverseInitPermute(int index)
{
    //bitset<8> temp(237); //test 11101101 to 01110111
    int newPos[] = {4, 1, 3, 5, 7, 2, 8, 6};
    bitset<8> tempObj(0);
    int tempInt;
    int range = bitsetCipherText[index].size() - 1;
    cout << "bitsetCipherText[index]: " << bitsetCipherText[index] << endl;
    cout << "inverse initPermBits: ";
    for (size_t j = 0; j < bitsetCipherText[index].size(); j++)
    {
        tempInt = newPos[j] - 1;
        tempObj[range - j] = bitsetCipherText[index][range - tempInt];
        cout << tempObj[range - j];
    }
    bitsetCipherText[index] = tempObj;
    cout << endl;
}

void SDES::funcK(int index, bitset<8> key)
{
    expandAndPermute(index);
    bitsetTemp ^= key;
    cout << "xorfunck: " << bitsetTemp << endl;
    //sboxSub();
    permuteFour();
    xorFunc(index);
}

void SDES::swapHalfs(int index)
{
    bitset<4> rightSideInitPerm(0);
    bitset<4> temp;
    for (int j = 0; j < 4; j++)
    {
        rightSideInitPerm[j] = bitsetCipherText[index][j];
    }

    for (int j = 0; j < 4; j++)
    {
        bitsetCipherText[index][j + 4] = rightSideInitPerm[j];
        bitsetCipherText[index][j] = fourbitTemp[j];
    }

    cout << "bitsetCipherText after swap halfs " << bitsetCipherText[index] << endl;
    /*
    cout << "rightside: " << rightSideInitPerm << endl;
    temp = rightSideInitPerm;
    rightSideInitPerm = fourbitTemp;
    fourbitTemp = temp;
    cout << "swaphalfs: " << fourbitTemp <<  rightSideInitPerm << endl;
    */
}

string SDES::getInput() const
{
    return input;
}

void SDES::printBitsetPlainText()
{
    cout << "Printing out bitsetPlainText" << endl;
    for(int i = 0; i < bitsetPlainText.size(); i++)
    {
        cout << bitsetPlainText[i] << " ";
    }
    cout << endl;
}

void SDES::printBitsetCipherText()
{
    cout << "Printing out bitsetCipherText" << endl;
    for(int i = 0; i < bitsetCipherText.size(); i++)
    {
        cout << bitsetCipherText[i] << " ";
    }
    cout << endl;
}

int SDES::getBitsetPlainTextSize()
{
    return bitsetPlainText.size();
}

int SDES::getBitsetCipherTextSize()
{
    return bitsetCipherText.size();
}

int SDES::getBitsetVectTempSize()
{
    return bitsetVectTemp.size();
}

void SDES::setCount(int countVar)
{
    count = countVar;
}

void SDES::expandAndPermute(int index)
{
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
}

void SDES::sboxSub()
{

}

void SDES::permuteFour()
{
    fourbitTemp = bitset<4>(11); //testing sbox result as 1011
    bitset<4> tempBitset(0);
    int newPos[] = {2, 4, 3, 1};

    int tempInt;
    int range = 3;
    cout << "permutefour: ";
    for (int i = 0; i <fourbitTemp.size(); i++)
    {
        tempInt = newPos[i] - 1;
        tempBitset[range - i] = fourbitTemp[range - tempInt];
        cout << tempBitset[range - i];
    }

    fourbitTemp = tempBitset;
    cout << endl;
}

void SDES::xorFunc(int index)
{
    bitset<4> leftSideInitPerm(0);
    for (int j = 0; j < 4; j++)
    {
        leftSideInitPerm[j] = bitsetCipherText[index][j + 4];
    }
    cout << "leftside: " << leftSideInitPerm << endl;
    fourbitTemp ^= leftSideInitPerm;
    cout << "xorFunc: " << fourbitTemp << endl;
}

void SDES::stringToBitset()
{

    for (size_t i = 0; i < input.size(); i++)
    {
      bitsetPlainText.push_back(bitset<8>(input[i])); //store vector of bitset objs
      cout << "bits: " << bitsetPlainText[i];
      cout << " char: " << input[i] << endl;
    }
    bitsetVectTemp = bitsetPlainText;
}

void SDES::bitsetToString()
{
    string str = "";

    //loop through each bitset and convert to char
    for(int i = 0; i < bitsetPlainText.size(); i++)
    {
        unsigned long charAsInt = bitsetPlainText[i].to_ulong(); //convert bitset to long
        unsigned char c = static_cast<unsigned char>(charAsInt); //convert long to char
        str += c;
    }

    cout << "bitsetToString:" << endl << str;
}

void SDES::cipherTextToString()
{
    string str = "";

    //loop through each bitset and convert to char
    for(int i = 0; i < bitsetCipherText.size(); i++)
    {
        unsigned long charAsInt = bitsetCipherText[i].to_ulong(); //convert bitset to long
        unsigned char c = static_cast<unsigned char>(charAsInt); //convert long to char
        str += c;
    }

    cout << "cipherTextToString:" << endl << str;
}
