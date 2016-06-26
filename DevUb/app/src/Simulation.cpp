// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL


#include "AsyncSimulImpl.hpp"
#include "Simulation.hpp"
#include "glUtils.hpp"
#include "Logger.hpp"

#include <string>
#include <vector>
#include <cassert>
#include <thread>

// Hardcoded values

const char* POINT_FRAG = "shaders/singleColor.glsl";
const char* POINT_VERT = "shaders/pointVert.glsl";
const int   SIDE_COUNT = 24;
const int   POINTS_COUNT = SIDE_COUNT + 2; // Draw as triangle fun

const char* UNI_COLOR  = "fColor";
const char* UNI_RADIUS = "vRadius";
const char* UNI_CENTER = "vCenter";

const float POINT_RADIUS = 0.1f;

Simulation::Simulation(Physics* physics) :
    pointDrawPtr(nullptr),
    asyncImpl(new AsyncSymulImpl()),
    physicsPtr(physics),
    timePoint(0.f),
    worldLen(0.f),
    worldHeight(0.f),
    aspectRatio(0.f),
    isXConstant(false),
    isLogFinish(false) {

    assert(physicsPtr != nullptr && "Ivalid physics");
}

Simulation::~Simulation() {
    if(pointDrawPtr != nullptr) {
        pointDrawPtr->clear();
    }
}

void Simulation::setViewPort(int width, int height) {
    aspectRatio = width / float(height);
    glViewport(0, 0, width, height);
}

void Simulation::update(float timeDelta) {
    timePoint += timeDelta;
    asyncImpl->setWaitFor(timePoint); // set that we wait for new point
}

void Simulation::restart() {
    assert(physicsPtr != nullptr && "Invalid physic");
    timePoint = 0.f;
    isLogFinish = false;
    asyncImpl->restart();
}

void Simulation::drawPoint(const Point2d& point) {
    Point2d normP = normilze(point);
    glUseProgram(pointDrawPtr->progID);
    glBindVertexArray(pointDrawPtr->vaoID);
    glUniform1f(glGetUniformLocation(pointDrawPtr->progID, UNI_RADIUS), POINT_RADIUS);
    glUniform4f(glGetUniformLocation(pointDrawPtr->progID, UNI_COLOR), 0.4f, 0.f, 0.f, 1.f); // circle color
    glUniform2f(glGetUniformLocation(pointDrawPtr->progID, UNI_CENTER), normP.x, normP.y);

    glDrawArrays(GL_TRIANGLE_FAN, 0, POINTS_COUNT);

    glBindVertexArray(0);
}

Point2d Simulation::normilze(const Point2d& p) {
    // locate point in the world
    Point2d tPoint(0.f, 0.f);
    if(!isXConstant) {
        tPoint.x = (1.f - POINT_RADIUS * 2.f) * (2.f * p.x / worldLen - 1.f);
    } else {
        tPoint.x = 0.f;
    }
    tPoint.y = (1.f - POINT_RADIUS * 2.f) * (2.f * p.y / worldHeight - 1.f);
    return tPoint;
}

void Simulation::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    Point2d tPoint = asyncImpl->getLastReady();
    if(FLOAT_EQ(tPoint.y, 0.f) && !physicsPtr->isFinished()) {
        Logger::debug("Simulation", "Jump");
    } else if (physicsPtr->isFinished() && !isLogFinish) {
        Logger::debug("Simulation", "Finished");
        isLogFinish = true;
    }
    drawPoint(tPoint);
}

bool Simulation::init() {
    assert(physicsPtr->isValid() && "Invalid physic for simulation");

    worldLen = physicsPtr->getFlyLen();
    worldHeight = physicsPtr->getFlyHeight();
    if(FLOAT_EQ(worldLen, 0.f)) {
        worldLen = 1.f;
        isXConstant = true;
    }
    worldHeight = std::max(worldHeight, worldLen);

    glClearColor(0.4f, 0.4f, 0.4f, 1.f); // grey

    pointDrawPtr.reset(createGLDraw(POINT_VERT, POINT_FRAG, generateCircle(SIDE_COUNT)));
    if (pointDrawPtr == nullptr || !pointDrawPtr->isValid()) {
        return false;
    }
    // Start async calculations on given physics
    Logger::info("Simulation", "Initialized");
    asyncImpl->start(physicsPtr.get());
    return true;
}
