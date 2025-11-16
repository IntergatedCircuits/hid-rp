#include <boost/ut.hpp>

#define SUITE(name) ::boost::ut::suite name = []
#define TEST_CASE(name) ::boost::ut::detail::test{"test", name} = [=]() mutable
#define CHECK(...) ::boost::ut::expect(::boost::ut::that % __VA_ARGS__)
