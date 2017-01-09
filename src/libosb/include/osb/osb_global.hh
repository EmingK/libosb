#ifndef __OSB_GLOBAL_HH__
#define __OSB_GLOBAL_HH__

#include <cstdint>
#include <ostream>

namespace osb {

    // Timing point value type in osb (ie. millisecond)
    typedef int32_t TimeValue;

    // Opacity value type
    typedef double OpacityValue;

    // Scale value type
    typedef double ScaleValue;

    // Rotation value type in osb (ie. radians)
    typedef double RotateValue;

    // Coordinate value type
    typedef double CoordinateValue;

    // Color channel value type
    typedef uint8_t ColorChannelValue;

    // Time span value type
    typedef struct {
        TimeValue start;
        TimeValue end;
    } TimeSpanValue;

    // Coornidate point value type
    typedef struct {
        CoordinateValue x;
        CoordinateValue y;
    } PointValue;

    // Vector scale value type
    typedef struct {
        ScaleValue scaleX;
        ScaleValue scaleY;
    } ScaleVectorValue;

    // Color value type
    typedef struct {
        ColorChannelValue r;
        ColorChannelValue g;
        ColorChannelValue b;
    } ColorValue;

    // operator overrides
    inline bool operator==(PointValue const& lhs, PointValue const& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    inline bool operator==(ScaleVectorValue const& lhs, ScaleVectorValue const& rhs) {
        return lhs.scaleX == rhs.scaleX && lhs.scaleY == rhs.scaleY;
    }
    inline bool operator==(ColorValue const& lhs, ColorValue const& rhs) {
        return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
    }

    inline std::ostream& operator<<(std::ostream& os, PointValue const& p) {
        return os << p.x << "," << p.y;
    }
    inline std::ostream& operator<<(std::ostream& os, ScaleVectorValue const& v) {
        return os << v.scaleX << "," << v.scaleY;
    }
    inline std::ostream& operator<<(std::ostream& os, ColorValue const& c) {
        return os << (int)c.r << "," << (int)c.g << "," << (int)c.b;
    }
}

#endif // __OSB_GLOBAL_HH__
