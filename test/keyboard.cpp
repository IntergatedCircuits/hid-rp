#include "hid/app/keyboard.hpp"
#include "hid/rdf/formatter.hpp"
#include "hid/report_protocol.hpp"
#include "test_framework.hpp"

using namespace hid::app::keyboard;

SUITE(keyboard_)
{
    TEST_CASE("keyboard report descriptor")
    {
        constexpr auto rp0 = hid::report_protocol::from_descriptor<app_report_descriptor<0>()>();
        static_assert(rp0.max_input_id == 0);
        static_assert(rp0.max_input_size == 8);
        static_assert(sizeof(keys_input_report<0>) == 8);
        static_assert(rp0.max_feature_id == 0);
        static_assert(rp0.max_feature_size == 0);
        static_assert(rp0.max_output_id == 0);
        static_assert(rp0.max_output_size == 1);
        static_assert(sizeof(output_report<0>) == 1);

        // test both compile-time and runtime
        static_assert(hid::rdf::get_application_usage_id(rp0.descriptor) ==
                      hid::page::generic_desktop::KEYBOARD);
        CHECK(hid::rdf::get_application_usage_id(
                  hid::rdf::descriptor_view::from_descriptor<app_report_descriptor<0>()>()) ==
              hid::page::generic_desktop::KEYBOARD);

        static constexpr auto desc5 = app_report_descriptor<5>();
        constexpr auto rp5 = hid::report_protocol(desc5);
        static_assert(rp5.max_input_id == 5);
        static_assert(rp5.max_input_size == 9);
        static_assert(sizeof(keys_input_report<5>) == 9);
        static_assert(rp5.max_feature_id == 0);
        static_assert(rp5.max_feature_size == 0);
        static_assert(rp5.max_output_id == 5);
        static_assert(rp5.max_output_size == 2);
        static_assert(sizeof(output_report<5>) == 2);

        // test both compile-time and runtime
        static_assert(hid::rdf::get_application_usage_id(rp5.descriptor) ==
                      hid::page::generic_desktop::KEYBOARD);
        CHECK(hid::rdf::get_application_usage_id(hid::rdf::descriptor_view(desc5)) ==
              hid::page::generic_desktop::KEYBOARD);
    };
};
