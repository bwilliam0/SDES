/**
 * @file keytest.cpp
 *
 * @brief Tests the Key class by generating two separate keys and reporting their output.
 *
 * This class when used with the compiler directive -DDEBUG_KEY is used to test the key class by generating two separate
 * keys and reporting their output.
 */
#include "MasterHeader.h"
#include "Key.h"
using namespace std;

int main() {

    Key keygen(0x282);
    Key keygen2(1023);

    return 0;

}