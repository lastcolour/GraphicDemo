// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __MATH_3D_HPP__
#define __MATH_3D_HPP__

#include <core/DEFS.hpp>

struct LIB_EXPORT_CONV Quad {

    float origX;
    float origY;
    float width;
    float height;

public:

    Quad();
    Quad(float origX, float origY, float width, float height);
    Quad(const Quad& quad);
    ~Quad();

    Quad& operator=(const Quad& quad);

};

#endif /* __MATH_3D_HPP__ */