#define BitStream_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>

using namespace std;
class BitStream
{
private:
    fstream file;
    int mode;
    int size;
    int p; // pointer
    unsigned char buffer;

public:
    BitStream();
    BitStream(const char *file, char mode);
    unsigned char read_bit();
    void write_bit(char bit);
    unsigned char *read_nbits(int n);
    void write_nbits(int n, unsigned char *bits);
    bool eoF();
    void closeF();
};
