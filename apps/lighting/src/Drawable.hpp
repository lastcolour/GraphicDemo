#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

class Drawable {
public:

    Drawable() {}
    virtual ~Drawable() {}

    virtual void draw() = 0;
    virtual void update() = 0;
};

#endif /* __DRAWABLE_HPP__ */