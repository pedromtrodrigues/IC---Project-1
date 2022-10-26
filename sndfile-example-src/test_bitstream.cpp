#include "BitStream.hpp"

int main(int argc, char **argv)
{
    BitStream b("test_bitstream.txt", 'w');
    unsigned char bits[8] = {1, 1, 0, 0, 1, 0, 1, 0};
    b.write_nbits(8, bits);
    b.closeF();
    return 0;
}
