#include "hid/page/consumer.hpp"
#include "hid/report_bitset.hpp"

using namespace hid::page;

hid::report_bitset<consumer::VOLUME_INCREMENT, consumer::VOLUME_DECREMENT> bits;

int main()
{
    // MUTE isn't part of the bitset's usage list; must be a compile-time error
    return bits.test<consumer::MUTE>();
}
