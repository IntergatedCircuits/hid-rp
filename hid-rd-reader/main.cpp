#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "hid/rdf/formatter.hpp"

// print the binary file or std input as human readable HID report descriptor
int main(int argc, char* argv[])
{
    std::vector<char> desc;
    if (argc > 1)
    {
        std::ifstream file(argv[1], std::ios::binary);
        if (!file)
        {
            std::cerr << "Error: Cannot open file " << argv[1] << '\n';
            return 1;
        }
        desc = std::vector<char>(std::istreambuf_iterator<char>(file),
                                 std::istreambuf_iterator<char>());
    }
    else
    {
        desc = std::vector<char>(std::istreambuf_iterator<char>(std::cin),
                                 std::istreambuf_iterator<char>());
    }

    std::cout << std::format(
        "{}", hid::rdf::descriptor_view(reinterpret_cast<std::uint8_t*>(desc.data()), desc.size()));

    return 0;
}
