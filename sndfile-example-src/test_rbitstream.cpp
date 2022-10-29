#include <iostream>
#include <BitStream.hpp>

using namespace std;

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    BitStream bs(argv[argc - 1], 'rd');
    BitStream b("test_rbitstream.txt", 'w');

    while (bs.eoF())
    {
        unsigned char c = bs.read_bit();
        b.write_bit(c);
    }
    b.closeF();
    return 0;
}