// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __IO_EVENT_HPP__
#define __IO_EVENT_HPP__

#include <core/DEFS.hpp>

enum class EventType {
    UNKNOWN = 0,
    RELEASE,
    PRESSED,
    REPEAT,
    MOVE,
    ROLL,
    NONE
};

#endif /* __IO_EVENT_HPP__ */