// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __KEYBOARD_EVENT_HPP__
#define __KEYBOARD_EVENT_HPP__

enum class KeyCode {
    UNKNOWN = 0,
    Q,
    W,
    E,
    R,
    T,
    Y,
    U,
    I,
    O,
    P,
    FIGURE_BRACKET_OPEN,
    FIGURE_BRACKET_CLOSE,
    BACK_SLASH,
    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,
    DOT_COMMA,
    APOSTROPHE,
    Z,
    X,
    C,
    V,
    B,
    N,
    M,
    COMMA,
    DOT,
    SLASH,
    SPACE
};

enum class KeyType {
    UNKNOWN = 0,
    RELEASE,
    PRESSED,
    REPEAT
};

class KeyboardEvent {
public:

    explicit KeyboardEvent(KeyCode keyCode, KeyType keyType) : 
        code(keyCode),
        type(keyType),
        altPressed(false),
        shiftPressed(false),
        ctrlPressed(false) {}

    KeyboardEvent(const KeyboardEvent& keyEvent) : 
        code(keyEvent.code),
        type(keyEvent.type),
        altPressed(keyEvent.altPressed), 
        shiftPressed(keyEvent.shiftPressed),
        ctrlPressed(keyEvent.ctrlPressed) {}

    KeyboardEvent& operator=(const KeyboardEvent& keyEvent) {
        if(this == &keyEvent) {
            return *this;
        }
        code = keyEvent.code;
        type = keyEvent.type;
        altPressed = keyEvent.altPressed;
        shiftPressed = keyEvent.shiftPressed;
        ctrlPressed =keyEvent.ctrlPressed;
        return *this;
    }

    ~KeyboardEvent() {}

    KeyCode getCode() const { return code; }
    KeyType getType() const { return type; }

    void setAltPressed(bool flag) { altPressed = flag; }
    void setShiftPressed(bool flag) { shiftPressed = flag; }
    void setCtrlPressed(bool flag) { ctrlPressed = flag; }

    bool isAltPressed() const {return altPressed; }
    bool isShiftPressed() const {return shiftPressed; }
    bool isCtrlPressed() const {return ctrlPressed; }


private:

    KeyCode code;
    KeyType type;
    bool altPressed;
    bool shiftPressed;
    bool ctrlPressed;

};

#endif /* __KEYBOARD_EVENT_HPP__  */