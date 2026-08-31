#include "hid/page/consumer.hpp"
#include "hid/report_bitset.hpp"

using namespace hid::page;

// duplicate usage values in the pack must be a compile-time error
hid::report_bitset<consumer::VOLUME_INCREMENT, consumer::VOLUME_INCREMENT> bits;

int main()
{
    return 0;
}
