#ifndef __HID_PAGE_SIMULATION_H_
#define __HID_PAGE_SIMULATION_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class simulation : usage_id_type;
    template<>
    struct info<simulation>
    {
        constexpr static usage_id_type base_id = 0x00020000;
        constexpr static usage_id_type max_usage = 0x00d0 | base_id;
        constexpr static const char* name = "Simulation Controls";
    };
    enum class simulation : usage_id_type
    {
        FLIGHT_SIMULATION_DEVICE = 0x0001 | info<simulation>::base_id,
        AUTOMOBILE_SIMULATION_DEVICE = 0x0002 | info<simulation>::base_id,
        TANK_SIMULATION_DEVICE = 0x0003 | info<simulation>::base_id,
        SPACESHIP_SIMULATION_DEVICE = 0x0004 | info<simulation>::base_id,
        SUBMARINE_SIMULATION_DEVICE = 0x0005 | info<simulation>::base_id,
        SAILING_SIMULATION_DEVICE = 0x0006 | info<simulation>::base_id,
        MOTORCYCLE_SIMULATION_DEVICE = 0x0007 | info<simulation>::base_id,
        SPORTS_SIMULATION_DEVICE = 0x0008 | info<simulation>::base_id,
        AIRPLANE_SIMULATION_DEVICE = 0x0009 | info<simulation>::base_id,
        HELICOPTER_SIMULATION_DEVICE = 0x000a | info<simulation>::base_id,
        MAGIC_CARPET_SIMULATION_DEVICE = 0x000b | info<simulation>::base_id,
        BICYCLE_SIMULATION_DEVICE = 0x000c | info<simulation>::base_id,
        FLIGHT_CONTROL_STICK = 0x0020 | info<simulation>::base_id,
        FLIGHT_STICK = 0x0021 | info<simulation>::base_id,
        CYCLIC_CONTROL = 0x0022 | info<simulation>::base_id,
        CYCLIC_TRIM = 0x0023 | info<simulation>::base_id,
        FLIGHT_YOKE = 0x0024 | info<simulation>::base_id,
        TRACK_CONTROL = 0x0025 | info<simulation>::base_id,
        AILERON = 0x00b0 | info<simulation>::base_id,
        AILERON_TRIM = 0x00b1 | info<simulation>::base_id,
        ANTI_TORQUE_CONTROL = 0x00b2 | info<simulation>::base_id,
        AUTOPILOT_ENABLE = 0x00b3 | info<simulation>::base_id,
        CHAFF_RELEASE = 0x00b4 | info<simulation>::base_id,
        COLLECTIVE_CONTROL = 0x00b5 | info<simulation>::base_id,
        DIVE_BRAKE = 0x00b6 | info<simulation>::base_id,
        ELECTRONIC_COUNTERMEASURES = 0x00b7 | info<simulation>::base_id,
        ELEVATOR = 0x00b8 | info<simulation>::base_id,
        ELEVATOR_TRIM = 0x00b9 | info<simulation>::base_id,
        RUDDER = 0x00ba | info<simulation>::base_id,
        THROTTLE = 0x00bb | info<simulation>::base_id,
        FLIGHT_COMMUNICATIONS = 0x00bc | info<simulation>::base_id,
        FLARE_RELEASE = 0x00bd | info<simulation>::base_id,
        LANDING_GEAR = 0x00be | info<simulation>::base_id,
        TOE_BRAKE = 0x00bf | info<simulation>::base_id,
        TRIGGER = 0x00c0 | info<simulation>::base_id,
        WEAPONS_ARM = 0x00c1 | info<simulation>::base_id,
        WEAPONS_SELECT = 0x00c2 | info<simulation>::base_id,
        WING_FLAPS = 0x00c3 | info<simulation>::base_id,
        ACCELERATOR = 0x00c4 | info<simulation>::base_id,
        BRAKE = 0x00c5 | info<simulation>::base_id,
        CLUTCH = 0x00c6 | info<simulation>::base_id,
        SHIFTER = 0x00c7 | info<simulation>::base_id,
        STEERING = 0x00c8 | info<simulation>::base_id,
        TURRET_DIRECTION = 0x00c9 | info<simulation>::base_id,
        BARREL_ELEVATION = 0x00ca | info<simulation>::base_id,
        DIVE_PLANE = 0x00cb | info<simulation>::base_id,
        BALLAST = 0x00cc | info<simulation>::base_id,
        BICYCLE_CRANK = 0x00cd | info<simulation>::base_id,
        HANDLE_BARS = 0x00ce | info<simulation>::base_id,
        FRONT_BRAKE = 0x00cf | info<simulation>::base_id,
        REAR_BRAKE = 0x00d0 | info<simulation>::base_id,
    };
}

#endif // __HID_PAGE_SIMULATION_H_

