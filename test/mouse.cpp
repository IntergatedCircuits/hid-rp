#include "hid/app/mouse.hpp"
#include "hid/rdf/formatter.hpp"
#include "hid/report_protocol.hpp"
#include "test_framework.hpp"

using namespace hid::app::mouse;

template <uint8_t MOUSE_REPORT_ID = 0, hid::page::button LAST_BUTTON = hid::page::button(3),
          int16_t AXIS_LIMIT = 127, int16_t WHEEL_LIMIT = 32767,
          int16_t MAX_SCROLL_RESOLUTION = 120>
constexpr auto high_res_mouse_desc()
{
    using namespace hid::page;
    using namespace hid::rdf;

    // clang-format off
    return descriptor(
        usage_page<generic_desktop>(),
        usage(generic_desktop::MOUSE),
        collection::application(
            conditional_report_id<MOUSE_REPORT_ID>(),
            usage(generic_desktop::POINTER),
            collection::physical(
                // buttons
                usage_extended_limits(button(1), LAST_BUTTON),
                logical_limits<1, 1>(0, 1),
                report_count(static_cast<uint8_t>(LAST_BUTTON)),
                report_size(1),
                input::absolute_variable(),
                input::byte_padding<static_cast<uint8_t>(LAST_BUTTON)>(),

                // relative X,Y directions
                usage(generic_desktop::X),
                usage(generic_desktop::Y),
                logical_limits<value_size(AXIS_LIMIT)>(-AXIS_LIMIT, AXIS_LIMIT),
                report_count(2),
                report_size(value_size(AXIS_LIMIT) * 8),
                input::relative_variable(),

                hid::app::mouse::high_resolution_scrolling<WHEEL_LIMIT, MAX_SCROLL_RESOLUTION>()
            )
        )
    );
    // clang-format on
};

SUITE(mouse_)
{
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

        static_assert(rp0.report_count == 1);
        constexpr auto table0 = hid::make_report_selector_table<app_report_descriptor<0>()>();
        static_assert(table0.size() == 1);
        static_assert(table0[0] == report<0>::selector());

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

        static_assert(rp5.report_count == 1);
        constexpr auto table5 = hid::make_report_selector_table<app_report_descriptor<5>()>();
        static_assert(table5.size() == 1);
        static_assert(table5[0] == report<5>::selector());

        // test both compile-time and runtime
        static_assert(hid::rdf::get_application_usage_id(rp5.descriptor) ==
                      hid::page::generic_desktop::MOUSE);
        CHECK(hid::rdf::get_application_usage_id(hid::rdf::descriptor_view(desc5)) ==
              hid::page::generic_desktop::MOUSE);
    };

    TEST_CASE("high-resolution mouse report descriptor")
    {
        static constexpr auto desc0 = high_res_mouse_desc<0>();
        constexpr auto rp0 = hid::report_protocol(desc0);
        static_assert(rp0.max_input_id == 0);
        static_assert(rp0.max_input_size == 7);
        static_assert(sizeof(hid::app::mouse::report<0>) == 3);
        static_assert(rp0.max_feature_id == 0);
        static_assert(rp0.max_feature_size == 1);
        static_assert(rp0.max_output_id == 0);
        static_assert(rp0.max_output_size == 0);

        static_assert(rp0.report_count == 2);
        constexpr auto table0 = hid::make_report_selector_table<high_res_mouse_desc<0>()>();
        static_assert(table0.size() == 2);
        static_assert(table0[0] == report<0>::selector());
        static_assert(table0[1] == resolution_multiplier_report<120, 0>::selector());

        // test both compile-time and runtime
        static_assert(hid::rdf::get_application_usage_id(rp0.descriptor) ==
                      hid::page::generic_desktop::MOUSE);
        CHECK(hid::rdf::get_application_usage_id(hid::rdf::descriptor_view(desc0)) ==
              hid::page::generic_desktop::MOUSE);

        static constexpr auto desc5 = high_res_mouse_desc<5>();
        constexpr auto rp5 = hid::report_protocol(desc5);
        static_assert(rp5.max_input_id == 5);
        static_assert(rp5.max_input_size == 8);
        static_assert(sizeof(hid::app::mouse::report<5>) == 4);
        static_assert(rp5.max_feature_id == 5);
        static_assert(rp5.max_feature_size == 2);
        static_assert(rp5.max_output_id == 0);
        static_assert(rp5.max_output_size == 0);

        static_assert(rp5.report_count == 2);
        constexpr auto table5 = hid::make_report_selector_table<high_res_mouse_desc<5>()>();
        static_assert(table5.size() == 2);
        static_assert(table5[0] == report<5>::selector());
        static_assert(table5[1] == resolution_multiplier_report<120, 5>::selector());

        // test both compile-time and runtime
        static_assert(hid::rdf::get_application_usage_id(rp5.descriptor) ==
                      hid::page::generic_desktop::MOUSE);
        CHECK(hid::rdf::get_application_usage_id(hid::rdf::descriptor_view(desc5)) ==
              hid::page::generic_desktop::MOUSE);
    };
};
