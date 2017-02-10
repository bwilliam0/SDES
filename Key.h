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
    bitset keyOne;
    bitset keyTwo;


};


#endif
