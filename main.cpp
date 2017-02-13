#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "SDES.h"
//#include "conversion.h"
#include "Key.h"

using namespace std;

//vectors to hold each char as a bitset
//vector<bitset<8>> bitsetPlainText; //each char from string as a bitset
//vector<bitset<8>> bitsetCipherText;

int main()
{
    string input, str;
    char c, c2;
    bitset<8> bitsetObj;

    //get string input from user
    cout << "Enter a string to encrypt:" << endl;
    getline(cin, input);  //store string including spaces
    cout << endl;

    //test string to bitset conversion
    //bitsetPlainText = stringToBitset(input);
    //str = bitsetToString(bitsetPlainText);
    /*
    cout << endl << "original string:" << endl << str;
    cout << endl << endl << "Enter a char:" << endl;
    cin >> c;
    */
    //test char to bitset conversion
    //bitsetObj = charToBitset(c);
    //cout << endl << "bits: ";

    //loop through each bit
    /*
    for(size_t i = 0; i < bitsetObj.size(); i++)
    {
        cout << bitsetObj[i];
    }
    */

    //test bitset to char
    /*
    c2 = bitsetToChar(bitsetObj);
    cout << endl<< "original char: " << c << endl;
    cout << "char after bitset conversion: " << c2 << endl << endl;
    */
    bitset<8> key1, key2;
    int count = 0;
    key1 = bitset<8>(164);
    key2 = bitset<8>(67);
    SDES sdes(input);
    sdes.printBitsetPlainText();

    for(int index = 0 ; index < 2; index++)
    {
        cout << "index: " << index << endl;
        for(int i = 0; i < sdes.getBitsetPlainTextSize(); i++)
        {
            sdes.initPermute(i);
            if (index == 0)
            {
                sdes.funcK(i, key1);
                sdes.swapHalfs(i);
            }
            else
            {
                sdes.funcK(i, key2);
                sdes.inverseInitPermute(i);
            }
        }
        count++;
        sdes.printBitsetCipherText();
        sdes.setCount(count);
        cout << endl;
    }

    for(int index = 0 ; index < 2; index++)
    {
        cout << "index: " << index << endl;
        for(int i = 0; i < sdes.getBitsetCipherTextSize(); i++)
        {
            sdes.initPermute(i);
            if (index == 0)
            {
                sdes.funcK(i, key2);
                sdes.swapHalfs(i);
            }
            else
            {
                sdes.funcK(i, key1);
                sdes.inverseInitPermute(i);
            }
        }
        count++;
        sdes.printBitsetCipherText();
        sdes.setCount(count);
        cout << endl;
    }

    sdes.printBitsetPlainText();
    sdes.printBitsetCipherText();
    sdes.bitsetToString();


    cout << endl;
    sdes.cipherTextToString();
    cout << endl;
    //cout << bitset<2>(1);
    //Key keygen(0x282);
    //Key keygen2(1023);

    return 0;


}
