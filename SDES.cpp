#include <iostream>
#include <string>
#include <bitset>
#include "SDES.h"

using namespace std;

SDES::SDES(){}

SDES::SDES(string userInput){
    input = userInput;
    bitsetTemp.reset();
    encryptDoneFlag = false;
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

void SDES::initPermute(int index)
{
    if (encryptDoneFlag == true)
    {
        bitsetVectTemp = bitsetCipherText;
    }

    int newPos[] = {2, 6, 3, 1, 4, 8, 5, 7};
    bitset<8> tempObj(0);
    int tempInt;
    int range = bitsetVectTemp[index].size() - 1;
    //cout << "Doing initial permuation: " << endl;
    for (size_t j = 0; j < bitsetVectTemp[index].size(); j++)
    {
        tempInt = newPos[j] - 1;
        tempObj[range - j] = bitsetVectTemp[index][range - tempInt];
        //cout << tempObj[range - j];
    }
    if (encryptDoneFlag == false)
        bitsetCipherText.push_back(tempObj);
    else
        bitsetCipherText[index] = tempObj;
    //cout << endl;
}

void SDES::inverseInitPermute(int index)
{
    int newPos[] = {4, 1, 3, 5, 7, 2, 8, 6};
    bitset<8> tempObj(0);
    int tempInt;
    int range = bitsetCipherText[index].size() - 1;
    //cout << "Doing inverse initial permuation: " << endl;
    for (size_t j = 0; j < bitsetCipherText[index].size(); j++)
    {
        tempInt = newPos[j] - 1;
        tempObj[range - j] = bitsetCipherText[index][range - tempInt];
        //cout << tempObj[range - j];
    }
    bitsetCipherText[index] = tempObj;
    //cout << endl;
}

void SDES::funcK(int index, bitset<8> key)
{
    //cout << "Doing func k: " << endl;
    expandAndPermute(index);
    bitsetTemp ^= key;
    //cout << "xorfunck: " << bitsetTemp << endl;
    sboxSub();
    permuteFour();
    xorFunc(index);
}

void SDES::swapHalfs(int index)
{
    //cout << "Swapping halfs of first round:" << endl;
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

    //cout << "bitsetCipherText after swap halfs " << bitsetCipherText[index] << endl;
}

void SDES::printBitsetPlainText()
{
    cout << "Printing out plain text bits:" << endl;
    for(int i = 0; i < bitsetPlainText.size(); i++)
    {
        cout << bitsetPlainText[i] << " ";
    }
    cout << endl;
}

void SDES::printBitsetCipherText()
{
    cout << "Printing out cipher text bits:" << endl;
    for(int i = 0; i < bitsetCipherText.size(); i++)
    {
        cout << bitsetCipherText[i] << " ";
    }
    cout << endl;
}

int SDES::getBitsetPlainTextSize() const
{
    return bitsetPlainText.size();
}

int SDES::getBitsetCipherTextSize() const
{
    return bitsetCipherText.size();
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

    cout << "Plain text before encryption:" << endl << str;
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

    cout << "Cipher text after decryption:" << endl << str;
}

void SDES::setEncryptFlag(bool flag)
{
    encryptDoneFlag = flag;
}

/** Private functions **/
void SDES::expandAndPermute(int index)
{
    int newPos[] = {4, 1, 2, 3, 2, 3, 4, 1};
    int tempInt;
    int arraySize = bitsetCipherText[index].size() - 1;
    int range = 3;
    //cout << "expandAndPermuteBits: ";
    for (size_t j = 0; j < bitsetCipherText[index].size(); j++)
    {
        tempInt = newPos[j] - 1;
        bitsetTemp[arraySize - j] = bitsetCipherText[index][range - tempInt];
        //cout << bitsetTemp[arraySize - j];
    }

    //cout << endl;
}

void SDES::sboxSub()
{
    bitset<2> zero(0), one(1), two(2), three(3), tempTwo;
    bitset<2> bit1bit4L, bit2bit3L, bit1bit4R, bit2bit3R;
    unsigned long bit1bit4Left, bit2bit3Left;
    unsigned long bit1bit4Right, bit2bit3Right;
    bitset<2> s1[4][4] = {{one,zero,three,two},{three,two,one,zero},
                          {zero,two,one,three},{three,one,three,two}};
    bitset<2> s2[4][4] = {{zero,one,two,three},{two,zero,one,three},
                          {three,zero,one,zero},{two,one,zero,three}};

    for (int j = 0; j < 8; j++)
    {
        switch (j)
        {
            case 0: bit1bit4R[0] = bitsetTemp[j];
                    break;
            case 1: bit2bit3R[0] = bitsetTemp[j];
                    break;
            case 2: bit2bit3R[1] = bitsetTemp[j];
                    break;
            case 3: bit1bit4R[1] = bitsetTemp[j];
                    break;
            case 4: bit1bit4L[0] = bitsetTemp[j];
                    break;
            case 5: bit2bit3L[0] = bitsetTemp[j];
                    break;
            case 6: bit2bit3L[1] = bitsetTemp[j];
                    break;
            case 7: bit1bit4L[1] = bitsetTemp[j];
                    break;
        }
    }
    bit1bit4Right = bit1bit4R.to_ulong();
    bit2bit3Right = bit2bit3R.to_ulong();
    bit1bit4Left = bit1bit4L.to_ulong();
    bit2bit3Left = bit2bit3L.to_ulong();

    tempTwo = s2[bit1bit4Right][bit2bit3Right];

    fourbitTemp[0] = tempTwo[0];
    fourbitTemp[1] = tempTwo[1];
    tempTwo = s1[bit1bit4Left][bit2bit3Left];

    fourbitTemp[2] = tempTwo[0];
    fourbitTemp[3] = tempTwo[1];

    //cout << "sbox: " << fourbitTemp << endl;
}

void SDES::permuteFour()
{
    bitset<4> tempBitset(0);
    int newPos[] = {2, 4, 3, 1};

    int tempInt;
    int range = 3;
    //cout << "permutefour: ";
    for (int i = 0; i <fourbitTemp.size(); i++)
    {
        tempInt = newPos[i] - 1;
        tempBitset[range - i] = fourbitTemp[range - tempInt];
        //cout << tempBitset[range - i];
    }

    fourbitTemp = tempBitset;
    //cout << endl;
}

void SDES::xorFunc(int index)
{
    bitset<4> leftSideInitPerm(0);
    for (int j = 0; j < 4; j++)
    {
        leftSideInitPerm[j] = bitsetCipherText[index][j + 4];
        bitsetTemp[j] = bitsetCipherText[index][j];

    }
    fourbitTemp ^= leftSideInitPerm;
    for (int j = 0; j < 4; j++)
    {
        bitsetTemp[j + 4] = fourbitTemp[j];
    }
    bitsetCipherText[index] = bitsetTemp;
    //cout << "xorFunc: " << fourbitTemp << endl;
}

void SDES::stringToBitset()
{

    for (size_t i = 0; i < input.size(); i++)
    {
      bitsetPlainText.push_back(bitset<8>(input[i])); //store vector of bitset objs
      //cout << "bits: " << bitsetPlainText[i];
      //cout << " char: " << input[i] << endl;
    }
    bitsetVectTemp = bitsetPlainText;
}
