#include <iostream>
#include <string>
#include <bitset>
#include "SDES.h"
//#include "conversion.h"

using namespace std;

SDES::SDES(){}

SDES::SDES(string userInput){
    input = userInput;
    stringToBitset();
}

SDES(string userInput, Key keyone, Key keytwo){
    input = userInput;
    key1 = keyone;
    key2 = keytwo;
    stringToBitset();
}

void SDES::initPermute(int i)
{
    int newPos[] = {2, 6, 3, 1, 4, 8, 5, 7};
    bitset<8> tempObj(0);
    int tempInt;
    int pos = bitsetPlainText[i].size() - 1;
    cout << "initPermBits: ";
    for (size_t j = 0; j < bitsetPlainText[i].size(); j++)
    {
        tempInt = newPos[j] - 1;
        tempObj[pos - j] = bitsetPlainText[i][pos - tempInt];
        cout << tempObj[pos - j];
    }
    bitsetCipherText.push_back(tempObj);
    cout << endl;
}

void SDES::funcK(int index)
{
    expandAndPermute(index);
    xorFunc();
    sboxSub();
    permuteFour();
    xorFunc();
}

void SDES::swapHalfs()
{

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

bitset<8> SDES::expandAndPermute(int index)
{
    int newPos[] = {4, 1, 2, 3, 2, 3, 4, 1};
    bitset<8> tempObj(0);
    int tempInt;
    int pos = 3;
    cout << "expandAndPermuteBits: ";
    for (size_t j = 0; j < pos; j++)
    {
        tempInt = newPos[j] - 1;
        tempObj[pos - j] = bitsetCipherText[index][pos - tempInt];
        cout << tempObj[pos - j];
    }

    cout << endl;
    return tempObj;
}

void SDES::sboxSub()
{

}

void SDES::permuteFour()
{

}

void SDES::xorFunc()
{

}

void SDES::stringToBitset()
{

    for (size_t i = 0; i < input.size(); i++)
    {
      bitsetPlainText.push_back(bitset<8>(input[i])); //store vector of bitset objs
      cout << "bits: " << bitsetPlainText[i];
      cout << " char: " << input[i] << endl;
    }
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
