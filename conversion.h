/** Header file to convert chars, strings, or bitsets
*/

#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED

#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

//Convert a string to bitset. Each char from string is converted
//to a bitset and stored in a vector.
vector<bitset<8>> stringToBitset(string input){
    vector<bitset<8>> bitsetTemp;
    for (size_t i = 0; i < input.size(); ++i)
    {
      bitsetTemp.push_back(bitset<8>(input[i])); //store vector of bitset objs
      cout << "bits: " << bitsetTemp[i];
      cout << " char: " << input[i] << endl;
    }

    return bitsetTemp;
}

//Convert a vector of bitsets to a string
string bitsetToString(const vector<bitset<8>> &bitsetTemp){
    string str = "";

    //loop through each bitset and convert to char
    for(int i = 0; i < bitsetTemp.size(); i++)
    {
        unsigned long charAsInt = bitsetTemp[i].to_ulong(); //convert bitset to long
        unsigned char c = static_cast<unsigned char>(charAsInt); //convert long to char
        str += c;
    }

    return str;
}

//convert char to bitset
bitset<8> charToBitset(char c){
    return bitset<8>(c);
}

//convert bitset to char
char bitsetToChar(const bitset<8> &bitsetTemp){
    unsigned long charAsInt = bitsetTemp.to_ulong(); //convert bitset to long
    unsigned char c = static_cast<unsigned char>(charAsInt); //convert long to char
    return c;
}

#endif // CONVERSION_H_INCLUDED
