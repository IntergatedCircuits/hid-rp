# HID report descriptor format library

This project utilizes C++17 and above language features to implement a common, standalone library
for creating and parsing HID report descriptors.

## Features

* Easy to use C++ syntax to define HID report descriptors and reports (examples in `include/hid/reports`)
* Compile-time validation of HID report descriptors (any C/C++ source header is supported)
* Base design for implementing any custom descriptor parsing logic, either for compile or runtime

## Demos

### [stm32-i2c-hid][stm32-i2c-hid]

HID over I2C using a generic STM32 devkit, tested with Raspberry Pi.

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
#include "hid/rdf/descriptor.h"
#include "hid/page/generic_desktop.h"
#include "hid/page/button.h"

using namespace hid::rdf;
using namespace hid::page;

constexpr auto mouse_report_desc = descriptor(
    usage_page<generic_desktop>(),
    usage(generic_desktop::MOUSE),
    collection::application(
        usage(generic_desktop::POINTER),
        collection::physical(
            usage_extended_limits(button(1), button(3)),
            logical_limits(0, 1), // _limits combine _min and _max
            report_count(3),
            report_size(1),
            input::absolute_variable(),
            input::padding(5), // combines report_count(1), report_size(param), and input()
            usage(generic_desktop::X),
            usage(generic_desktop::Y),
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

This library implements two types of descriptor views, one for runtime (`descriptor_view`)
and one for `constexpr` compile-time (`ce_descriptor_view`), which offer iterating item-by-item.
A generic `parser` class is implemented that serves as a base for any kind of descriptor parsing logic.
Being able to parse the descriptor at compile-time and using the compiler for descriptor error checking
greatly reduces the development time of report descriptors.

## Usage pages

In the above example the `hid/page/` files aren't supplied by this library. They are in fact generated code,
using the [hid-usage-tables] project.

[USB-HID]: https://www.usb.org/sites/default/files/hid1_11.pdf
[hid-usage-tables]: https://github.com/IntergatedCircuits/hid-usage-tables
[stm32-i2c-hid]: https://github.com/benedekkupper/stm32-i2c-hid
