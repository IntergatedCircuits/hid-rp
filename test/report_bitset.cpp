#include "hid/report_bitset.hpp"
#include "hid/page/consumer.hpp"
#include "hid/page/leds.hpp"
#include "test_framework.hpp"

using namespace hid::page;

SUITE(report_bitset)
{
    using volume_bitset =
        hid::report_bitset<consumer::VOLUME_INCREMENT, consumer::VOLUME_DECREMENT, consumer::MUTE>;

    TEST_CASE("size and membership")
    {
        static_assert(volume_bitset::size() == 3);
        static_assert(sizeof(volume_bitset) == 1);

        volume_bitset volume;
        CHECK(volume.contains(consumer::VOLUME_INCREMENT));
        CHECK(volume.contains(consumer::VOLUME_DECREMENT));
        CHECK(volume.contains(consumer::MUTE));
        CHECK(not volume.contains(consumer::VOLUME));
    };

    TEST_CASE("runtime set/test/reset/flip")
    {
        volume_bitset volume;
        CHECK(not volume.test(consumer::MUTE));
        CHECK(volume.set(consumer::MUTE, true));
        CHECK(volume.test(consumer::MUTE));
        CHECK(not volume.test(consumer::VOLUME_INCREMENT));
        CHECK(not volume.set(consumer::VOLUME, true));

        CHECK(volume.flip(consumer::VOLUME_INCREMENT));
        CHECK(volume.test(consumer::VOLUME_INCREMENT));
        CHECK(volume.flip(consumer::VOLUME_INCREMENT));
        CHECK(not volume.test(consumer::VOLUME_INCREMENT));

        CHECK(volume.reset(consumer::MUTE));
        CHECK(not volume.test(consumer::MUTE));

        volume.set(consumer::VOLUME_DECREMENT, true);
        CHECK(volume.test(consumer::VOLUME_DECREMENT));
        volume.reset();
        CHECK(not volume.test(consumer::VOLUME_DECREMENT));
    };

    TEST_CASE("compile-time usage API")
    {
        volume_bitset volume;
        CHECK(not volume.test<consumer::VOLUME_INCREMENT>());
        volume.set<consumer::VOLUME_INCREMENT>();
        CHECK(volume.test<consumer::VOLUME_INCREMENT>());
        volume.flip<consumer::MUTE>();
        CHECK(volume.test<consumer::MUTE>());
        volume.reset<consumer::VOLUME_INCREMENT>();
        CHECK(not volume.test<consumer::VOLUME_INCREMENT>());
    };

    TEST_CASE("equality")
    {
        volume_bitset a;
        volume_bitset b;
        CHECK(a == b);
        a.set(consumer::MUTE, true);
        CHECK(a != b);
        b.set(consumer::MUTE, true);
        CHECK(a == b);
    };

    TEST_CASE("mixed usage pages")
    {
        // keys don't need to share a usage page or enumeration type
        using mixed_bitset = hid::report_bitset<consumer::MUTE, leds::NUM_LOCK, leds::CAPS_LOCK>;
        static_assert(mixed_bitset::size() == 3);

        mixed_bitset mixed;
        CHECK(mixed.contains(consumer::MUTE));
        CHECK(mixed.contains(leds::NUM_LOCK));
        CHECK(not mixed.contains(leds::SCROLL_LOCK));

        CHECK(mixed.set(consumer::MUTE, true));
        CHECK(mixed.set(leds::CAPS_LOCK, true));
        CHECK(mixed.test(consumer::MUTE));
        CHECK(not mixed.test(leds::NUM_LOCK));
        CHECK(mixed.test(leds::CAPS_LOCK));
    };
};
