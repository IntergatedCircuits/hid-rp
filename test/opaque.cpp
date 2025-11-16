#include "hid/app/opaque.hpp"
#include "hid/rdf/descriptor.hpp"
#include "hid/rdf/formatter.hpp"
#include "hid/report_protocol.hpp"
#include "test_framework.hpp"

using namespace hid::app::opaque;

namespace hid::page
{
enum class custom_page : std::uint8_t;
template <>
constexpr inline auto get_info<custom_page>()
{
    return info(0xff01, 0x0003, "custom", nullptr, 0x0000);
}
enum class custom_page : std::uint8_t
{
    APPLICATION = 0x0001,
    IN_DATA = 0x0002,
    OUT_DATA = 0x0003,
};
} // namespace hid::page

using raw_in_report = hid::app::opaque::report<32, hid::report::type::INPUT>;
using raw_out_report = hid::app::opaque::report<32, hid::report::type::OUTPUT>;

SUITE(opaque_)
{
    TEST_CASE("opaque report descriptor")
    {
        using namespace hid::rdf;
        using namespace hid::page;
        // clang-format off
    static constexpr auto desc0 = descriptor(
        usage_extended(custom_page::APPLICATION),
        collection::application(
            hid::app::opaque::report_descriptor<raw_in_report>(custom_page::IN_DATA),

            hid::app::opaque::report_descriptor<raw_out_report>(custom_page::OUT_DATA)
        )
    );
        // clang-format on
        constexpr auto rp0 = hid::report_protocol(desc0);
        static_assert(rp0.max_input_id == 0);
        static_assert(rp0.max_input_size == sizeof(raw_in_report));
        static_assert(rp0.max_feature_id == 0);
        static_assert(rp0.max_feature_size == 0);
        static_assert(rp0.max_output_id == 0);
        static_assert(rp0.max_output_size == sizeof(raw_out_report));
        static_assert(rp0.report_count == 2);

        static_assert(hid::rdf::get_application_usage_id(rp0.descriptor) ==
                      hid::page::custom_page::APPLICATION);
        CHECK(hid::rdf::get_application_usage_id(hid::rdf::descriptor_view(desc0)) ==
              hid::page::custom_page::APPLICATION);
    };
};

