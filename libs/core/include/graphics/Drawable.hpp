// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

#include <core/DEFS.hpp>

class LIB_EXPORT_CONV Drawable {
public:

    Drawable() {}
    virtual ~Drawable() {}

    virtual void update() = 0;
    virtual void render() = 0;

};

#endif /* __DRAWABLE_HPP__ */