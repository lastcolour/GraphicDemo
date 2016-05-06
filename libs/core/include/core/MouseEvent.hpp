#ifndef __MOUSE_EVENT_HPP__
#define __MOUSE_EVENT_HPP__

enum class MouseKey {
    LEFT,
    RIGHT,
    MID
};

class MouseEvent {
public:

    MouseEvent() {}
    ~MouseEvent() {}

private:

    bool inFocus;
};

#endif /* __MOUSE_EVENT_HPP__ */