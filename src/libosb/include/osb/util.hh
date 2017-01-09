#ifndef __OSB_UTIL_HH__
#define __OSB_UTIL_HH__

#include <osb/osb_global.hh>
#include <cmath>
#include <type_traits>

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#endif

/**
 * convert literal degree value to radian (representatiion in osb files).
 *
 * Example:
 *   osb::RotateValue value = 90_deg; // converts to Pi/2 raidus
 *
 * @param degree value in degree
 * @returns value in radian
 */
constexpr osb::RotateValue operator"" _deg(long double degree) {
    return (osb::RotateValue)((M_PI / 180.0) * degree);
}

/**
 * convert literal second value to milliseconds.
 *
 * Example:
 *   osb::TimeValue value = 3.568_s; // converts to 3568 milliseconds
 *
 * @param second value in seconds
 * @returns value in milliseconds
 */
constexpr osb::TimeValue operator"" _s(long double second) {
    // round functions are not constexpr in OSX std lib
    return (osb::TimeValue)(second * 1000);
}

/**
 * convert literal second value to milliseconds.
 * negative values are not supported due to language restriction, use double version instead.
 *
 * Example:
 *   osb::TimeValue value = 3_s; // converts to 3000 milliseconds
 *
 * @param second value in seconds
 * @returns value in milliseconds
 */
constexpr osb::TimeValue operator"" _s(unsigned long long second) {
    return (osb::TimeValue)(second * 1000);
}

namespace osb {

    /**
     * Convenience color value builder.
     * accepts any integral type
     */
    template<typename T>
    ColorValue color(T value) {
        static_assert(std::is_integral<T>::value, "value type cannot be converted to ColorValue type");
        return {
            (ColorChannelValue)((value & 0xFF0000) >> 16),
            (ColorChannelValue)((value &   0xFF00) >> 8),
            (ColorChannelValue) (value &     0xFF)
        };
    }

    /**
     * Convenience color value builder.
     * accepts string literal type
     */
    template<>
    ColorValue color(char const *value) {
        // TODO
        return {0, 0, 0};
    }
}

#endif // __OSB_UTIL_HH__
