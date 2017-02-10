#ifndef _KEY_H
#define _KEY_H

#include <iostream>
#include <bitset>


class Key {

public:

    Key(int seed);
    Key();
    int getKeyOne();
    int getKeyTwo();

private:

    int keyInput;
    std::bitset<10> key10bit;
    std::bitset<8> keyOne;
    std::bitset<8> keyTwo;


};


#endif
