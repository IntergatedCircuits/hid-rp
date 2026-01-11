#include "hid/app/lamparray.hpp"
#include "hid/rdf/formatter.hpp"
#include "hid/report_protocol.hpp"
#include "test_framework.hpp"

using namespace hid::app::lamparray;

SUITE(lamparray_)
{
    TEST_CASE("lamp array report descriptor")
    {
        using namespace hid::rdf;
        static constexpr auto desc = descriptor(
            // clang-format off
            usage_page<hid::page::lighting_and_illumination>(),
            usage(hid::page::lighting_and_illumination::LAMP_ARRAY),
            collection::application(
                lamp_array_attributes_report_descriptor<1>(),
                lamp_attributes_request_report_descriptor<2>(),
                lamp_attributes_response_report_descriptor<3>(),
                lamp_multi_update_report_descriptor<4, 10>(),
                lamp_range_update_report_descriptor<5>(),
                control_report_descriptor<6>()
            )
            // clang-format on
        );
        constexpr auto rp = hid::report_protocol::from_descriptor<desc>();
        static_assert(rp.input_report_count == 0);
        static_assert(rp.max_input_size == 0);
        static_assert(rp.feature_report_count == 6);
        static_assert(rp.max_feature_size == 25);
        static_assert(rp.output_report_count == 0);
        static_assert(rp.max_output_size == 0);
        static_assert(rp.uses_report_ids());

        constexpr auto table0 = hid::make_report_selector_table<desc>();
        static_assert(table0.size() == rp.feature_report_count);

        // test both compile-time and runtime
        static_assert(hid::rdf::get_application_usage_id(rp.descriptor) ==
                      hid::page::lighting_and_illumination::LAMP_ARRAY);
        CHECK(hid::rdf::get_application_usage_id(
                  hid::rdf::descriptor_view::from_descriptor<desc>()) ==
              hid::page::lighting_and_illumination::LAMP_ARRAY);
    };
};
