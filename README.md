# HID report descriptor format library

This project utilizes C++17 and above language features to implement a common library for creating and parsing
HID report descriptors.

## Motivation

The HID report descriptor format (HID RDF) is a unique descriptor format that was standardized in the USB HID class specification ([pdf][USB-HID]).
An HID peripheral device uses this descriptor to explain the internal layout of its messages to the host system.
This descriptor is therefore fixed at design time on the peripheral device, while the host system has to parse it
to understand the purpose(s) of the peripheral and its messages (known as reports).

As the format is designed to consume the least amount of resources (non-volatile memory), it is condensed,
meaning that each item's size can vary between 1 and 5 bytes, depending on the size of the value carried in it.
This property makes it complicated for the descriptor - that is stored as a raw array of bytes - to be created
from a variable amount of variable size items in a structured way.

Therefore the conventional way to define these descriptors has been to calculate the items by hand/script
and write the resulting raw bytes into the source code:

```C++
const unsigned char mouse_report_desc[] = {
    0x05, 0x01,    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,    // USAGE (Mouse)
    0xa1, 0x01,    // COLLECTION (Application)
    0x09, 0x01,    //   USAGE (Pointer)
    0xa1, 0x00,    //   COLLECTION (Physical)
    0x05, 0x09,    //     USAGE_PAGE (Buttons)
    0x19, 0x01,    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,    //     REPORT_COUNT (3)
    0x75, 0x01,    //     REPORT_SIZE (1)
    0x81, 0x02,    //     INPUT (Data,Var,Abs)
    0x95, 0x01,    //     REPORT_COUNT (1)
    0x75, 0x05,    //     REPORT_SIZE (5)
    0x81, 0x03,    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,    //     USAGE (X)
    0x09, 0x31,    //     USAGE (Y)
    0x15, 0x81,    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,    //     REPORT_SIZE (8)
    0x95, 0x02,    //     REPORT_COUNT (2)
    0x81, 0x06,    //     INPUT (Data,Var,Rel)
    0xc0,          //   END_COLLECTION
    0xc0           // END_COLLECTION
};
```

And while this certainly can be improved by [clever use of macros](https://github.com/IntergatedCircuits/HidReportDef/blob/8e77498e0e8f4bf4ba57a64ee958ba134de2a37e/include/hid/mouse.h#L35),
the result could be vastly improved by using the C++ compiler instead of the preprocessor.

Taking into consideration the more and more powerful `constexpr` capabilities of C++,
we can create a design that isn't only simpler to code, but that can perform compile-time verification
and extract relevant properties of the resulting descriptor.

## Design

### Descriptor definition

The current implementation allows us to rewrite the above descriptor to this:

```C++
#include "hid/rdf/all_items.h"
/* #include  [...] definition of usage pages */

using namespace hid::rdf;

constexpr auto mouse_report_desc = (
    usage_page(page::generic_desktop::PAGE_ID),
    usage(page::generic_desktop::MOUSE),
    collection::application(
        usage(page::generic_desktop::POINTER),
        collection::physical(
            usage_extended_limits(page::button(1), page::button(3)),
            logical_limits(0, 1), // _limits combine _min and _max
            report_count(3),
            report_size(1),
            input::absolute_variable(),
            input::padding(5), // combines report_count(1), report_size(param), and input()
            usage(page::generic_desktop::X),
            usage(page::generic_desktop::Y),
            logical_limits(-127, 127),
            report_count(2),
            report_size(8),
            input::relative_variable()
        )
    )
);
```

It is clear that the latter descriptor is much more expressive. We can create combined items such as `logical_limits(0, 1)`
instead of having a minimum and maximum in separate lines. Some item groups can be coded in more expressive way,
such as `input::padding(5)`. No COLLECTION will be left without a terminating END_COLLECTION item, and it's obvious,
which items belong to which collection.

The benefits don't stop here. Developers can create their own complex application descriptor templates, and parameterize them
depending on the application/device variant, instead of having to copy-paste and modify raw bytes.

### Descriptor parsing

Parsing the report descriptor is a lot more complicated, that's why it was delegated to be performed by the host operating system.
In practice it's done in iterations, the higher levels only determining the application type, then looking up the appropriate subdriver
for it (that's also when a peripheral with multiple top-level applications gets split).
The current implementation only implements a `descriptor_view`, with an iterator that advances item-by-item.

## Future plans

This library has a lot of potential for expansion, but as always, development resources are limited.
Contributions in the forms of pull requests and issues are welcome.

* [hid-usage-tables] needs a (Python) code generator
* add `constexpr` descriptor validator
* add `constexpr` descriptor properties parser (max IN, OUT and FEATURE report size is the most relevant information)

[USB-HID]: https://www.usb.org/sites/default/files/hid1_11.pdf
[hid-usage-tables]: https://github.com/IntergatedCircuits/hid-usage-tables
