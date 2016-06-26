// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL


#ifndef __PHYSICS_MODEL_HPP__
#define __PHYSICS_MODEL_HPP__

#ifdef WIN_BUILD
 #define DLL_IMPORT __declspec(dllexport)
#else
 #define DLL_IMPORT
#endif

#define FLOAT_CMP_PRECISION 0.001f

#define FLOAT_EQ(val, expected) \
        val >= expected - FLOAT_CMP_PRECISION && val <= expected + FLOAT_CMP_PRECISION


struct DLL_IMPORT PhysicsModel {
    float speed;
    float weight;
    float angle;
    float height;
    float lossEnger;
    bool jump;
};

struct DLL_IMPORT Point2d {
    float x;
    float y;

    Point2d() : x(0.f), y(0.f) {}
    Point2d(float X, float Y) : x(X), y(Y) {}
    Point2d(const Point2d& p) : x(p.x), y(p.y) {}
    Point2d& operator=(const Point2d& p) { x = p.x; y = p.y; return *this; }
};

#endif /* __PHYSICS_MODEL_HPP__ */
