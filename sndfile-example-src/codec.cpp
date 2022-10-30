#include <BitStream.hpp>
#include <math.h>
#include <string>
#include <bitset>
#include <iostream>


string EncoderToBinary(string word){
    string binaryString = "";
    for (char& _char: word){        // For every char in char
        binaryString +=bitset<8>(_char).to_string();
    }

    return binaryString;
}

string DecoderToString()