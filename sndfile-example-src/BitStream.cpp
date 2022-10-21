#include "BitStream.hpp"
#include <math.h>
#include <string>

using namespace std;

BitStream::BitStream()
{
    this->mode = 0;
    this->size = 0;
    this->p = 0;
    this->buffer = 0;
}

BitStream::BitStream(const char *name, char mode)
{
    if (mode == 'rd')
    {
        this->mode = 10;
        this->file.open(name, ios::in | ios::binary);
        file.seekg(0, ios::end);
        size = file.tellg();
        file.seekg(0, ios::beg);
    }
    else if (mode == 'wr')
    {
        this->mode = 1;
        this->p = 8;
        this->file.open(name, ios::out | ios::binary);
    }
    else
    {
        throw "Invalid mode";
    }
    buffer = 0;
    if (!file.is_open())
        throw runtime_error("Could not open file");
}

unsigned char BitStream::read_bit()
{
    if (mode != 10)
        throw "Invalid mode";

    if (p == 8)
    {
        file.read((char *)&buffer, 1);
        p = 0;
    }

    unsigned char bit = (buffer >> (7 - p)) & 1;
    p++;
    return bit;
}

void BitStream::write_bit(char bit)
{
    if (mode != 1)
        throw "Invalid mode";

    if (p == 8)
    {
        file.write((char *)&buffer, 1);
        p = 0;
        buffer = 0;
    }

    buffer |= (bit << (7 - p));
    p++;
}

void BitStream::write_nbits(int n, unsigned char *bits)
{
    if (this->mode != 10)
    {
        throw "Invalid mode";
    }

    int i = 0;
    while (i < n)
    {
        this->write_bit(bits[i]);
    }
}

bool BitStream::eoF()
{
    if (mode != 10)
        throw "Invalid mode";
    return file.eof();
}

void BitStream::closeF()
{
    if (mode == 1)
        file.write((char *)&buffer, 1);
    file.close();
}