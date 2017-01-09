#ifndef __OSB_EVENT_HH__
#define __OSB_EVENT_HH__

#include <osb/osb_global.hh>
#include <osb/easing.hh>
#include <osb/line_helper.hh>

#include <string>
#include <ostream>
#include <memory>
#include <forward_list>

namespace osb {
    enum class EventType {
        Fade,
        Move,
        MoveX,
        MoveY,
        Scale,
        ScaleVector,
        Rotate,
        Color,
        Parameter,
        Loop,
        Trigger
    };

    namespace EventScriptValue {
        extern std::string const Fade;
        extern std::string const Move;
        extern std::string const MoveX;
        extern std::string const MoveY;
        extern std::string const Scale;
        extern std::string const ScaleVector;
        extern std::string const Rotate;
        extern std::string const Color;
        extern std::string const Parameter;
        extern std::string const Loop;
        extern std::string const Trigger;
    }

    /**
     * Abstract base Event.
     */
    class Event;
    typedef Event *EventRef;

    class Event {
    public:
        /**
         * Get the event's type identifier.
         */
        EventType type() const {
            return _type;
        }

        /**
         * @returns true if the event is a compound event
         */
        virtual bool isCompound() = 0;

        /**
         * @param e an event happens after self
         * @returns true if self can be coalesced with event e afterwards
         */
        virtual bool canCoalesceWithEvent(Event const& e) = 0;

        /**
         * write string form of this event to a output stream.
         *
         * @param os an output stream to write
         * @returns the output stream
         */
        virtual std::ostream& writeToStream(std::ostream& os) const = 0;
    protected:
        EventType _type;
        Event() { };
    };

    /**
     * Represents all kind of events of transitions from a value range [start, end].
     *
     * Template parameters:
     *   T event value type. Should implement operator== and operator<<(std::ostream&, T const&) for this type.
     *   eventType event type identifier
     *   scriptExpr representation in osb script
     */
    template<typename T, EventType eventType, std::string const& scriptExpr>
    class SimpleEvent : public Event {
    public:
        Easing easing;
        TimeSpanValue timeSpan;
        T startValue;
        T endValue;

        SimpleEvent(
            Easing easing_,
            TimeSpanValue timeSpan_,
            T startValue_,
            T endValue_
        ) : easing(easing_),
            timeSpan(timeSpan_),
            startValue(startValue_),
            endValue(endValue_) {
                _type = eventType;
            }
        SimpleEvent(
            Easing easing_,
            TimeValue startTime_,
            TimeValue endTime_,
            T startValue_,
            T endValue_
        ) : SimpleEvent(easing_, {startTime_, endTime_}, startValue_, endValue_) { }

        bool isCompound() override {
            return false;
        }
        bool canCoalesceWithEvent(Event const& e) override {
            if (_type == e.type()) {
                SimpleEvent const &se = dynamic_cast<SimpleEvent const &>(e);
                return (timeSpan.end - timeSpan.start == se.timeSpan.end - se.timeSpan.start);
            }
            return false;
        }
        std::ostream& writeToStream(std::ostream& os) const override {
            if (timeSpan.start == timeSpan.end) {
                if (startValue == endValue) {
                    return LineHelper::writeCommaJoined(os, scriptExpr, easing, timeSpan.start, "", startValue);
                }
                return LineHelper::writeCommaJoined(os, scriptExpr, easing, timeSpan.start, "", startValue, endValue);
            } else {
                if (startValue == endValue) {
                    return LineHelper::writeCommaJoined(os, scriptExpr, easing, timeSpan.start, timeSpan.end, startValue);
                }
                return LineHelper::writeCommaJoined(os, scriptExpr, easing, timeSpan.start, timeSpan.end, startValue, endValue);
            }
        }
    };

    /**
     * Abstract compound Event (loop, trigger).
     */
    class CompoundEvent : public Event {
    public:
        std::forward_list<std::shared_ptr<Event>> subEvents;

        bool isCompound() override {
            return true;
        }
        bool canCoalesceWithEvent(Event const& e) override {
            return false;
        }
    protected:
        using Event::_type;
    private:
        CompoundEvent() { };
    };

    // template type aliases
    using FadeEvent = SimpleEvent<OpacityValue, EventType::Fade, EventScriptValue::Fade>;
    using MoveEvent = SimpleEvent<PointValue, EventType::Move, EventScriptValue::Move>;
    using MoveXEvent = SimpleEvent<CoordinateValue, EventType::MoveX, EventScriptValue::MoveX>;
    using MoveYEvent = SimpleEvent<CoordinateValue, EventType::MoveY, EventScriptValue::MoveY>;
    using ScaleEvent = SimpleEvent<ScaleValue, EventType::Scale, EventScriptValue::Scale>;
    using VectorScaleEvent = SimpleEvent<ScaleVectorValue, EventType::ScaleVector, EventScriptValue::ScaleVector>;
    using RotateEvent = SimpleEvent<RotateValue, EventType::Rotate, EventScriptValue::Rotate>;
    using ColorEvent = SimpleEvent<ColorValue, EventType::Color, EventScriptValue::Color>;

    class LoopEvent : public CompoundEvent {
    public:
        TimeValue startTime;
        int loopCount;
    };

    inline std::ostream& operator<<(std::ostream& os, Event const& event) {
        return event.writeToStream(os);
    };
    inline std::ostream& operator<<(std::ostream& os, Event const *eventRef) {
        return os << *eventRef;
    }
}

#endif // __OSB_EVENT_HH__
