/** @file main.cpp

    @authors: Jesse Babcock, Brady Anderson

    The main file coordinates execution of the Key and SDES classes. A random 10 bit key
    is generated and used in Key.h. This class then creates 2 8 bit subkeys for 2 rounds
    of bit transformations in encryption and decryption processing. The plaintext, ciphertext,
    bit patterns, and steps of execution are displayed to the user.

*/

#include "MasterHeader.h"
#include "SDES.h"

using namespace std;

/** @brief create random 10 bit key for Key.h
 *
 * @return unsigned long 10 bit key as an int
 *
 */
unsigned long createRandomTenBitKey()
{
    srand (time(NULL)); //seed rand generator
    bitset<10> rand10BitKey; // store 10 bits
    unsigned long randKey;

    cout << endl << "Creating random 10 bit key" << endl;

    // create 1 bit during each iter
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
    string input; // user input
    bitset<8> key1, key2; // 2 subkeys
    unsigned long randKey; // 10 bit key for key gen

    //get string input from user
    cout << "Enter a string to encrypt:" << endl;
    getline(cin, input);  //store string including spaces

    randKey = createRandomTenBitKey(); // create random 10 bit key

    cout << endl << "Generating key1 and key2" << endl;

    Key keygen(randKey); // create key obj

    key1 = keygen.getKeyOne(); // get first sub key
    key2 = keygen.getKeyTwo(); // get second sub key

    cout << "key1 bits: " << key1 << endl;
    cout << "key2 bits: " << key2 << endl;

    SDES sdes(input); // create SDES obj

    //encrypt
    cout << endl << "Starting Encryption" << endl;
    for(int i = 0; i < sdes.getBitsetPlainTextSize(); i++)
    {
        cout << "Encrypting char num: " << i << endl;
        sdes.initPermute(i);

        // 2 rounds of transformations
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
    sdes.setEncryptFlag(true); // encryption is done
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

        // 2 rounds of transformations
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
