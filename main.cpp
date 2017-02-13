#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "SDES.h"
#include "Key.h"

using namespace std;

int main()
{
    string input;
    bitset<8> key1, key2;
    key1 = bitset<8>(164); //test with youtube example keys
    key2 = bitset<8>(67);

    //get string input from user
    cout << "Enter a string to encrypt:" << endl;
    getline(cin, input);  //store string including spaces
    cout << endl;

    SDES sdes(input);
    sdes.printBitsetPlainText();

    //encrypt
    cout << endl << "Starting Encryption" << endl;
    for(int i = 0; i < sdes.getBitsetPlainTextSize(); i++)
    {
        cout << "Encrypting char num: " << i << endl;
        sdes.initPermute(i);
        for(int index = 0 ; index < 2; index++)
        {
            if (index == 0)
            {
                cout << "Encrypt with key1" << endl;
                sdes.funcK(i, key1);
                sdes.swapHalfs(i);
            }
            else
            {
                cout << "Encrypt with key2" << endl;
                sdes.funcK(i, key2);
                sdes.inverseInitPermute(i);
            }

            cout << endl;
        }

        sdes.printBitsetCipherText();
    }
    sdes.setEncryptFlag(true);

    //decrypt
    cout << "Starting Decryption" << endl;
    for(int i = 0; i < sdes.getBitsetCipherTextSize(); i++)
    {
        cout << "Decrypting char num: " << i << endl;
        sdes.initPermute(i);
        for(int index = 0 ; index < 2; index++)
        {
            if (index == 0)
            {
                cout << "Decrypt with key1" << endl;
                sdes.funcK(i, key2);
                sdes.swapHalfs(i);
            }
            else
            {
                cout << "Decrypt with key2" << endl;
                sdes.funcK(i, key1);
                sdes.inverseInitPermute(i);
            }
        }
        sdes.printBitsetCipherText();

        cout << endl;
    }

    sdes.printBitsetPlainText();
    sdes.printBitsetCipherText();
    sdes.bitsetToString();
    cout << endl;
    sdes.cipherTextToString();
    cout << endl;

    //Key keygen(0x282);
    //Key keygen2(1023);

    return 0;


}
