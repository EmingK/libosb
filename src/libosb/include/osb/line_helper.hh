#ifndef __OSB_LINE_HELPER_HH__
#define __OSB_LINE_HELPER_HH__

#include <ostream>

namespace osb {
    namespace LineHelper {
        template<typename T>
        std::ostream& writeCommaJoined(std::ostream& os, T value) {
            return os << value;
        }

        template<typename T, typename... Args>
        std::ostream& writeCommaJoined(std::ostream& os, T value, Args... args) {
            os << value << ",";
            return writeCommaJoined(os, args...);
        }
    }
}

#endif // __OSB_LINE_HELPER_HH__
