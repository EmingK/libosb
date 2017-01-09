#include <osb/osb.hh>
#include <osb/util.hh>

#include <iostream>

int main() {
    auto move = osb::MoveEvent(
        osb::Easing::Linear,
        {1.6_s, 1.6_s},
        {320, 240},
        {480, 460}
    );
    auto rotate = osb::RotateEvent(
        osb::Easing::Linear,
        {1800, 1900},
        45.0_deg,
        90.0_deg
    );
    auto color = osb::ColorEvent(
        osb::Easing::Linear,
        {3_s, 6_s},
        osb::color(0xFFC80A),
        osb::color("A6B5C3")
    );
    std::cout << move << std::endl;
    std::cout << rotate << std::endl;
    std::cout << color << std::endl;
    std::cout << std::boolalpha << move.canCoalesceWithEvent(rotate) << std::endl;
    return 0;
}