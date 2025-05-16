#include "hid/app/mouse.hpp"
#include "hid/report_protocol.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace hid::app::mouse;

TEST_CASE("mouse report descriptor")
{
    static constexpr auto desc0 = app_report_descriptor<0>();
    constexpr auto rp0 = hid::report_protocol(desc0);
    static_assert(rp0.max_input_id == 0);
    static_assert(rp0.max_input_size == 3);
    static_assert(sizeof(hid::app::mouse::report<0>) == 3);
    static_assert(rp0.max_feature_id == 0);
    static_assert(rp0.max_feature_size == 0);
    static_assert(rp0.max_output_id == 0);
    static_assert(rp0.max_output_size == 0);

    // test both compile-time and runtime
    static_assert(hid::rdf::get_application_usage_id(rp0.descriptor) ==
                  hid::page::generic_desktop::MOUSE);
    CHECK(hid::rdf::get_application_usage_id(hid::rdf::descriptor_view(desc0)) ==
          hid::page::generic_desktop::MOUSE);

    static constexpr auto desc5 = app_report_descriptor<5>();
    constexpr auto rp5 = hid::report_protocol(desc5);
    static_assert(rp5.max_input_id == 5);
    static_assert(rp5.max_input_size == 4);
    static_assert(sizeof(hid::app::mouse::report<5>) == 4);
    static_assert(rp5.max_feature_id == 0);
    static_assert(rp5.max_feature_size == 0);
    static_assert(rp5.max_output_id == 0);
    static_assert(rp5.max_output_size == 0);

    // test both compile-time and runtime
    static_assert(hid::rdf::get_application_usage_id(rp5.descriptor) ==
                  hid::page::generic_desktop::MOUSE);
    CHECK(hid::rdf::get_application_usage_id(hid::rdf::descriptor_view(desc5)) ==
          hid::page::generic_desktop::MOUSE);
}
