#ifndef __SIMULATION_HPP__
#define __SIMULATION_HPP__

#include "Physics.hpp"

#include "GLDraw.hpp"

#include <memory>
#include <vector>

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

    void drawWorld();
    void drawPoint(const Point2d& p);

    Point2d normilze(const Point2d& p);

private:
    
    float timePoint;
    std::unique_ptr<Physics> physicsPtr;
    std::vector<Point2d> trajectory;

    GLDrawData pointDraw;
    GLDrawData worldDraw;
    float worldLen;
    float worldHeight;
};

#endif /* __SIMULATION_HPP__ */
