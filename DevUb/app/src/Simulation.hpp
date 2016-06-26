// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL

#ifndef __SIMULATION_HPP__
#define __SIMULATION_HPP__

#include "AsyncSimulImpl.hpp"
#include "Physics.hpp"

#include <memory>
#include <vector>

class GLDrawData;

class Simulation {
public:

    Simulation(Physics* physics);
    ~Simulation();

    void restart();
    void update(float timeDelta);
    void draw();
    bool init();

    void setViewPort(int width, int height);

private:

    void updatePoint();
    void getLastPoint();
    void drawPoint(const Point2d& p);

    Point2d normilze(const Point2d& p);

private:

    std::unique_ptr<GLDrawData> pointDrawPtr;
    std::unique_ptr<AsyncSymulImpl> asyncImpl;
    std::unique_ptr<Physics> physicsPtr;
    float timePoint;
    float worldLen;
    float worldHeight;
    float aspectRatio;
    bool  isXConstant;
    bool  isLogFinish;
};

#endif /* __SIMULATION_HPP__ */
