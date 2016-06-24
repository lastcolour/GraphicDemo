#ifndef __PHYSICS_MODEL_HPP__
#define __PHYSICS_MODEL_HPP__

#define DLL_IMPORT __declspec(dllexport)

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

    Point2d(float X, float Y) : x(X), y(Y) {} 
};

#endif /* __PHYSICS_MODEL_HPP__ */
