#ifndef __OSB_SPRITE_HH__
#define __OSB_SPRITE_HH__

#include <osb/event.hh>

#include <forward_list>
#include <memory>

namespace osb {
    class Object {
    public:
        std::forward_list<std::shared_ptr<Event>> events;
    };
}

#endif // __OSB_SPRITE_HH__
