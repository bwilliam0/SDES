#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <random>
#include <time.h>
#include "SDES.h"
#include "Key.h"

using namespace std;

unsigned long createRandomTenBitKey()
{
    srand (time(NULL)); //seed rand generator
    bitset<10> rand10BitKey;
    unsigned long randKey;

    cout << endl << "Creating random 10 bit key" << endl;
    for (int index = 0; index < 10; index++)
    {
        int x = rand() % 2;
        bitset<1> oneBit(x);
        rand10BitKey[index] = oneBit[0];
    }

    randKey = rand10BitKey.to_ulong();
    cout << "random key bits: " << rand10BitKey << endl;
    cout << "random key bits as unsigned long: " << randKey << endl;

    return randKey;
}

int main()
{
    string input;
    bitset<8> key1, key2;
    unsigned long randKey;

    //get string input from user
    cout << "Enter a string to encrypt:" << endl;
    getline(cin, input);  //store string including spaces

    randKey = createRandomTenBitKey();

    cout << endl << "Generating key1 and key2" << endl;

    //Key keygen(1023);
    Key keygen(randKey);

    key1 = keygen.getKeyOne();
    key2 = keygen.getKeyTwo();

    cout << "key1 bits: " << key1 << endl;
    cout << "key2 bits: " << key2 << endl;

    SDES sdes(input);

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

            //cout << endl;
        }

        //sdes.printBitsetCipherText();
    }
    sdes.setEncryptFlag(true);
    cout << endl;
    sdes.printBitsetPlainText();
    cout << endl;
    sdes.printBitsetCipherTextAfterEncrypt();

    //decrypt
    cout << endl << "Starting Decryption" << endl;
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
        //sdes.printBitsetCipherText();

        //cout << endl;
    }

    cout << endl << "Plain text bits before encryption" << endl;
    sdes.printBitsetPlainText();
    cout << endl << "Cipher text bits after decryption" << endl;
    sdes.printBitsetCipherText();
    cout << endl;
    sdes.bitsetToString();
    cout << endl << endl;
    sdes.cipherTextToString();
    cout << endl;

    return 0;
}
