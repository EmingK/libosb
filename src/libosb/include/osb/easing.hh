#ifndef __OSB_EASING_HH__
#define __OSB_EASING_HH__

#include <ostream>

namespace osb {
    enum class Easing : int {
        Linear = 0,
        EaseOut,
        EaseIn,
        QuadIn,
        QuadOut,
        QuadInOut,
        CubicIn,
        CubicOut,
        CubicInOut,
        QuartIn,
        QuartOut,
        QuartInOut,
        QuintIn,
        QuintOut,
        QuintInOut,
        SineIn,
        SineOut,
        SineInOut,
        ExpoIn,
        ExpoOut,
        ExpoInOut,
        CircIn,
        CircOut,
        CircInOut,
        ElasticIn,
        ElasticOut,
        ElasticHalfOut,
        ElasticQuarterOut,
        ElasticInOut,
        BackIn,
        BackOut,
        BackInOut,
        BounceIn,
        BounceOut,
        BounceInOut
    };

    inline std::ostream& operator<<(std::ostream&os, Easing e) {
        return os << static_cast<int>(e);
    }
}

#endif // __OSB_EASING_HH__
